/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:38:52 by ksura             #+#    #+#             */
/*   Updated: 2022/11/01 17:00:25 by ksura            ###   ########.fr       */
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
	
	pthread_mutex_lock(&one_phil->print_mutex);
	// printf("Thread %lu is living\n", (unsigned long)one_phil->tid);
	print_time_thread(one_phil);
	printf("Philosopher %i is alive\n", one_phil->id_num);
	pthread_mutex_unlock(&one_phil->print_mutex);
	
	// taking_fork(philostr);
	return (NULL);
}

void *supervising(void *data)
{
	// (void)data;
	t_onephil	*one_phil;
	int			dead;

	one_phil = (t_onephil *)data;
	
	pthread_mutex_lock(&one_phil->print_mutex);
	// printf("Thread %lu is living\n", (unsigned long)one_phil->tid);
	print_time_thread(one_phil);
	printf("Supervisoris alive\n");
	pthread_mutex_unlock(&one_phil->print_mutex);
	pthread_mutex_lock(&one_phil->dead_mutex);
	one_phil->stop = 0;
	dead = 1;
	one_phil->dead = &dead;
	while (1)
	{
		if (*one_phil->dead == 1)
		{
			one_phil->stop = 1;
			break;
		}
	}

	pthread_mutex_unlock(&one_phil->dead_mutex);
	
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