/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:38:52 by ksura             #+#    #+#             */
/*   Updated: 2022/11/26 22:18:08 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

time_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_time(t_philostr	*philostr)
{
	time_t	time;
	time_t	time_start;

	time_start = philostr->time_start;
	time = get_time_ms();
	printf("%ldms", time - time_start);
	return ;
}

void	sleeping(t_philostr *philostr, time_t sleeping_time)
{
	time_t	end;

	end = get_time_ms() + sleeping_time;
	while (get_time_ms() < end)
	{
		if (!stop_checker(philostr))
			return ;
		usleep(100);
	}
}
