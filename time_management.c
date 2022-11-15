/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 20:02:55 by sde-mull          #+#    #+#             */
/*   Updated: 2022/11/15 17:12:15 by sde-mull         ###   ########.fr       */
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


void	udumb(long long utime, t_philo *info, t_data *ginfo)
{
	struct timeval	time;
	long long		start;

	gettimeofday(&time, NULL);
	start = time.tv_sec * 1000 + time.tv_usec / 1000;
	while (get_time(start) < utime)
	{
		if (get_time(ginfo->p_time) - info->last_meal >= ginfo->time_die)
			break;
	}
}
