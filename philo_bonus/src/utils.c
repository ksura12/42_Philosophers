/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 11:30:09 by ksura             #+#    #+#             */
/*   Updated: 2022/11/27 18:21:45 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	is_digit(char **argv)
{
	int	i;
	int	count;

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
		write(2, "Please check input:\n./philosophers\
		 [1] [2] [3] [4] [[5]]\n", 58);
		write(2, "1:	number_of_philosophers\
		\n2:	time_to_die[ms]\
		\n3:	time_to_eat[ms]\
		\n4:	time_to_sleep[ms]\
		\n[5]:	number_of_times_each_philosopher_must_eat\n", 153);
		return (0);
	}
	return (1);
}

void	free_structs(t_philostr	*philostr)
{
	int	i;

	i = 0;
	while (i < philostr->philo_num)
	{
		sem_unlink("/last_mealsem");
		free(philostr->philos[i]);
		i++;
	}
	free(philostr->philos);
	sem_unlink("/printsem");
	sem_unlink("/stopsem");
	sem_unlink("/fullsem");
	sem_unlink("/forks");
	free(philostr);
}

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
