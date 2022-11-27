/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:38:52 by ksura             #+#    #+#             */
/*   Updated: 2022/11/26 22:11:30 by ksura            ###   ########.fr       */
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
			if (check_full(philostr))
			{
				pthread_mutex_lock(&philostr->stop_mutex);
				philostr->stop = 1;
				pthread_mutex_unlock(&philostr->stop_mutex);
				break ;
			}
			i++;
		}
	}
	return (NULL);
}

int	lifetime_counter(t_philos	*one_phil)
{
	time_t	time;

	time = get_time_ms();
	pthread_mutex_lock(&one_phil->last_meal_mutex);
	if ((time - one_phil->last_meal_eaten) >= one_phil->philostr->time_to_die)
	{
		pthread_mutex_unlock(&one_phil->last_meal_mutex);
		print_event(one_phil->philostr, one_phil->id_num, 5);
		pthread_mutex_lock(&one_phil->philostr->stop_mutex);
		one_phil->philostr->stop = 1;
		pthread_mutex_unlock(&one_phil->philostr->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&one_phil->last_meal_mutex);
	return (0);
}

int	check_full(t_philostr *philostr)
{
	pthread_mutex_lock(&philostr->full_mutex);
	if (philostr->full == philostr->philo_num)
	{
		pthread_mutex_unlock(&philostr->full_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philostr->full_mutex);
	return (0);
}

int	stop_checker(t_philostr *philostr)
{
	pthread_mutex_lock(&philostr->stop_mutex);
	if (philostr->stop == 1)
	{
		pthread_mutex_unlock(&philostr->stop_mutex);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philostr->stop_mutex);
		return (1);
	}
}
