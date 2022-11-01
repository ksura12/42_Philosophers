/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:38:52 by ksura             #+#    #+#             */
/*   Updated: 2022/08/02 10:30:58 by ksura            ###   ########.fr       */
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

t_philos *init(char **argv)
{
	t_philos		*philos;
	
	philos = malloc(sizeof(t_philos));
	if(!philos)
		exit(1);
	philos->time_start = get_time_ms();
	philos->philo = ft_atoi(argv[1]);
	philos->time_to_die = ft_atoi(argv[2]);
	philos->time_to_eat = ft_atoi(argv[3]);
	philos->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philos->c_eat = ft_atoi(argv[5]);
	else
		philos->c_eat = -1;
	// pthread_mutex_init(philos->mutex_wright, NULL);
	return (philos);
}