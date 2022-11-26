/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 11:30:09 by ksura             #+#    #+#             */
/*   Updated: 2022/11/26 21:52:38 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"


int	is_digit(char **argv)
{
	int i;
	int count;

	count = 1;
	while (argv[count])
	{
		i = 0;
		while (argv[count][i])
		{
			if (argv[count][i] >= 48 && argv[count][i] <= 57)
			i++;
			else
			return (0);
		}
		count++;
	}
	return (1);
}

int	checker(int argc, char **argv)
{
	(void)argv;
	if (argc < 5 || argc > 6 || !is_digit(argv))
	{
		write(2, "Please check input:\n./philosophers [1] [2] [3] [4] [[5]]\n", 58 );
		write(2, "1:	number_of_philosophers\
		\n2:	time_to_die[ms]\
		\n3:	time_to_eat[ms]\
		\n4:	time_to_sleep[ms]\
		\n[5]:	number_of_times_each_philosopher_must_eat\n", 153 );
		return (0);
	}
	return(1);
}

void	free_structs(t_philostr	*philostr)
{
	int i;

	i = 0;
	while (i < philostr->philo_num)
	{
	
		pthread_mutex_destroy(&philostr->forks[i]->fork_mutex);
		free(philostr->forks[i]);
		pthread_mutex_destroy(&philostr->philos[i]->last_meal_mutex);
		free(philostr->philos[i]);
		i++;
	}
	free(philostr->forks);
	free(philostr->philos);
	pthread_mutex_destroy(&philostr->print_mutex);
	pthread_mutex_destroy(&philostr->stop_mutex);
	pthread_mutex_destroy(&philostr->full_mutex);
	free(philostr);
}

int	main(int argc, char **argv, char **envp)
{
	t_philostr	*philostr;
	
	(void)envp;
	if (!checker(argc, argv))
		return (0);
	philostr = init_all(argv);
	// print_main_str(philostr);
	table(philostr);
	free_structs(philostr);
	
	return (0);
}