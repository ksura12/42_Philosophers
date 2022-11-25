/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:38:52 by ksura             #+#    #+#             */
/*   Updated: 2022/11/25 19:09:41 by ksura            ###   ########.fr       */
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

// int	taking_fork_l(t_philos *philo, t_fork *fork_r, t_fork *fork_l)
// {
// 	pthread_mutex_lock(&fork_r->fork_mutex);
// 	fork_r->in_use = 1;
// 	pthread_mutex_unlock(&fork_r->fork_mutex);
// 	pthread_mutex_lock(&fork_l->fork_mutex);
// 	if (fork_l->in_use == 0)
// 	{
// 		pthread_mutex_lock(&fork_r->fork_mutex);
// 		print_event(philo->philostr, philo->id_num, 1);
// 		print_event(philo->philostr, philo->id_num, 2);
// 		sleeping(philo->philostr, philo->philostr->time_to_eat);
// 		// usleep(philo->philostr->time_to_eat * 1000);
// 		fork_r->in_use = 0;
// 		pthread_mutex_unlock(&fork_r->fork_mutex);
// 		pthread_mutex_unlock(&fork_l->fork_mutex);
// 		pthread_mutex_lock(&philo->last_meal_mutex);
// 		philo->last_meal_eaten = get_time_ms();
// 		pthread_mutex_unlock(&philo->last_meal_mutex);
// 		return (0);
// 	}
// 	else
// 	{
// 		pthread_mutex_unlock(&fork_l->fork_mutex);
// 		usleep(1 * 1000);
// 		return (1);
// 	}
// }

// void	eating(t_philos *philo)
// {
// 	t_fork		*fork_r;
// 	t_fork		*fork_l;
	
// 	fork_r = philo->philostr->forks[philo->id_num];
// 	if (philo->id_num == philo->philostr->philo_num)
// 		fork_r = philo->philostr->forks[0];
// 	fork_l = philo->philostr->forks[philo->id_num - 1];
// 	while(stop_checker(philo->philostr))
// 	{	
// 			pthread_mutex_lock(&fork_r->fork_mutex);
// 			if (fork_r->in_use == 0)
// 			{
// 				pthread_mutex_unlock(&fork_r->fork_mutex);
// 				while(stop_checker(philo->philostr))
// 				{
// 					if (!taking_fork_l(philo, fork_r, fork_l))
// 						return;
// 				}
// 			}
// 			else
// 			{
// 				pthread_mutex_unlock(&fork_r->fork_mutex);
// 				usleep(1 * 1000);
// 			}
// 	}
// }

void	eat_routine(t_philos *philo)
{
	t_fork		*fork_r;
	t_fork		*fork_l;
	
	fork_r = philo->philostr->forks[philo->id_num];
	if (philo->id_num == philo->philostr->philo_num)
		fork_r = philo->philostr->forks[0];
	fork_l = philo->philostr->forks[philo->id_num - 1];
	if (stop_checker(philo->philostr))
	{
		pthread_mutex_lock(&fork_r->fork_mutex);
		print_event(philo->philostr, philo->id_num, 1);
		pthread_mutex_lock(&fork_l->fork_mutex);
		print_event(philo->philostr, philo->id_num, 1);
		print_event(philo->philostr, philo->id_num, 2);
		sleeping(philo->philostr, philo->philostr->time_to_eat);
		pthread_mutex_unlock(&fork_r->fork_mutex);
		pthread_mutex_unlock(&fork_l->fork_mutex);
		pthread_mutex_lock(&philo->last_meal_mutex);
		philo->last_meal_eaten = get_time_ms();
		pthread_mutex_unlock(&philo->last_meal_mutex);
		philo->nb_meals += 1;
		// if (philo->nb_meals == philo->philostr->c_eat)
	}
	
}

void	think_routine(t_philos *philo)
{
	print_event(philo->philostr, philo->id_num, 4);
	sleeping(philo->philostr, philo->philostr->time_to_think);
	return ;
}

void	sleep_routine(t_philos *philo)
{
	print_event(philo->philostr, philo->id_num, 3);
	sleeping(philo->philostr, philo->philostr->time_to_sleep);
	return ;
}

void	*living(void *data)
{
	t_philos	*philo;

	philo = (t_philos *)data;
	// if (philo->id_num % 2)
	// 	think(philo);
	while(stop_checker(philo->philostr))
	{
		eat_routine(philo);
		sleep_routine(philo);
		think_routine(philo);
	}
	return (NULL);
}

void *supervising(void *data)
{
	// (void)data;
	t_philostr	*philostr;
	int			i;

	philostr = (t_philostr *)data;
	while (1)
	{
		i = 0;
		while (i < philostr->philo_num)
		{
			if (lifetime_counter(philostr->philos[i]) == 1)
			{
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

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
	pthread_create(&philostr->super, NULL, &supervising, philostr);
	while (philostr->philo_num > c)
	{
		pthread_create(&philostr->philos[c]->tid, NULL, &living, philostr->philos[c]);
		c++;
	}
	c = philostr->philo_num - 1;
	while (c >= 0)
	{
		pthread_join(philostr->philos[c]->tid, NULL);
		c--;
	}
	pthread_join(philostr->super, NULL);
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