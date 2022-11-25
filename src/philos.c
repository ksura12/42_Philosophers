/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:38:52 by ksura             #+#    #+#             */
/*   Updated: 2022/11/25 13:58:23 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// void taking_fork(t_philostr	*philostr);
// {

// }

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

void	*living(void *data)
{
	t_philos	*philo;
	t_fork		*fork_r;
	t_fork		*fork_l;

	philo = (t_philos *)data;
	fork_r = philo->philostr->forks[philo->id_num];
	if (philo->id_num == philo->philostr->philo_num)
		fork_r = philo->philostr->forks[0];
	fork_l = philo->philostr->forks[philo->id_num - 1];
	while(stop_checker(philo->philostr))
	{	
			pthread_mutex_lock(&fork_r->fork_mutex);
			if (fork_r->in_use == 0)
			{
				pthread_mutex_unlock(&fork_r->fork_mutex);
				while(1)
				{
					pthread_mutex_lock(&fork_r->fork_mutex);
					fork_r->in_use = 1;
					pthread_mutex_unlock(&fork_r->fork_mutex);
					pthread_mutex_lock(&fork_l->fork_mutex);
					if (fork_l->in_use == 0)
					{
						pthread_mutex_lock(&fork_r->fork_mutex);
						print_event(philo->philostr, philo->id_num, 1);
						print_event(philo->philostr, philo->id_num, 2);
						usleep(philo->philostr->time_to_eat * 1000);
						fork_r->in_use = 0;
						pthread_mutex_unlock(&fork_r->fork_mutex);
						pthread_mutex_unlock(&fork_l->fork_mutex);
						philo->last_meal_eaten = get_time_ms();
						break;
					}
					else
					{
						pthread_mutex_unlock(&fork_l->fork_mutex);
						usleep(1 * 1000);
					}
				}
			}
			else
			{
				pthread_mutex_unlock(&fork_r->fork_mutex);
				usleep(10 * 1000);
			}
	}
	return (NULL);
}

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

void	table(t_philostr *philostr)
{
	int			c;

	c = 0;
	philostr->time_start = get_time_ms();
	while (philostr->philo_num > c)
	{
		pthread_create(&philostr->philos[c]->tid, NULL, &living, philostr->philos[c]);
		c++;
	}
	c = philostr->philo_num - 1;
	while (c >= 0)
	{
		pthread_join(philostr->philos[c]->tid, NULL);
		pthread_mutex_lock(&philostr->print_mutex);
		printf("Joining thread n: %lu with main\n", (unsigned long)philostr->philos[c]->tid);
		pthread_mutex_unlock(&philostr->print_mutex);
		c--;
	}
}

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