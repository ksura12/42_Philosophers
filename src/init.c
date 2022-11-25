/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:38:52 by ksura             #+#    #+#             */
/*   Updated: 2022/11/24 17:09:36 by ksura            ###   ########.fr       */
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

// t_onephil	*ft_table(t_philostr	*philostr)
// {
// 	t_onephil	*new_table;
// 	//char		*tmp;

// 	new_table = malloc(sizeof (t_onephil *));
// 	if (!new_table)
// 		return (NULL);
// 	new_table->fork_right = malloc(sizeof(t_fork));
// 	pthread_mutex_init(&new_table->fork_right->fork_mutex, NULL);
// 	new_table->philostr = philostr;
// 	return (new_table);
// }

t_onephil_l	*ft_phillast(t_onephil_l *lst)
{
	t_onephil_l	*last;

	if (!lst)
		return (NULL);
	last = lst;
	while (last->next)
		last = last->next;
	return (last);
}

void	ft_philadd_back(t_onephil_l **lst, t_onephil_l *new)
{
	if (!*lst)
	{
		*lst = new;
		printf("first of list\n");
	}
	else
	{
		ft_phillast(*lst)->next = new;
		printf("next in list list\n");
	}
}

t_onephil_l	*ft_philnew(t_philostr **philostr, int c)
{
	t_onephil_l	*new_list;

	new_list = malloc(sizeof (t_onephil_l	*));
	if (!new_list)
		return (NULL);
	new_list->philostr = philostr;
	new_list->id_num = c;
	new_list->last_meal_eaten = *philostr.time_start;
	pthread_mutex_init(&new_list->last_meal_mutex, NULL);
	new_list->fork_right = malloc(sizeof(t_fork));
	new_list->fork_right->in_use = 0;
	pthread_mutex_init(&new_list->fork_right->fork_mutex, NULL);
	new_list->next = NULL;
	
	return (new_list);
}

void	print_main_str(t_philostr	*main_str)
{
	printf("main_str Philo_num: %i\n", main_str->philo_num);
	printf("main_str->time_to_die: %i\n", main_str->time_to_die);
	printf("main_str->time_to_eat: %i\n", main_str->time_to_eat);
	printf("main_str->time_to_sleep: %i\n", main_str->time_to_sleep);
	printf("main_str->c_eat: %i\n", main_str->c_eat);
	printf("main_str->stop: %i\n", main_str->stop);
	printf("main_str->dead: %i\n", main_str->dead);
	printf("main_str->time_start: %li\n", main_str->time_start);
}

void	print_phil_str(t_onephil_l	*one_phil)
{
	printf("one_phil->main_str Philo_num: %i\n", one_phil->philostr->philo_num);
	printf("one_phil->main_str->time_to_die: %i\n", one_phil->philostr->time_to_die);
	printf("one_phil->main_str->time_to_eat: %i\n", one_phil->philostr->time_to_eat);
	printf("one_phil->main_str->time_to_sleep: %i\n", one_phil->philostr->time_to_sleep);
	printf("one_phil->main_str->c_eat: %i\n", one_phil->philostr->c_eat);
	printf("one_phil->main_str->stop: %i\n", one_phil->philostr->stop);
	printf("one_phil->main_str->dead: %i\n", one_phil->philostr->dead);
	printf("one_phil->id_num: %i\n", one_phil->id_num);
	printf("one_phil->last_meal_eaten: %li\n", one_phil->last_meal_eaten);
	printf("one_phil->fork_right->in_use: %i\n", one_phil->fork_right->in_use);
	// printf("main_str->time_start: %li\n", one_phil->philostr->time_start);
	// printf("main_str->time_start: %li\n", one_phil->philostr->time_start);
	// printf("main_str->time_start: %li\n", one_phil->philostr->time_start);
}

/**
 * @brief initialises the main structure
 * includes starting time of simulation
 * 
 * @param argv 
 * @return t_philostr* 
 */
t_philostr **init_main_str(char **argv)
{
	t_philostr	*main_str;
	
	main_str = malloc(sizeof(t_philostr *));
	if (!main_str)
		return (NULL);
	main_str->philo_num = ft_atoi(argv[1]);
	main_str->time_to_die = ft_atoi(argv[2]);
	main_str->time_to_eat = ft_atoi(argv[3]);
	main_str->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		main_str->c_eat = ft_atoi(argv[5]);
	else
		main_str->c_eat = -1;
	main_str->stop = 0;
	main_str->dead = 0;
	pthread_mutex_init(&main_str->print_mutex, NULL);
	pthread_mutex_init(&main_str->dead_mutex, NULL);
	pthread_mutex_init(&main_str->stop_mutex, NULL);
	main_str->time_start = get_time_ms();
	return (&main_str);
}

