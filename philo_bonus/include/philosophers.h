/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 11:32:09 by ksura             #+#    #+#             */
/*   Updated: 2022/11/27 17:55:50 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
#	include <semaphore.h>

////++++struct definitions++++////

typedef struct s_philos	t_philos;

typedef struct s_philostr
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				c_eat;
	int				stop;
	int				full;
	time_t			time_start;
	t_philos		**philos;
	sem_t			*forks;
	sem_t			*printsem;
	sem_t			*fullsem;
	sem_t			*stopsem;
	pthread_t		super;
}	t_philostr;

typedef struct s_philos
{
	t_philostr			*philostr;
	int					id_num;
	int					nb_meals;
	time_t				last_meal_eaten;
	sem_t				*last_mealsem;
	pid_t				pid;
}	t_philos;

////++++function declarations++++////

//timing.c
time_t		get_time_ms(void);
void		print_time(t_philostr	*philostr);
void		sleeping(t_philostr *philostr, time_t sleeping_time);

//init.c
t_philos	**ft_philnew(t_philostr *philostr);
t_philostr	*init_main_str(char **argv);
t_philostr	*init_all(char **argv);

//philos.c
void		table(t_philostr *philostr);
void		*living(void *data);
void		eat_routine(t_philos *philo);
void		sleep_routine(t_philos *philo);
void		think_routine(t_philos *philo);

//main.c
int			main(int argc, char **argv, char **envp);

//printing.c
void		print_event(t_philostr *pstr, int phil_id, int event);

//utils.c
int			is_digit(char **argv);
int			checker(int argc, char **argv);
void		free_structs(t_philostr	*philostr);
int			ft_atoi(const char *str);

//supervisor.c
int			stop_checker(t_philostr *philostr);
int			lifetime_counter(t_philos	*one_phil);
void		*supervising(void *data);
int			check_full(t_philostr *philostr);

#endif