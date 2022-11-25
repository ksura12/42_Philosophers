/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:38:52 by ksura             #+#    #+#             */
/*   Updated: 2022/11/24 19:57:08 by ksura@student.42 ###   ########.fr       */
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

t_philos	**ft_philnew(t_philostr *philostr)
{
	t_philos	**philos;
	int			i;

	philos = malloc(sizeof (t_philos) * philostr->philo_num);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < philostr->philo_num)
	{
		philos[i] = malloc(sizeof(t_philos));
		philos[i]->id_num = i + 1;
		philos[i]->philostr = philostr;
		philos[i]->last_meal_eaten = 0;
		pthread_mutex_init(&philos[i]->last_meal_mutex, NULL);
	}
	return (philos);
}

t_philostr	*init_all(char **argv)
{
	t_philostr	*philostr;
	int			c;
	t_philos	**one_phil;
	
	philostr = malloc(sizeof(t_philostr));
	if (philostr == NULL)
		return (NULL);
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
	pthread_mutex_init(&philostr->dead_mutex, NULL);
	pthread_mutex_init(&philostr->stop_mutex, NULL);
	pthread_mutex_lock(&philostr->stop_mutex);
	philostr->stop = 0;
	pthread_mutex_unlock(&philostr->stop_mutex);
	pthread_mutex_lock(&philostr->dead_mutex);
	philostr->dead = 0;
	pthread_mutex_unlock(&philostr->dead_mutex);
	one_phil = ft_philnew(philostr);

}

// t_onephil_l *init(char **argv)
// {
// 	t_philostr	*philostr;
// 	int			c;
// 	// int			c_next;
// 	t_onephil_l	*one_phil;
// 	t_onephil_l	*tmp;
// 	//t_onephil	*supervis;
// 	// t_fork		**fork;

// 	// one_phil = malloc(sizeof(t_onephil *) * 601);
// 	// if (one_phil == NULL)
// 	// 	return (NULL);
// 	one_phil = NULL;
// 	philostr = malloc(sizeof(t_philostr));
// 	if (philostr == NULL)
// 		return (NULL);
// 	philostr->time_start = get_time_ms();
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
// 	pthread_mutex_lock(&philostr->stop_mutex);
// 	philostr->stop = 0;
// 	pthread_mutex_unlock(&philostr->stop_mutex);
// 	pthread_mutex_lock(&philostr->dead_mutex);
// 	philostr->dead = 0;
// 	pthread_mutex_unlock(&philostr->dead_mutex);
// 	c = philostr->philo_num;
// 	while (c > 0)
// 	{	
// 		printf("philo_num: %i\n", c);
// 		if (c == philostr->philo_num)
// 			one_phil = ft_philnew(philostr, c);
// 		else
// 		{
// 			tmp = ft_philnew(philostr, c);
// 			ft_philadd_back(&one_phil, tmp);
// 		}
// 		c--;
// 		// one_phil[c].fork_right = malloc(sizeof(t_fork *));
// 		// pthread_mutex_init(&one_phil[c].fork_right->fork_mutex, NULL);
// 		// one_phil[c].fork_right->in_use = 0;
// 		// c--;
// 	}
// 	c = philostr->philo_num;
// 	tmp = one_phil;
// 	while (c > 0)
// 	{
// 		if (c == 0 && philostr->philo_num > 1)
// 			tmp->next = one_phil;
// 		if (tmp->next != NULL)
// 		{
// 			printf("philo_num before lock: %i\n", c);
// 			pthread_mutex_lock(&tmp->next->fork_right->fork_mutex);
// 			tmp->fork_left = tmp->next->fork_right;
// 			pthread_mutex_unlock(&tmp->next->fork_right->fork_mutex);
// 			tmp = tmp->next;
// 		}
// 		c--;
// 	}
// 	return (one_phil);
// }