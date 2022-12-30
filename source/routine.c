/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 00:10:05 by sde-mull          #+#    #+#             */
/*   Updated: 2022/12/30 20:08:58 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	ft_sleepthink(t_philo *info)
{
	udumb(ginfo()->time_sleep);
	print_step("is Thinking", info);
}

void	ft_eating(t_philo *info, int next)
{
	pthread_mutex_lock(&(ginfo()->eat[info->id]));
	pthread_mutex_lock(&(ginfo()->eat[next]));
	print_step("has taken a fork", info);
	print_step("has taken a fork", info);
	print_step("is eating", info);
	pthread_mutex_lock(&ginfo()->time);
	info->last_meal = get_time();
	pthread_mutex_unlock(&ginfo()->time);
	udumb(ginfo()->time_eat);
	info->times_eaten += 1;
	print_step("is sleeping", info);
	pthread_mutex_unlock(&(ginfo()->eat[next]));
	pthread_mutex_unlock(&(ginfo()->eat[info->id]));
}

bool	ft_table(t_philo *info)
{
	int	next;

	next = info->id + 1;
	if (info->id == ginfo()->nbr_philo - 1)
		next = 0;
	if (ginfo()->nbr_philo == 1)
	{
		pthread_mutex_lock(&(ginfo()->eat[info->id]));
		printf("%d ms %d has taken a fork\n", 0, info->id + 1);
		udumb(ginfo()->time_die);
		pthread_mutex_unlock(&(ginfo()->eat[info->id]));
		return (true);
	}
	ft_eating(info, next);
	if (info->times_eaten == ginfo()->nbr_eat)
	{
		info->eated = 1;
		return (true);
	}
	ft_sleepthink(info);
	return (false);
}

void	*routine(void *info_copy)
{
	t_philo	*info;

	info = (t_philo *)info_copy;
	info->p_time = get_time();
	info->c_time = get_time();
	pthread_mutex_lock(&ginfo()->time);
	info->last_meal = get_time();
	pthread_mutex_unlock(&ginfo()->time);
	if (info->id + 1 % 2 == 0)
		usleep(1500);
	while (true)
	{
		pthread_mutex_lock(&ginfo()->death);
		if (ginfo()->dead)
		{
			pthread_mutex_unlock(&ginfo()->death);
			break ;
		}
		pthread_mutex_unlock(&ginfo()->death);
		if (ft_table(info))
			break ;
	}
	return (info);
}
