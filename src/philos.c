/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:38:52 by ksura             #+#    #+#             */
/*   Updated: 2022/11/03 14:45:03 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// void taking_fork(t_philostr	*philostr);
// {

// }

void *living(void *data)
{
	// (void)data;
	t_onephil	*one_phil;

	one_phil = (t_onephil *)data;

	// pthread_mutex_lock(one_phil->print_mutex);
	// // printf("Thread %lu is living\n", (unsigned long)one_phil->tid);
	// print_time_thread(one_phil);
	// printf("Philosopher %i is alive\n", one_phil->id_num);
	// pthread_mutex_unlock(one_phil->print_mutex);
	while(1)
	{
		pthread_mutex_lock(&one_phil->philostr->stop_mutex);
		if (one_phil->philostr->stop == 1)
		{
			pthread_mutex_unlock(&one_phil->philostr->stop_mutex);
			return(NULL);
		}
		pthread_mutex_unlock(&one_phil->philostr->stop_mutex);
		while (1)
		{
			pthread_mutex_lock(&one_phil->fork_right->fork_mutex);
			if (one_phil->fork_right->in_use == 0)
			{
				one_phil->fork_right->in_use = 1;
				pthread_mutex_unlock(&one_phil->fork_right->fork_mutex);
				pthread_mutex_lock(&one_phil->fork_left->fork_mutex);
				if (one_phil->fork_left->in_use == 0)
				{
					pthread_mutex_lock(&one_phil->fork_right->fork_mutex);
					pthread_mutex_lock(&one_phil->philostr->print_mutex);
					pthread_mutex_lock(&one_phil->philostr->stop_mutex);
					if (one_phil->philostr->stop == 1)
					{
						pthread_mutex_unlock(&one_phil->philostr->stop_mutex);
						return(NULL);
					}
					pthread_mutex_unlock(&one_phil->philostr->stop_mutex);
					print_time_thread(one_phil);
					printf("%i has taken a fork\n", one_phil->id_num);
					print_time_thread(one_phil);
					printf("%i is eating\n", one_phil->id_num);
					pthread_mutex_unlock(&one_phil->philostr->print_mutex);
					usleep(one_phil->philostr->time_to_eat * 1000);
					one_phil->fork_right->in_use = 0;
					pthread_mutex_unlock(&one_phil->fork_right->fork_mutex);
					pthread_mutex_unlock(&one_phil->fork_left->fork_mutex);
					one_phil->last_meal_eaten = get_time_ms();
					break;
				}
				else
				{
					pthread_mutex_unlock(&one_phil->fork_left->fork_mutex);
					usleep(1 * 1000);
				}
			}
			else
			{
				pthread_mutex_unlock(&one_phil->fork_right->fork_mutex);
				usleep(1 * 1000);
			}
		}
		// break;
	}
	return (NULL);
}

void *supervising(void *data)
{
	// (void)data;
	t_onephil	*supervi;
	int			i;

	supervi = (t_onephil *)data;

	// pthread_mutex_lock(one_phil->print_mutex);
	// // printf("Thread %lu is living\n", (unsigned long)one_phil->tid);
	// print_time_thread(one_phil);
	// // printf("Supervisoris alive\n");
	// pthread_mutex_unlock(one_phil->print_mutex);
	// usleep(100 *1000);
	// pthread_mutex_lock(one_phil->stop_mutex);
	// *one_phil->stop = 1;
	// pthread_mutex_unlock(one_phil->stop_mutex);

	while (1)
	{
		i = 0;
		while (i < supervi->philostr->philo_num)
		{
			if (lifetime_counter(&supervi[i + 1]) == 1)
			{
				return (NULL);
			}
			i++;
		}

	}
	return (NULL);
}

void	philos(t_onephil **phili)
{
	int c;
	
	// pthread_t	tid[600];

	// philostr->counter = 0;
	c = phili[0]->philostr->philo_num + 1;
	pthread_create(&phili[c]->tid, NULL, &supervising, &phili[c]);
	c = phili[0]->philostr->philo_num;
	while (phili[0]->philostr->philo_num > c - 1)
	{
		phili[c]->id_num = c;
		pthread_create(&phili[c]->tid, NULL, &living, &phili[c]);
		c++;
	}
	c--;
	while (c >= 0)
	{
		// print_time(philostr);
		pthread_join(phili[c]->tid, NULL);
		pthread_mutex_lock(&phili[0]->philostr->print_mutex);
		printf("Joining thread n: %lu with main\n", (unsigned long)phili[c]->tid);
		pthread_mutex_unlock(&phili[0]->philostr->print_mutex);
		// free (tid[c]);
		c--;
	}
}

int	lifetime_counter(t_onephil	*one_phil)
{
	time_t	time;
	
	time = get_time_ms();
	if (time - one_phil->last_meal_eaten >= one_phil->philostr->time_to_die)
	{
		pthread_mutex_lock(&one_phil->philostr->stop_mutex);
		one_phil->philostr->stop = 1;
		pthread_mutex_unlock(&one_phil->philostr->stop_mutex);
		pthread_mutex_lock(&one_phil->philostr->print_mutex);
		print_time_thread(one_phil);
		printf("%i died\n", one_phil->id_num);
		pthread_mutex_unlock(&one_phil->philostr->print_mutex);
		return (1);
	}
	return (0);
}