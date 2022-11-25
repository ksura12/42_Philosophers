/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:38:52 by ksura             #+#    #+#             */
/*   Updated: 2022/11/25 19:29:06 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_atoi(const char *str)
{
	long int	n;
	int			m;

	n = 0;
	m = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			m = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		n = n * 10 + *str - '0';
		str++;
		if (n > 2147483647 && m == 1)
			return (-1);
		else if (n > 2147483648 && m == -1)
			return (0);
	}
	return (n * m);
}

t_philos	**ft_philnew(t_philostr *philostr)
{
	t_philos	**philos;
	int 		i;

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
		pthread_mutex_init(&philos[i]->last_meal_mutex, NULL);
		i++;
	}
	return(philos);
}

t_fork	**ft_forks(t_philostr *philostr)
{
	t_fork	**forks;
	int 		i;

	forks = malloc(sizeof (t_fork *) * philostr->philo_num);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < philostr->philo_num)
	{
		forks[i] = malloc(sizeof(t_fork));
		if (!forks[i])
			return (NULL);
		forks[i]->in_use = 0;
		pthread_mutex_init(&forks[i]->fork_mutex, NULL);
		i++;
	}
	return (forks);
}

void	print_main_str(t_philostr	*main_str)
{
	int i = 0;
	printf("main_str Philo_num: %i\n", main_str->philo_num);
	printf("main_str->time_to_die: %i\n", main_str->time_to_die);
	printf("main_str->time_to_eat: %i\n", main_str->time_to_eat);
	printf("main_str->time_to_sleep: %i\n", main_str->time_to_sleep);
	printf("main_str->c_eat: %i\n", main_str->c_eat);
	printf("main_str->stop: %i\n", main_str->stop);
	printf("main_str->full: %i\n", main_str->full);
	printf("main_str->time_start: %li\n", main_str->time_start);
	while (i < main_str->philo_num)
	{
		printf("philo id: %i\n", main_str->philos[i]->id_num);
		printf("philo id: %i\n", main_str->philos[i]->philostr->philos[i]->id_num);
		printf("fork in use: %i\n", main_str->forks[i]->in_use);
		i++;
	}
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
	pthread_mutex_init(&philostr->print_mutex, NULL);
	pthread_mutex_init(&philostr->full_mutex, NULL);
	pthread_mutex_init(&philostr->stop_mutex, NULL);
	philostr->stop = 0;
	philostr->full = 0;
	philostr->forks = ft_forks(philostr);
	philostr->philos = ft_philnew(philostr);
	philostr->time_to_think = (philostr->time_to_die 
	- philostr->time_to_sleep - philostr->time_to_eat) / 4;
	return (philostr);
}
