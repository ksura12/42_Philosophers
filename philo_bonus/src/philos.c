/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:38:52 by ksura             #+#    #+#             */
/*   Updated: 2022/11/27 18:07:42 by ksura            ###   ########.fr       */
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
	if (stop_checker(philo->philostr))
	{
		sem_wait(philo->philostr->forks);
		print_event(philo->philostr, philo->id_num, 1);
		sem_wait(philo->philostr->forks);
		print_event(philo->philostr, philo->id_num, 1);
		print_event(philo->philostr, philo->id_num, 2);
		sleeping(philo->philostr, philo->philostr->time_to_eat);
		sem_post(philo->philostr->forks);
		sem_post(philo->philostr->forks);
		sem_wait(philo->last_mealsem);
		philo->last_meal_eaten = get_time_ms();
		sem_post(philo->last_mealsem);
		philo->nb_meals += 1;
		if (philo->nb_meals == philo->philostr->c_eat)
			exit(0);
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
		sleep_routine(philo);
		think_routine(philo);
	}
	exit(0);
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
		philostr->philos[c]->pid = fork();
		if (philostr->philos[c]->pid == 0)
		{
			living((void *)philostr->philos[c]);
		}
		c++;
	}
	c = philostr->philo_num - 1;
	pthread_join(philostr->super, NULL);
	return ;
}
