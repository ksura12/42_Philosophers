/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 11:30:09 by ksura             #+#    #+#             */
/*   Updated: 2022/11/22 15:24:02 by ksura            ###   ########.fr       */
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


int	main(int argc, char **argv, char **envp)
{
	t_onephil_l	*one_phil;
	(void)envp;
	if (!checker(argc, argv))
		return (0);
	one_phil = init(argv);
	printf("start time: ");
	print_time(one_phil->philostr);
	printf("\n");
	// printf("\n");

	// print_time(philos_struc);
	philos(one_phil);
	//Free forks
	//while()
	//	free(one_phil[0]->fork)
	
	//FREeing the only allocated philostr
	free (one_phil->philostr);
	free (one_phil);
	
	return (0);
}