/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 11:30:09 by ksura             #+#    #+#             */
/*   Updated: 2022/07/30 12:00:06 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	checker(int argc, char **argv)
{
	(void)argv;
	if (argc < 5 || argc > 6)
	{
		write(2, "Please check input:\n./philosophers [1] [2] [3] [4] [[5]]\n", 58 );
	write(2, "1:	[number_of_philosophers]\
	\n2:	[time_to_die]\
	\n3:	[time_to_eat]\
	\n4:	[time_to_sleep]\
	\n[5:	[number_of_times_each_philosopher_must_eat]\n", 146 );
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)envp;
	checker(argc, argv);
	return (0);
}