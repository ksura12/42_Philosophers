/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 11:32:09 by ksura             #+#    #+#             */
/*   Updated: 2022/08/02 11:05:07 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
	#define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_philos
{
	time_t	time_start;
	int		philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		c_eat;
} t_philos;

time_t		get_time_ms(void);
void		print_time(t_philos	*philos);
t_philos	*init(char **argv);
void	philos(t_philos *philos);




#endif