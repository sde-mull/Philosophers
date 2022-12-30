/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:35:28 by sde-mull          #+#    #+#             */
/*   Updated: 2022/12/07 15:53:00 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	long long		last_meal;
	int				times_eaten;
	pthread_t		philo_init;
	int				eated;
	long long		c_time;
	long long		p_time;
}	t_philo;

typedef struct s_data
{
	int				forks;
	int				nbr_philo;
	long long		time_eat;
	long long		time_sleep;
	long long		time_die;
	int				nbr_eat;
	int				dead;
	t_philo			*locker;
	pthread_mutex_t	*eat;
	pthread_mutex_t	death;
	pthread_mutex_t	hobby;
	pthread_mutex_t	time;
}	t_data;

// ------------- death.c -------------

void		death_checker(void);
bool		check_death(t_philo *info);

// ------------- extra.c -------------

int			ft_isdigit(char *c);
int			ft_atoi(const char *str);
int			check_input(int arg, char **str);
t_data		*ginfo(void);
void		print_step(char *str, t_philo *info);

// ------------- information.c -------------

int			ft_reunion(void);
bool		init_philo(void);
bool		ft_convert_info(char **str, int arg);
bool		ft_create_mutex(void);
void		destroy_mutex(void);

// ------------- routine.c -------------

void		ft_sleepthink(t_philo *info);
void		ft_eating(t_philo *info, int next);
bool		ft_table(t_philo *info);
void		*routine(void *info_copy);

// ------------- time_management.c -------------

long long	timediff(long long past, long long present);
long long	get_time(void);
void		udumb(long long utime);

#endif