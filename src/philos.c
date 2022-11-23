/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:38:52 by ksura             #+#    #+#             */
/*   Updated: 2022/11/23 12:52:11 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// void taking_fork(t_philostr	*philostr);
// {

// }

void *living(void *data)
{
	// (void)data;
	t_onephil_l	*one_phil;

	one_phil = (t_onephil_l *)data;

	// pthread_mutex_lock(one_phil->print_mutex);
	// // printf("Thread %lu is living\n", (unsigned long)one_phil->tid);
	// print_time_thread(one_phil);
	// printf("Philosopher %i is alive\n", one_phil->id_num);
	// pthread_mutex_unlock(one_phil->print_mutex);
	while(1)
	{
		printf("in while\n");
		printf("in here\n");
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
	t_onephil_l	*supervi;
	int			i;

	supervi = (t_onephil_l *)data;

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
		// printf("timo to die:%i\n",supervi->philostr->time_to_die );
		while (i < supervi->philostr->philo_num)
		{
			printf("in while\n");
			printf("stop value %i\n", supervi->philostr->stop);
			printf("time to eat %i\n", supervi->philostr->time_to_eat);
			if (lifetime_counter(supervi) == 1)
			{
				printf("in if\n");
				return (NULL);
			}
			i++;
		}

	}
	return (NULL);
}

void	supervisor(t_onephil_l *philis)
{
	t_onephil_l *super;
	
	super = ft_philnew(philis->philostr, -1);
	pthread_create(&super->tid, NULL, &supervising, &super);
}

void	philos(t_onephil_l *phili)
{
	int c;
	t_onephil_l *tmp;
	
	// pthread_t	tid[600];
	tmp = phili;
	// philostr->counter = 0;
	// printf("timo to die:%i\n",phili->philostr->time_to_die );
	c = 0;
	while (tmp && tmp->philostr->philo_num > c)
	{
		tmp->id_num = c;
		pthread_create(&tmp->tid, NULL, &living, &tmp);
		tmp = tmp->next;
		c++;
	}
	tmp = phili;
	c = tmp->philostr->philo_num;
	while (c > 0)
	{
		// print_time(philostr);
		pthread_join(tmp->tid, NULL);
		pthread_mutex_lock(&phili->philostr->print_mutex);
		printf("Joining thread n: %lu with main\n", (unsigned long)tmp->tid);
		pthread_mutex_unlock(&phili->philostr->print_mutex);
		tmp = tmp->next;
		// free (tid[c]);
		c--;
	}
}

int	lifetime_counter(t_onephil_l	*one_phil)
{
	time_t	time;
	
	time = get_time_ms();
	pthread_mutex_lock(&one_phil->last_meal_mutex);
	if (time - one_phil->last_meal_eaten >= one_phil->philostr->time_to_die)
	{
		pthread_mutex_unlock(&one_phil->last_meal_mutex);
		pthread_mutex_lock(&one_phil->philostr->stop_mutex);
		printf("stop value %i\n", one_phil->philostr->stop);
		one_phil->philostr->stop = 1;
		pthread_mutex_unlock(&one_phil->philostr->stop_mutex);
		pthread_mutex_lock(&one_phil->philostr->print_mutex);
		print_time_thread(one_phil);
		printf("%i died\n", one_phil->id_num);
		pthread_mutex_unlock(&one_phil->philostr->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&one_phil->last_meal_mutex);
	return (0);
}