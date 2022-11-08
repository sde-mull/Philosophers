/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:56:07 by sde-mull          #+#    #+#             */
/*   Updated: 2022/11/08 02:13:51 by sde-mull         ###   ########.fr       */
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

bool check_death(t_philo *info, t_data *ginfo, int next)
{
	pthread_mutex_lock(&ginfo->death);
	if (ginfo->dead == 1 || ginfo->times_eaten == 1)
	{
		pthread_mutex_unlock(&ginfo->death);
		return (true);
	}
	ginfo->c_time = get_time(ginfo->p_time);
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
	if (!(check_death(info, ginfo, next)))
	{
		printf("%lld ms %d is sleeping\n",ginfo->c_time, info->id + 1);
		udumb(ginfo->time_sleep);
		if (!(check_death(info, ginfo, next)))
			printf("%lld ms %d is thinking\n", ginfo->c_time, info->id + 1);
	}
	else
	{
		return ;
	}
}

void	ft_eating(t_data *ginfo, t_philo *info, int next)
{
	pthread_mutex_lock(&(ginfo->locker[info->id].eat));
	if (!(check_death(info, ginfo, next)))
	{
		printf("%lld ms %d has taken a fork\n",ginfo->c_time, info->id + 1);
		pthread_mutex_lock(&(ginfo->locker[next].eat));
		if (!(check_death(info, ginfo, next)))
		{
			printf("%lld ms %d has taken a fork\n",ginfo->c_time, info->id + 1);
			printf("%lld ms %d is eating\n",ginfo->c_time, info->id + 1);
			udumb(ginfo->time_eat);
			info->times_eat += 1;
			info->last_meal = ginfo->c_time;
		}
		else
			return ;
		pthread_mutex_unlock(&(ginfo->locker[next].eat));
	}
	else
		return ;
	pthread_mutex_unlock(&(ginfo->locker[info->id].eat));
}



void	ft_table(t_data *ginfo, t_philo *info)
{
	int next;
	
	next = info->id + 1;
	if (info->id == ginfo->nbr_philo - 1)
		next = 0;
	ft_eating(ginfo, info, next);
	if (info->times_eat == ginfo->nbr_eat)
		ginfo->times_eaten = 1;
	ft_sleepthink(ginfo, info, next);
	//printf("|||%d has eaten %d|||\n", info->id + 1, info->times_eat);
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
	ginfo_copy->times_eaten = 0;
	while(!ginfo_copy->dead)
	{
		ft_table(ginfo, &info);
		if (ginfo_copy->times_eaten == 1)
			break;
	}
	return (ginfo);
}

int main(int argc, char *argv[])
{
	t_data ginfo;
	
	if(check_input(argc, argv) != 0)
		return(printf("Error:\nInvalid input\n"));
	ft_convert_info(&ginfo, argv, argc);
	if (!ft_create_mutex(&ginfo))
		return(printf("Failed to create array"));
	if (ft_reunion(&ginfo))
		return(printf("Error:\nFailed to create/join thread"));
	destroy_mutex(&ginfo);
	free(ginfo.locker);
	return(0);
}