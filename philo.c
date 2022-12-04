/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:56:07 by sde-mull          #+#    #+#             */
/*   Updated: 2022/12/04 17:16:19 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void destroy_mutex(t_data *ginfo)
{
	int index;

	index = -1;
	while (++index < ginfo->nbr_philo)
		pthread_mutex_destroy(&ginfo->eat[index]);
	pthread_mutex_destroy(&ginfo->death);
	pthread_mutex_destroy(&ginfo->hobby);
}

bool check_death(t_philo *info, t_data *ginfo)
{
	pthread_mutex_lock(&ginfo->death);
	if (info->dead == 1)
	{
		pthread_mutex_unlock(&ginfo->death);
		return (true);
	}
	if (get_time() - info->last_meal >= ginfo->time_die)
	{
		info->dead = 1;
		printf("%lld ms %d died\n", get_time() - ginfo->p_time, info->id + 1);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&ginfo->death);
		return (false);
	}
}

void	ft_sleepthink(t_data *ginfo, t_philo *info, int next)
{
		print_step("is sleeping", info, ginfo);
		udumb(ginfo->time_sleep, info, ginfo);
		print_step("is Thinking", info, ginfo);
}

void	print_step(char *str, t_philo *info, t_data *ginfo)
{
	pthread_mutex_lock(&ginfo->hobby);
	if (!(check_death(info, ginfo)))
		printf("%lld ms %d %s\n", get_time() - ginfo->p_time, info->id + 1, str);
	pthread_mutex_unlock(&ginfo->hobby);
}

void	ft_eating(t_data *ginfo, t_philo *info, int next)
{
	pthread_mutex_lock(&(ginfo->eat[info->id]));
	print_step("has taken a fork", info, ginfo);
	pthread_mutex_lock(&(ginfo->eat[next]));
	print_step("has taken a fork", info, ginfo);
	print_step("is eating", info, ginfo);
	udumb(ginfo->time_eat, info, ginfo);
	info->last_meal = get_time();
	info->times_eaten += 1;
	pthread_mutex_unlock(&(ginfo->eat[next]));
	pthread_mutex_unlock(&(ginfo->eat[info->id]));
}

bool	ft_table(t_data *ginfo, t_philo *info)
{
	int next;
	
	next = info->id + 1;
	if (info->id == ginfo->nbr_philo - 1)
		next = 0;
	if (ginfo->nbr_philo == 1)
	{
		pthread_mutex_lock(&(ginfo->eat[info->id]));
		printf("%lld ms %d has taken a fork\n",info->c_time, info->id + 1);
		udumb(ginfo->time_die, info, ginfo);
		pthread_mutex_unlock(&(ginfo->eat[info->id]));
		if (check_death(info, ginfo))
			return (true);
	}
	ft_eating(ginfo, info, next);
	if (info->times_eaten == ginfo->nbr_eat)
	{
		info->eated = 1;
		return (true);
	}
	ft_sleepthink(ginfo, info, next);
	return (false);
}

void *routine(void *info_copy)
{
	t_philo *info;
	t_data *ginfo;

	info = (t_philo *)info_copy;
	ginfo = (t_data *)info->info;
	info->dead = 0;
	info->eated = 0;
	info->c_time = 0;
	ginfo->p_time = get_time();
	info->last_meal = get_time();
	if (info->id % 2 == 0)
		usleep(1500);
	while(!info->dead)
		if (ft_table(ginfo, info))
			break;
	return (info);
}

int main(int argc, char *argv[])
{
	t_data ginfo;
	
	if(check_input(argc, argv) != 0)
		return(printf("Error:\nInvalid input\n"));
	if (!ft_convert_info(&ginfo, argv, argc))
		return (printf("Error:\nThere must be at least 1 philo\n"));
	if (!ft_create_mutex(&ginfo))
		return(printf("Failed to create array\n"));
	init_philo(&ginfo);
	if (ft_reunion(&ginfo))
		return(printf("Error:\nFailed to create/join thread\n"));
	destroy_mutex(&ginfo);
	free(ginfo.locker);
	free(ginfo.eat);
	return(0);
}