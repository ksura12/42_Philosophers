/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:38:52 by ksura             #+#    #+#             */
/*   Updated: 2022/11/01 10:04:48 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void *living(void *data)
{
	// (void)data;
	t_philos	*philostr;

	philostr = (t_philos *)data;
	// pthread_mutex_lock()
	printf("Thread %lu is living\n", (unsigned long)philostr->tid[philostr->counter]);
	// printf("Thread -x- is living\n");
	return (NULL);
}

void	philos(t_philos *philostr)
{
	// int c;
	// pthread_t	tid[600];
	
	philostr->counter = 0;
	while (philostr->philo > philostr->counter)
	{
		// tid[c] = malloc(sizeof(pthread_t));
		if (!pthread_create(&philostr->tid[philostr->counter], NULL, &living, philostr))
		{
			print_time(philostr);
			printf("created thread n: %lu\n", (unsigned long)philostr->tid[philostr->counter]);
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
		philostr->counter++;
	}
	philostr->counter--;
	while (philostr->counter >= 0)
	{
		print_time(philostr);
		printf("before joining\n");
		pthread_join(philostr->tid[philostr->counter], NULL);
		printf("Joining thread n: %lu with main\n", (unsigned long)philostr->tid[philostr->counter]);
		// free (tid[c]);
		philostr->counter--;
	}
}