/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 00:09:56 by sde-mull          #+#    #+#             */
/*   Updated: 2022/12/30 20:08:06 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	death_checker(void)
{
	int	index;

	index = 0;
	usleep(5000);
	while (!ginfo()->dead)
	{
		if (index == ginfo()->nbr_philo)
			index = 0;
		if (ginfo()->locker[index].eated == 1)
			break ;
		pthread_mutex_lock(&ginfo()->time);
		if (check_death(&ginfo()->locker[index]))
		{
			pthread_mutex_lock(&ginfo()->death);
			ginfo()->dead = 1;
			pthread_mutex_unlock(&ginfo()->death);
			pthread_mutex_unlock(&ginfo()->time);
			break ;
		}
		pthread_mutex_unlock(&ginfo()->time);
		index++;
	}
	pthread_mutex_unlock(&ginfo()->hobby);
}

bool	check_death(t_philo *info)
{
	if (get_time() - info->last_meal > ginfo()->time_die)
	{
		pthread_mutex_lock(&ginfo()->hobby);
		printf("%lld ms %d died\n", get_time() - \
		info->p_time, info->id + 1);
		return (true);
	}
	else
		return (false);
}