/**
 * @brief initialises a structure for each philosopher
 * 	allocates for it
 * 	allocates for the forks
 * 	giving values for each component of the structure
 * 
 * @param argv 
 * @return t_onephil_l* 
 */
t_onephil_l *init_table(char **argv)
{
	t_philostr	**main_str;
	t_onephil_l	*table;
	t_onephil_l	*seats;
	int			c;

	main_str = init_main_str(argv);
	c = 1;
	table = NULL;
	while (c <= main_str->philo_num)
	{
		seats = ft_philnew(main_str, c);
		ft_philadd_back(&table, seats);
		print_phil_str(seats);
		c++;
		
	}
	// print_phil_str(table);
	return (table);
}

// t_onephil_l *init(char **argv)
// {
// 	t_philostr	*philostr;
// 	int			c;
// 	t_onephil_l	*one_phil;
// 	t_onephil_l	*tmp;
	
// 	one_phil = NULL;
// 	philostr = malloc(sizeof(t_philostr));
// 	if (philostr == NULL)
// 		return (NULL);
// 	philostr->philo_num = ft_atoi(argv[1]);
// 	philostr->time_to_die = ft_atoi(argv[2]);
// 	philostr->time_to_eat = ft_atoi(argv[3]);
// 	philostr->time_to_sleep = ft_atoi(argv[4]);
// 	if (argv[5])
// 		philostr->c_eat = ft_atoi(argv[5]);
// 	else
// 		philostr->c_eat = -1;
// 	pthread_mutex_init(&philostr->print_mutex, NULL);
// 	pthread_mutex_init(&philostr->dead_mutex, NULL);
// 	pthread_mutex_init(&philostr->stop_mutex, NULL);
// 	// pthread_mutex_lock(&philostr->stop_mutex);
// 	philostr->stop = 0;
// 	// pthread_mutex_unlock(&philostr->stop_mutex);
// 	// pthread_mutex_lock(&philostr->dead_mutex);
// 	philostr->dead = 0;
// 	// pthread_mutex_unlock(&philostr->dead_mutex);
// 	c = philostr->philo_num;
// 	philostr->time_start = get_time_ms();
// 	while (c > 0)
// 	{	
// 		// printf("philo_num: %i\n", c);
// 		if (c == philostr->philo_num)
// 		{
// 			one_phil = ft_philnew(philostr, c);
// 				printf("while: one_phil->fork_right->in_use: %i\n", one_phil->fork_right->in_use);
// 				printf("while: one_phil->id: %i\n", one_phil->id_num);
// 		}
			
			
// 		else
// 		{
// 			tmp = ft_philnew(philostr, c);
// 			ft_philadd_back(&one_phil, tmp);
// 				printf("while: tmp->fork_right->in_use: %i\n", tmp->fork_right->in_use);
// 				printf("while: tmp->id: %i\n", tmp->id_num);
// 				printf("else: one_phil->fork_right->in_use: %i\n", one_phil->fork_right->in_use);
// 				printf("else: one_phil->id: %i\n", one_phil->id_num);
// 		}
// 		c--;
// 	}
// 	c = philostr->philo_num;
// 	tmp = one_phil;
// 	printf("tmp =one: tmp->fork_right->in_use: %i\n", tmp->fork_right->in_use);
// 	printf("tmp =one: tmp->id: %i\n", tmp->id_num);
// 	printf("tmp =one: one_phil->fork_right->in_use: %i\n", one_phil->fork_right->in_use);
// 	printf("tmp =one: one_phil->id: %i\n", one_phil->id_num);
// 	printf("philo id: %i\n", one_phil->id_num);
// 	while (c > 0)
// 	{
// 		if (tmp->next != NULL)
// 		{
// 				printf("looping: tmp->fork_right->in_use: %i\n", tmp->fork_right->in_use);
// 				printf("looping: tmp->id: %i\n", tmp->id_num);
// 			// pthread_mutex_lock(&tmp->next->fork_right->fork_mutex);
// 			// tmp->fork_left = &tmp->next->fork_right;
// 			// pthread_mutex_unlock(&tmp->next->fork_right->fork_mutex);
// 			tmp = tmp->next;
// 		}
// 		c--;
// 	}
// 	if (philostr->philo_num > 1)
// 		tmp->next = one_phil;
// 	return (one_phil);
// }