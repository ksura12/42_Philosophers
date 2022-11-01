/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:38:52 by ksura             #+#    #+#             */
/*   Updated: 2022/11/01 09:28:15 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void *living(void *data)
{
	(void)data;
	// pthread_mutex_lock()
	// printf("Thread %i is living\n", c);
	printf("Thread -x- is living\n");
	return (NULL);
}

void	philos(t_philos *philos)
{
	int c;
	pthread_t	tid[600];
	
	c = 0;
	while (philos->philo > c)
	{
		// tid[c] = malloc(sizeof(pthread_t));
		if (!pthread_create(&tid[c], NULL, &living, NULL))
		{
			print_time(philos);
			printf("created thread n: %lu\n", (unsigned long)tid[c]);
		}
		// pthread_create(&tid[c], NULL, living, NULL);
		// print_time(philos);
		// printf("created thread n: %lu\n", tid[c]);
		// pthread_join(tid, NULL);
		// printf("Joining thread n: %lu with main\n", (unsigned long)tid);
		// while (number of meals > 0)
		// 	creating thread
		// 	taking forks
		// 	sleeping
		// 	thinking
		// taking_fork();
		// printf("c:%i\n", c);
		c++;
	}
	c--;
	while (c >= 0)
	{
		print_time(philos);
		printf("before joining\n");
		pthread_join(tid[c], NULL);
		printf("Joining thread n: %lu with main\n", (unsigned long)tid[c]);
		// free (tid[c]);
		c--;
	}
}