/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:38:52 by ksura             #+#    #+#             */
/*   Updated: 2022/11/27 17:56:01 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/**
 * @brief initialises the array of philosopher structs
 * 
 * @param philostr 
 * @return t_philos** 
 */
t_philos	**ft_philnew(t_philostr *philostr)
{
	t_philos	**philos;
	int			i;

	philos = malloc(sizeof (t_philos) * philostr->philo_num);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < philostr->philo_num)
	{
		philos[i] = malloc(sizeof(t_philos));
		philos[i]->id_num = i + 1;
		philos[i]->nb_meals = 0;
		philos[i]->philostr = philostr;
		philos[i]->last_meal_eaten = get_time_ms();
		philos[i]->last_mealsem = sem_open("/last_mealsem", O_CREAT);
		i++;
	}
	return (philos);
}

/**
 * @brief initialises the main structure
 * includes starting time of simulation
 *
 * @param argv
 * @return t_philostr*
 */
t_philostr	*init_all(char **argv)
{
	t_philostr	*philostr;

	philostr = malloc(sizeof(t_philostr));
	if (philostr == NULL)
		return (NULL);
	philostr->philo_num = ft_atoi(argv[1]);
	philostr->time_to_die = ft_atoi(argv[2]);
	philostr->time_to_eat = ft_atoi(argv[3]);
	philostr->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philostr->c_eat = ft_atoi(argv[5]);
	else
		philostr->c_eat = 0;
	philostr->stopsem = sem_open("/stopsem", O_CREAT);
	philostr->printsem = sem_open("/printsem", O_CREAT);
	philostr->fullsem = sem_open("/fullsem", O_CREAT);
	philostr->stop = 0;
	philostr->full = 0;
	philostr->forks = sem_open("/forks", O_CREAT, S_IROTH | S_IWOTH, philostr->philo_num);
	philostr->philos = ft_philnew(philostr);
	philostr->time_to_think = (philostr->time_to_die \
	- philostr->time_to_sleep - philostr->time_to_eat) / 4;
	return (philostr);
}
