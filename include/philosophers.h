/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 11:32:09 by ksura             #+#    #+#             */
/*   Updated: 2022/11/25 09:56:25 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_phils			**philos;
	t_fork			**forks;
} t_philostr;

typedef struct s_philos
{
	t_philostr			**philostr;
	int					id_num;
	time_t				last_meal_eaten;
	pthread_mutex_t		last_meal_mutex;
	t_fork				*fork_left;
	t_fork				*fork_right;
	pthread_t			tid;
	struct s_onephil_l	*next;
} t_philos;


//timing.c
time_t		get_time_ms(void);
void		print_time(t_philostr	*philos);
void		print_time_thread(t_onephil_l	*one_phil);

//init.c
t_onephil_l	*init(char **argv);
t_philos	**ft_philnew(t_philostr *philostr);
void		ft_philadd_back(t_onephil_l **lst, t_onephil_l *new);
t_onephil_l	*ft_phillast(t_onephil_l *lst);
t_philostr	*init_main_str(char **argv);
t_onephil_l	*init_table(char **argv);

//philos.c
void		philos(t_onephil_l *phili);
int			lifetime_counter(t_onephil_l	*one_phil);
void		supervisor(t_onephil_l *philis);

//main.c
int			is_digit(char **argv);
int			checker(int argc, char **argv);
int			main(int argc, char **argv, char **envp);




#endif