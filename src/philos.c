/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:38:52 by ksura             #+#    #+#             */
/*   Updated: 2022/11/02 18:03:37 by ksura            ###   ########.fr       */
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

	pthread_mutex_lock(one_phil->print_mutex);
	// printf("Thread %lu is living\n", (unsigned long)one_phil->tid);
	print_time_thread(one_phil);
	printf("Philosopher %i is alive\n", one_phil->id_num);
	pthread_mutex_unlock(one_phil->print_mutex);
	while(1)
	{
		printf("%i one\n", one_phil->id_num);
		pthread_mutex_lock(one_phil->stop_mutex);
		printf("%i onepointone\n", one_phil->id_num);
		if (*one_phil->stop == 1)
		{
			pthread_mutex_unlock(one_phil->stop_mutex);
			return(NULL);
		}
		pthread_mutex_unlock(one_phil->stop_mutex);
		printf("%i onepointone\n", one_phil->id_num);
		while (1)
		{
			printf("%i two\n", one_phil->id_num);
			pthread_mutex_lock(&one_phil->fork[0].fork_mutex);
			if (one_phil->fork[0].in_use == 0)
			{
				printf("%i three\n", one_phil->id_num);
				one_phil->fork[0].in_use = 1;
				pthread_mutex_unlock(&one_phil->fork[0].fork_mutex);
				printf("%i tthree.1\n", one_phil->id_num);
				pthread_mutex_lock(&one_phil->fork[1].fork_mutex);
				printf("%i tthree.2\n", one_phil->id_num);
				if (one_phil->fork[1].in_use == 0)
				{
					pthread_mutex_lock(&one_phil->fork[0].fork_mutex);
					printf("%i tthree.3\n", one_phil->id_num);
					pthread_mutex_lock(one_phil->print_mutex);
					printf("%i tthree.4\n", one_phil->id_num);
					pthread_mutex_lock(one_phil->stop_mutex);
					printf("%i tthree.5\n", one_phil->id_num);
					if (*one_phil->stop == 1)
					{
						printf("%i tthree.6\n", one_phil->id_num);
						pthread_mutex_unlock(one_phil->stop_mutex);
						return(NULL);
					}
					print_time_thread(one_phil);
					printf("%i has taken a fork\n", one_phil->id_num);
					print_time_thread(one_phil);
					printf("%i is eating\n", one_phil->id_num);
					pthread_mutex_unlock(one_phil->print_mutex);
					usleep(one_phil->time_to_eat * 1000);
					one_phil->fork[0].in_use = 0;
					pthread_mutex_unlock(&one_phil->fork[0].fork_mutex);
					pthread_mutex_unlock(&one_phil->fork[1].fork_mutex);
					break;
				}
				else
				{
					printf("%i is in\n", one_phil->id_num);
					pthread_mutex_unlock(&one_phil->fork[1].fork_mutex);
					usleep(1 * 1000);
				}
			}
			else
			{
				printf("%i is out\n", one_phil->id_num);
				pthread_mutex_unlock(&one_phil->fork[0].fork_mutex);
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
	t_onephil	*one_phil;

	one_phil = (t_onephil *)data;

	pthread_mutex_lock(one_phil->print_mutex);
	// printf("Thread %lu is living\n", (unsigned long)one_phil->tid);
	print_time_thread(one_phil);
	printf("Supervisoris alive\n");
	pthread_mutex_unlock(one_phil->print_mutex);
	usleep(100 *1000);
	pthread_mutex_lock(one_phil->stop_mutex);
	*one_phil->stop = 1;
	pthread_mutex_unlock(one_phil->stop_mutex);

	// while (1)
	// {
	// 	if (*one_phil->dead == 1)
	// 	{
	// 		*one_phil->stop = 1;
	// 		break;
	// 	}
	// }

	
	// taking_fork(philostr);
	return (NULL);
}

void	philos(t_philostr *philostr)
{
	int c;
	// pthread_t	tid[600];

	// philostr->counter = 0;
	c = 0;
	pthread_create(&philostr->one_phil[c].tid, NULL, &supervising, &philostr->one_phil[c]);
	c++;
	while (philostr->philo_num > c - 1)
	{
		philostr->one_phil[c].id_num = c;
		pthread_create(&philostr->one_phil[c].tid, NULL, &living, &philostr->one_phil[c]);
		c++;
	}
	c--;
	while (c >= 0)
	{
		// print_time(philostr);
		pthread_join(philostr->one_phil[c].tid, NULL);
		pthread_mutex_lock(&philostr->print_mutex);
		printf("Joining thread n: %lu with main\n", (unsigned long)philostr->one_phil[c].tid);
		pthread_mutex_unlock(&philostr->print_mutex);
		// free (tid[c]);
		c--;
	}
}