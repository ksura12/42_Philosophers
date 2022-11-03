/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 11:32:09 by ksura             #+#    #+#             */
/*   Updated: 2022/11/03 15:35:27 by ksura            ###   ########.fr       */
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



typedef struct s_philostr
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				c_eat;
	int				stop;
	int				dead;
	time_t			time_start;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	stop_mutex;
} t_philostr;

typedef struct s_onephil
{
	int				id_num;
	time_t			last_meal_eaten;
	t_fork			*fork_left;
	t_fork			*fork_right;
	pthread_t		tid;
	t_philostr		*philostr;
	//t_onephil		*next;
} t_onephil;

//timing.c
time_t		get_time_ms(void);
void		print_time(t_philostr	*philos);
void		print_time_thread(t_onephil	*one_phil);

//init.c
t_onephil	**init(char **argv);

//philos.c
void		philos(t_onephil **phili);
int			lifetime_counter(t_onephil	*one_phil);

//main.c
int			is_digit(char **argv);
int			checker(int argc, char **argv);
int			main(int argc, char **argv, char **envp);




#endif