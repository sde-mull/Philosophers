/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 20:02:55 by sde-mull          #+#    #+#             */
/*   Updated: 2022/10/26 23:30:44 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long get_time(long long p_time)
{
	struct timeval current_time;

 	gettimeofday(&current_time, NULL);
	if (p_time == -1)
		return((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000) - p_time);
}


void	udumb(long long utime)
{
	struct timeval	time;
	long long		start;

	gettimeofday(&time, NULL);
	start = time.tv_sec * 1000 + time.tv_usec / 1000;
	while (get_time(start) < utime);
}