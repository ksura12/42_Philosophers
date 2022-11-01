/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:38:52 by ksura             #+#    #+#             */
/*   Updated: 2022/11/01 12:36:51 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// void taking_fork(t_philostr	*philostr);
// {
	
// }

void *living(void *data)
{
	// (void)data;
	t_philostr	*philostr;
	int			id_num;

	philostr = (t_philostr *)data;
	id_num = philostr->counter;
	
	// pthread_mutex_lock(&philostr->print_mutex);
	printf("Thread %lu is living\n", (unsigned long)philostr->tid[id_num]);
	print_time(philostr);
	printf("Philosopher %i is alive\n", id_num);
	// pthread_mutex_unlock(&philostr->print_mutex);
	
	// taking_fork(philostr);
	return (NULL);
}

void	philos(t_philostr *philostr)
{
	// int c;
	// pthread_t	tid[600];
	
	philostr->counter = 0;
	while (philostr->philo_num > philostr->counter)
	{
		// tid[c] = malloc(sizeof(pthread_t));
		if (!pthread_create(&philostr->tid[philostr->counter], NULL, &living, philostr))
		{
			// print_time(philostr);
			// pthread_mutex_lock(&philostr->print_mutex);
			printf("created thread n: %lu\n", (unsigned long)philostr->tid[philostr->counter]);
			// pthread_mutex_unlock(&philostr->print_mutex);
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
		// print_time(philostr);
		pthread_join(philostr->tid[philostr->counter], NULL);
		pthread_mutex_lock(&philostr->print_mutex);
		printf("Joining thread n: %lu with main\n", (unsigned long)philostr->tid[philostr->counter]);
		pthread_mutex_unlock(&philostr->print_mutex);
		// free (tid[c]);
		philostr->counter--;
	}
}