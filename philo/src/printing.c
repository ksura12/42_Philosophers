/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:08:14 by ksura             #+#    #+#             */
/*   Updated: 2022/11/26 22:18:58 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/**
 * @brief prints all events, check stop mutex and blocks print mutex
 * 1 - taking fork
 * 2 - eating
 * 3 - sleeping
 * 4 - thinking
 * 5 - dead
 * 
 * @param pstr 
 * @param phil 
 * @param event 
 */
void	print_event(t_philostr *pstr, int phil_id, int event)
{
	if (stop_checker(pstr))
	{
		pthread_mutex_lock(&pstr->print_mutex);
		if ((event > 0) && (event < 6))
			print_time(pstr);
		if (event == 1)
			printf("	%i has taken a fork\n", phil_id);
		else if (event == 2)
			printf("	%i is eating\n", phil_id);
		else if (event == 3)
			printf("	%i is sleeping\n", phil_id);
		else if (event == 4)
			printf("	%i is thinking\n", phil_id);
		else if (event == 5)
			printf("	%i died\n", phil_id);
		pthread_mutex_unlock(&pstr->print_mutex);
	}
}
