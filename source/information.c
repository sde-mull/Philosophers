/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   information.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 03:36:53 by sde-mull          #+#    #+#             */
/*   Updated: 2022/12/30 19:36:20 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	ft_reunion(void)
{
	int	i;

	i = 0;
	while (i < ginfo()->nbr_philo)
	{
		if (pthread_create(&ginfo()->locker[i].philo_init, NULL, &routine,
				&(ginfo()->locker[i])) != 0)
			return (1);
		usleep(50);
		i++;
	}
	death_checker();
	i = 0;
	while (i < ginfo()->nbr_philo)
	{
		if (pthread_join(ginfo()->locker[i].philo_init, NULL) != 0)
			return (2);
		i++;
	}
	return (0);
}

bool	init_philo(void)
{
	int	index;

	index = -1;
	ginfo()->locker = (t_philo *)malloc(sizeof(t_philo) \
	* ginfo()->nbr_philo);
	if (!ginfo()->locker)
		return (false);
	while (++index < ginfo()->nbr_philo)
	{
		ginfo()->locker[index].times_eaten = 0;
		ginfo()->locker[index].id = index;
		ginfo()->locker[index].last_meal = 0;
		ginfo()->locker[index].eated = 0;
	}
	return (true);
}

bool	ft_convert_info(char **str, int arg)
{
	ginfo()->dead = 0;
	ginfo()->forks = ft_atoi(str[1]);
	ginfo()->nbr_philo = ft_atoi(str[1]);
	ginfo()->time_die = ft_atoi(str[2]);
	ginfo()->time_eat = ft_atoi(str[3]);
	ginfo()->time_sleep = ft_atoi(str[4]);
	if (arg == 6)
		ginfo()->nbr_eat = ft_atoi(str[5]);
	if (ginfo()->nbr_philo == 0)
		return (false);
	return (true);
}

bool	ft_create_mutex(void)
{
	int	index;

	index = -1;
	ginfo()->eat = malloc(sizeof(pthread_mutex_t) * ginfo()->nbr_philo + 1);
	if (!ginfo()->eat)
		return (false);
	while (++index < ginfo()->nbr_philo)
		pthread_mutex_init(&ginfo()->eat[index], NULL);
	pthread_mutex_init(&ginfo()->death, NULL);
	pthread_mutex_init(&ginfo()->hobby, NULL);
	pthread_mutex_init(&ginfo()->time, NULL);
	return (true);
}

void	destroy_mutex(void)
{
	int	index;

	index = -1;
	while (++index < ginfo()->nbr_philo)
		pthread_mutex_destroy(&ginfo()->eat[index]);
	pthread_mutex_destroy(&ginfo()->death);
	pthread_mutex_destroy(&ginfo()->hobby);
	pthread_mutex_destroy(&ginfo()->time);
}
