/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 11:30:09 by ksura             #+#    #+#             */
/*   Updated: 2022/11/26 21:57:16 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv, char **envp)
{
	t_philostr	*philostr;

	(void)envp;
	if (!checker(argc, argv))
		return (0);
	philostr = init_all(argv);
	table(philostr);
	free_structs(philostr);
	return (0);
}
