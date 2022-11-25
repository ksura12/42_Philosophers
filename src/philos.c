/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:38:52 by ksura             #+#    #+#             */
/*   Updated: 2022/11/25 10:21:55 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// void taking_fork(t_philostr	*philostr);
// {

// }

// void *living(void *data)
// {
// 	// (void)data;
// 	t_onephil_l	*one_phil;

// 	one_phil = (t_onephil_l *)data;
	// printf("one_phil->fork_right->in_use: %i\n", one_phil->fork_right->in_use);
	// while(1)
	// {
	// 	printf("in while\n");
	// 	printf("in here\n");
	// 	pthread_mutex_lock(&one_phil->philostr->stop_mutex);
	// 	printf("in here1\n");
	// 	if (one_phil->philostr->stop == 1)
	// 	{
	// 		printf("in here2\n");
	// 		pthread_mutex_unlock(&one_phil->philostr->stop_mutex);
	// 		return(NULL);
	// 	}
	// 	printf("in here3\n");
	// 	pthread_mutex_unlock(&one_phil->philostr->stop_mutex);
	// 	printf("in here4\n");
	// 	printf("one_phil->fork_right->in_use: %i\n", one_phil->fork_right->in_use);
	// 	while (1)
	// 	{
	// 		pthread_mutex_lock(&one_phil->fork_right->fork_mutex);
	// 		// printf("in here5\n");
			
	// 		if (one_phil->fork_right->in_use == 0)
	// 		{
	// 			one_phil->fork_right->in_use = 1;
	// 			printf("in here6\n");
	// 			pthread_mutex_unlock(&one_phil->fork_right->fork_mutex);
	// 			printf("in here7\n");
	// 			pthread_mutex_lock(&one_phil->fork_left->fork_mutex);
	// 			printf("in here8\n");
	// 			if (one_phil->fork_left->in_use == 0)
	// 			{
	// 				printf("in here9\n");
	// 				pthread_mutex_lock(&one_phil->fork_right->fork_mutex);
	// 				printf("in here10\n");
	// 				pthread_mutex_lock(&one_phil->philostr->print_mutex);
	// 				printf("in here11\n");
	// 				pthread_mutex_lock(&one_phil->philostr->stop_mutex);
	// 				printf("in here12\n");
	// 				if (one_phil->philostr->stop == 1)
	// 				{
	// 					printf("in here13\n");
	// 					pthread_mutex_unlock(&one_phil->philostr->stop_mutex);
	// 					printf("in here^14\n");
	// 					return(NULL);
	// 				}
	// 				printf("in here4\n");
	// 				pthread_mutex_unlock(&one_phil->philostr->stop_mutex);
	// 				printf("in here4\n");
	// 				print_time_thread(one_phil);
	// 				printf("%i has taken a fork\n", one_phil->id_num);
	// 				print_time_thread(one_phil);
	// 				printf("%i is eating\n", one_phil->id_num);
	// 				pthread_mutex_unlock(&one_phil->philostr->print_mutex);
	// 				usleep(one_phil->philostr->time_to_eat * 1000);
	// 				one_phil->fork_right->in_use = 0;
	// 				pthread_mutex_unlock(&one_phil->fork_right->fork_mutex);
	// 				pthread_mutex_unlock(&one_phil->fork_left->fork_mutex);
	// 				one_phil->last_meal_eaten = get_time_ms();
	// 				break;
	// 			}
	// 			else
	// 			{
					
	// 				pthread_mutex_unlock(&one_phil->fork_left->fork_mutex);
	// 				usleep(1 * 1000);
	// 			}
	// 		}
	// 		else
	// 		{
	// 			// printf("in here end\n");
	// 			pthread_mutex_unlock(&one_phil->fork_right->fork_mutex);
	// 			usleep(10 * 1000);
	// 		}
	// 	}
	// 	// break;
	// }
// 	return (NULL);
// }

// void *supervising(void *data)
// {
// 	// (void)data;
// 	t_onephil_l	*supervi;
// 	int			i;

// 	supervi = (t_onephil_l *)data;
// 	pthread_mutex_lock(&supervi->philostr->stop_mutex);
// 	supervi->philostr->stop = 1;
// 	pthread_mutex_unlock(&supervi->philostr->stop_mutex);
// 	printf("supervi->philostr->philo_num%i\n",supervi->philostr->philo_num );
// 	while (1)
// 	{
// 		i = 0;
		
// 		while (i < supervi->philostr->philo_num)
// 		{
// 			printf("in while\n");
// 			printf("stop value %i\n", supervi->philostr->stop);
// 			printf("time to eat %i\n", supervi->philostr->time_to_eat);
// 			if (lifetime_counter(supervi) == 1)
// 			{
// 				printf("in if\n");
// 				return (NULL);
// 			}
// 			i++;
// 		}

// 	}
// 	return (NULL);
// }

// void	supervisor(t_onephil_l *philis)
// {
// 	t_onephil_l *super;
	
// 	super = philis;
// 	printf("super->philostr->philo_num: %i\n",super->philostr->philo_num );
// 	printf("id_num: %i\n",super->id_num );
// 	printf("fork use: %i\n",super->fork_right->in_use );
// 	printf("super->next: %i\n", (int)super->next );
// 	pthread_create(&super->tid, NULL, &supervising, &super);
// }

// void	philos(t_onephil_l *phili)
// {
// 	int c;
// 	t_onephil_l *tmp;

// 	tmp = phili;
// 	// philostr->counter = 0;
// 	// printf("timo to die:%i\n",phili->philostr->time_to_die );
// 	c = 0;
// 	while (tmp && tmp->philostr->philo_num > c)
// 	{
// 		tmp->id_num = c;
// 		pthread_create(&tmp->tid, NULL, &living, &tmp);
// 		tmp = tmp->next;
// 		c++;
// 	}
// 	tmp = phili;
// 	c = tmp->philostr->philo_num;
// 	while (c > 0)
// 	{
// 		// print_time(philostr);
// 		pthread_join(tmp->tid, NULL);
// 		pthread_mutex_lock(&phili->philostr->print_mutex);
// 		printf("Joining thread n: %lu with main\n", (unsigned long)tmp->tid);
// 		pthread_mutex_unlock(&phili->philostr->print_mutex);
// 		tmp = tmp->next;
// 		// free (tid[c]);
// 		c--;
// 	}
// }

// int	lifetime_counter(t_onephil_l	*one_phil)
// {
// 	time_t	time;
	
// 	time = get_time_ms();
// 	pthread_mutex_lock(&one_phil->last_meal_mutex);
// 	if (time - one_phil->last_meal_eaten >= one_phil->philostr->time_to_die)
// 	{
// 		pthread_mutex_unlock(&one_phil->last_meal_mutex);
// 		pthread_mutex_lock(&one_phil->philostr->stop_mutex);
// 		printf("stop value %i\n", one_phil->philostr->stop);
// 		one_phil->philostr->stop = 1;
// 		pthread_mutex_unlock(&one_phil->philostr->stop_mutex);
// 		pthread_mutex_lock(&one_phil->philostr->print_mutex);
// 		print_time_thread(one_phil);
// 		printf("%i died\n", one_phil->id_num);
// 		pthread_mutex_unlock(&one_phil->philostr->print_mutex);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&one_phil->last_meal_mutex);
// 	return (0);
// }