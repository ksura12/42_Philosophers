/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 11:32:09 by ksura             #+#    #+#             */
/*   Updated: 2022/11/01 11:52:01 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
	#define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_philostr
{
	time_t			time_start;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				c_eat;
	int				counter;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	fork_mutex[600];
	pthread_t		tid[600];
} t_philostr;

time_t		get_time_ms(void);
void		print_time(t_philostr	*philos);
t_philostr	*init(char **argv);
void	philos(t_philostr *philos);




#endif