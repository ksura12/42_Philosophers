/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:38:52 by ksura             #+#    #+#             */
/*   Updated: 2022/11/27 18:22:34 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*supervising(void *data)
{
	t_philostr	*philostr;
	int			i;

	philostr = (t_philostr *)data;
	while (stop_checker(philostr))
	{
		i = 0;
		while (i < philostr->philo_num)
		{
			if (lifetime_counter(philostr->philos[i]) == 1)
				break ;
			i++;
		}
	}
	return (NULL);
}

int	lifetime_counter(t_philos	*one_phil)
{
	time_t	time;

	time = get_time_ms();
	sem_wait(one_phil->last_mealsem);
	if ((time - one_phil->last_meal_eaten) >= one_phil->philostr->time_to_die)
	{
		sem_post(one_phil->last_mealsem);
		print_event(one_phil->philostr, one_phil->id_num, 5);
		sem_wait(one_phil->philostr->stopsem);
		one_phil->philostr->stop = 1;
		sem_post(one_phil->philostr->stopsem);
		return (1);
	}
	sem_post(one_phil->last_mealsem);
	return (0);
}

int	stop_checker(t_philostr *philostr)
{
	sem_wait(philostr->stopsem);
	if (philostr->stop == 1)
	{
		sem_post(philostr->stopsem);
		return (0);
	}
	else
	{
		sem_post(philostr->stopsem);
		return (1);
	}
}
