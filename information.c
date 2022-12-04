/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   information.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 03:36:53 by sde-mull          #+#    #+#             */
/*   Updated: 2022/12/03 18:20:22 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void death_checker(t_data *ginfo)
{
	int index;

	index = 0;
	while (index <= ginfo->nbr_philo)
	{
		if (index == ginfo->nbr_philo)
			index = 0;
		if (ginfo->locker[index].eated == 1)
			break;
		if (ginfo->locker[index].dead == 1)
		{
			index = 0;
			while (index <= ginfo->nbr_philo)
			{
				ginfo->locker[index].dead = 1;
				index++;
			}
			pthread_mutex_unlock(&ginfo->death);
			break;
		}
		index++;
	}
}

int ft_reunion(t_data *ginfo)
{
	int i;

	i = 0;
	while (i < ginfo->nbr_philo)
	{
		if (pthread_create(&ginfo->locker[i].philo_init, NULL, &routine, &(ginfo->locker[i])) != 0)
			return(1);
		i++;
	}
	death_checker(ginfo);
	i = 0;
	while (i < ginfo->nbr_philo)
	{
		if (pthread_join(ginfo->locker[i].philo_init, NULL) != 0)
			return(2);
		i++;
	}
	return(0);
}

bool	init_philo(t_data *ginfo)
{
	int index;

	index = -1;
	ginfo->locker = malloc(sizeof(t_philo) * ginfo->nbr_philo + 1);
	if (!ginfo->locker)
		return (false);
	while (++index < ginfo->nbr_philo)
	{
		ginfo->locker[index].times_eaten = 0;
		ginfo->locker[index].id = index;
		ginfo->locker[index].last_meal = 0;
		ginfo->locker[index].info = ginfo;
	}
	return (true);
}

bool	ft_convert_info(t_data *ginfo, char **str, int arg)
{
	ginfo->forks = ft_atoi(str[1]);
	ginfo->nbr_philo = ft_atoi(str[1]);
	ginfo->time_die = ft_atoi(str[2]);
	ginfo->time_eat = ft_atoi(str[3]);
	ginfo->time_sleep = ft_atoi(str[4]);
	if (arg == 6)
		ginfo->nbr_eat = ft_atoi(str[5]);
	if (ginfo->nbr_philo == 0)
		return (false);
	return (true);
}

bool	ft_create_mutex(t_data *ginfo)
{
	int index;

	index = -1;
	ginfo->eat = malloc(sizeof(pthread_mutex_t *) * ginfo->nbr_philo + 1);
	if (!ginfo->eat)
		return(false);
	while (++index < ginfo->nbr_philo)
		pthread_mutex_init(&ginfo->eat[index], NULL);
	pthread_mutex_init(&ginfo->death, NULL);
	pthread_mutex_init(&ginfo->hobby, NULL);
	pthread_mutex_init(&ginfo->time, NULL);
	return (true);
}