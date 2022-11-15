/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   information.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 03:36:53 by sde-mull          #+#    #+#             */
/*   Updated: 2022/11/15 16:16:59 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_reunion(t_data *ginfo)
{
	pthread_t filo[ginfo->nbr_philo];

	ginfo->fil_id = 0;
	while (ginfo->fil_id < ginfo->nbr_philo)
	{
		if (pthread_create(&filo[ginfo->fil_id], NULL, &routine, ginfo) != 0)
			return(1);
		usleep(25);
		ginfo->fil_id++;
	}
	ginfo->fil_id = 0;
	while (ginfo->fil_id < ginfo->nbr_philo)
	{
		if (pthread_join(filo[ginfo->fil_id],NULL) != 0)
			return(2);
		ginfo->fil_id++;
	}
	return(0);
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
	ginfo->locker = malloc(sizeof(t_philo) * ginfo->nbr_philo);
	if (!ginfo->locker)
		return(false);
	while (++index < ginfo->nbr_philo)
		pthread_mutex_init(&ginfo->locker[index].eat, NULL);
	pthread_mutex_init(&ginfo->death, NULL);
	pthread_mutex_init(&ginfo->hobby, NULL);
	return (true);
}