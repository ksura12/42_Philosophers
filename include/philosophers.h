/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 11:32:09 by ksura             #+#    #+#             */
/*   Updated: 2022/11/25 13:17:50 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_philos t_philos;

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
	int				in_use;
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
	t_philos		**philos;
	t_fork			**forks;
} t_philostr;

typedef struct s_philos
{
	t_philostr			*philostr;
	int					id_num;
	time_t				last_meal_eaten;
	pthread_mutex_t		last_meal_mutex;
	pthread_t			tid;
} t_philos;


//timing.c
time_t		get_time_ms(void);
void		print_time(t_philostr	*philostr);
// void		print_time_thread(t_onephil_l	*one_phil);

//init.c
// t_onephil_l	*init(char **argv);
t_philos	**ft_philnew(t_philostr *philostr);
t_fork		**ft_forks(t_philostr *philostr);
t_philostr	*init_main_str(char **argv);
// t_onephil_l	*init_table(char **argv);
t_philostr	*init_all(char **argv);
void	print_main_str(t_philostr	*main_str);

//philos.c
void	table(t_philostr *philostr);
void	*living(void *data);
int		stop_checker(t_philostr *philostr);
// void		philos(t_onephil_l *phili);
// int			lifetime_counter(t_onephil_l	*one_phil);
// void		supervisor(t_onephil_l *philis);

//main.c
int			is_digit(char **argv);
int			checker(int argc, char **argv);
int			main(int argc, char **argv, char **envp);

//printing.c
void	print_event(t_philostr *pstr, int phil_id, int event);


#endif