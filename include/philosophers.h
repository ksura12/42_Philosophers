/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 11:32:09 by ksura             #+#    #+#             */
/*   Updated: 2022/11/02 10:34:53 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
	#define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
	int		in_use;
}	t_fork;

typedef struct s_onephil
{
	int				id_num;
	
	pthread_t		tid;
	time_t			time_start;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				c_eat;
	int				*stop;
	int				*dead;
	pthread_mutex_t	*print_mutex;
	t_fork			*fork[2];
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*stop_mutex;
} t_onephil;

typedef struct s_philostr
{
	time_t			time_start;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				c_eat;
	// int				counter;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	stop_mutex;
	t_fork			*fork[600];
	t_onephil		one_phil[600];
	int				stop;
	int				dead;
} t_philostr;

time_t		get_time_ms(void);
void		print_time(t_philostr	*philos);
void	print_time_thread(t_onephil	*one_phil);
t_philostr	*init(char **argv);
void	philos(t_philostr *philos);




#endif