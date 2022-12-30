/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 20:02:55 by sde-mull          #+#    #+#             */
/*   Updated: 2022/12/30 19:52:52 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

long long	timediff(long long past, long long present)
{
	return (present - past);
}

long long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	udumb(long long utime)
{
	long long		start;

	start = get_time();
	while (1)
	{
		if (timediff(start, get_time()) >= utime)
			break ;
		usleep(50);
	}
}
