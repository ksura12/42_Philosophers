/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:38:52 by ksura             #+#    #+#             */
/*   Updated: 2022/11/26 22:33:18 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/**
 * @brief eating routine of each philosopher
 * telling which forks to use
 * taking forks one by one
 * 
 * @param philo 
 */
void	eat_routine(t_philos *philo)
{
	t_fork		*fork_r;
	t_fork		*fork_l;

	if (philo->id_num == philo->philostr->philo_num)
		fork_r = philo->philostr->forks[0];
	else
		fork_r = philo->philostr->forks[philo->id_num];
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

/**
 * @brief routine funtion of the philos in which they
 * eat, sleep and think
 * philos with odd numbered id's start their life by thinking
 * 
 * @param data 
 * @return void* 
 */
void	*living(void *data)
{
	t_philos	*philo;

	philo = (t_philos *)data;
	if (philo->philostr->philo_num == 1)
		return (NULL);
	if (philo->id_num % 2)
		think_routine(philo);
	while (stop_checker(philo->philostr))
	{
		eat_routine(philo);
		if (philo->nb_meals == philo->philostr->c_eat)
		{
			pthread_mutex_lock(&philo->philostr->full_mutex);
			philo->philostr->full += 1;
			pthread_mutex_unlock(&philo->philostr->full_mutex);
			return (NULL);
		}
		sleep_routine(philo);
		think_routine(philo);
	}
	return (NULL);
}

/**
 * @brief starts the simulation by getting the start time
 * and creating threads for the philosophers and one extra
 * for the supervisor
 * joins all threads at the end of simulation
 * 
 * @param philostr 
 */
void	table(t_philostr *philostr)
{
	int			c;

	c = 0;
	philostr->time_start = get_time_ms();
	pthread_create(&philostr->super, NULL, &supervising, philostr);
	while (philostr->philo_num > c)
	{
		pthread_create(&philostr->philos[c]->tid, NULL, \
		&living, philostr->philos[c]);
		c++;
	}
	c = philostr->philo_num - 1;
	while (c >= 0)
	{
		pthread_join(philostr->philos[c]->tid, NULL);
		c--;
	}
	pthread_join(philostr->super, NULL);
	return ;
}
