/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:38:52 by ksura             #+#    #+#             */
/*   Updated: 2022/11/01 14:27:21 by ksura            ###   ########.fr       */
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

t_philostr *init(char **argv)
{
	t_philostr		*philostr;
	int				c;
	int				c_next;
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
	c = philostr->philo_num;
	while (c >= 0)
	{
		pthread_mutex_init(&philostr->fork_mutex[c], NULL);
		c--;
	}
	c = philostr->philo_num;
	while (c >= 0)
	{
		if (c == 0)
			c_next = philostr->philo_num;
		else
			c_next = philostr->philo_num - 1;
		philostr->one_phil[c].time_start = philostr->time_start;
		philostr->one_phil[c].time_to_die = philostr->time_to_die;
		philostr->one_phil[c].time_to_eat = philostr->time_to_eat;
		philostr->one_phil[c].time_to_sleep = philostr->time_to_sleep;
		philostr->one_phil[c].print_mutex = philostr->print_mutex;
		philostr->one_phil[c].fork_mutex[0] = philostr->fork_mutex[c];
		philostr->one_phil[c].fork_mutex[1] = philostr->fork_mutex[c_next];
		c--;
	}
	return (philostr);
}