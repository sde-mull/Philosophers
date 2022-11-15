/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:56:07 by sde-mull          #+#    #+#             */
/*   Updated: 2022/11/15 16:18:03 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void destroy_mutex(t_data *ginfo)
{
	int index;

	index = -1;
	while (++index < ginfo->nbr_philo)
		pthread_mutex_destroy(&ginfo->locker[index].eat);
	pthread_mutex_destroy(&ginfo->death);
}

bool check_death(t_philo *info, t_data *ginfo)
{
	pthread_mutex_lock(&ginfo->death);
	if (ginfo->dead == 1 || ginfo->times_eaten == 1)
	{
		pthread_mutex_unlock(&ginfo->death);
		return (true);
	}
	ginfo->c_time = get_time(ginfo->p_time);
	//printf("%lld -> last meal || %lld -> ginfo->c_time || %d -> philo\n\n", info->last_meal, ginfo->c_time, info->id + 1);
	if (ginfo->c_time - info->last_meal >= ginfo->time_die)
	{
		ginfo->dead = 1;
		printf("%lld ms %d died\n", ginfo->c_time, info->id + 1);
		pthread_mutex_unlock(&ginfo->death);
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
		printf("%lld ms %d %s\n",ginfo->c_time, info->id + 1, str);
	pthread_mutex_unlock(&ginfo->hobby);
}

void	ft_eating(t_data *ginfo, t_philo *info, int next)
{
	pthread_mutex_lock(&(ginfo->locker[info->id].eat));
	print_step("has taken a fork", info, ginfo);
	pthread_mutex_lock(&(ginfo->locker[next].eat));
	print_step("has taken a fork", info, ginfo);
	print_step("is eating", info, ginfo);
	info->last_meal = ginfo->c_time;
	udumb(ginfo->time_eat, info, ginfo);
	//check_death(info, ginfo);
	info->times_eat += 1;
	pthread_mutex_unlock(&(ginfo->locker[next].eat));
	pthread_mutex_unlock(&(ginfo->locker[info->id].eat));
}

bool	ft_table(t_data *ginfo, t_philo *info)
{
	int next;
	
	next = info->id + 1;
	if (info->id == ginfo->nbr_philo - 1)
		next = 0;
	if (ginfo->nbr_philo == 1)
	{
		pthread_mutex_lock(&(ginfo->locker[info->id].eat));
		printf("%lld ms %d has taken a fork\n",ginfo->c_time, info->id + 1);
		udumb(ginfo->time_die, info, ginfo);
		pthread_mutex_unlock(&(ginfo->locker[info->id].eat));
		if (check_death(info, ginfo))
			return (true);
	}
	ft_eating(ginfo, info, next);
	if (info->times_eat == ginfo->nbr_eat)
		return (true);
	ft_sleepthink(ginfo, info, next);
	return (false);
}

void *routine(void *ginfo)
{
	t_philo info;

	t_data *ginfo_copy = (t_data *) ginfo;
	info.id = ginfo_copy->fil_id;
	ginfo_copy->dead = 0;
	ginfo_copy->c_time = 0;
	ginfo_copy->p_time = get_time(-1);
	info.times_eat = 0;
	info.last_meal = 0;
	ginfo_copy->times_eaten = 0;
	while(!ginfo_copy->dead)
		if (ft_table(ginfo, &info))
			break;
	return (ginfo);
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
	if (ft_reunion(&ginfo))
		return(printf("Error:\nFailed to create/join thread\n"));
	destroy_mutex(&ginfo);
	free(ginfo.locker);
	return(0);
}