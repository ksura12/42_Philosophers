/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:38:52 by ksura             #+#    #+#             */
/*   Updated: 2022/11/03 12:32:47 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_atoi(const char *str)
{
	long int	n;
	int			m;

	n = 0;
	m = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			m = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		n = n * 10 + *str - '0';
		str++;
		if (n > 2147483647 && m == 1)
			return (-1);
		else if (n > 2147483648 && m == -1)
			return (0);
	}		
	return (n * m);
}

t_onephil **init(char **argv)
{
	t_philostr		*philostr;
	int				c;
	int				c_next;
	t_onephil		*one_phil[600];

	one_phil = malloc(sizeof(t_onephil *) * 600);
	philostr = malloc(sizeof(t_philostr));
	if(!philostr)
		exit(1);
	philostr->time_start = get_time_ms();
	philostr->philo_num = ft_atoi(argv[1]);
	philostr->time_to_die = ft_atoi(argv[2]);
	philostr->time_to_eat = ft_atoi(argv[3]);
	philostr->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philostr->c_eat = ft_atoi(argv[5]);
	else
		philostr->c_eat = -1;
	pthread_mutex_init(&philostr->print_mutex, NULL);
	pthread_mutex_init(&philostr->dead_mutex, NULL);
	pthread_mutex_init(&philostr->stop_mutex, NULL);
	pthread_mutex_lock(&philostr->stop_mutex);
	philostr->stop = 0;
	pthread_mutex_unlock(&philostr->stop_mutex);
	pthread_mutex_lock(&philostr->dead_mutex);
	philostr->dead = 0;
	pthread_mutex_unlock(&philostr->dead_mutex);
	c = philostr->philo_num;
	while (c >= 0)
	{
		one_phil[c] = malloc(sizeof(t_onephil *));
		one_phil[c]->fork[0] = malloc(sizeof(t_fork));
		pthread_mutex_init(&one_phil[c]->fork[0]->fork_mutex, NULL);
		one_phil[c]->fork[c]->in_use = 0;
		c--;
	}
	c = philostr->philo_num;
	
	while (c >= 0)
	{
		if (c == 0)
			c_next = philostr->philo_num;
		else
			c_next = philostr->philo_num - 1;
		one_phil[c]->fork[1]->fork_mutex = one_phil[c_next]->fork[0]->fork_mutex;
		one_phil[c]->philostr = philostr;
		c--;
	}
	return (one_phil);
}