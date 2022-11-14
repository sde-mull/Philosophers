#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>

typedef struct s_philo
{
	int 			id;
	pthread_mutex_t eat;
	long long 		last_meal;
	int				times_eat;
} t_philo;

typedef struct s_data
{
	int 			forks;
	int 			nbr_philo;
	long long 		time_eat;
	long long		time_sleep;
	long long 		time_die;
	int 			nbr_eat;
	int 			fil_id;
	t_philo 		*locker;
	pthread_mutex_t death;
	pthread_mutex_t hobby;
	long long 		c_time;
	long long 		p_time;
	int				dead;
	int				times_eaten;
} t_data;



int			ft_isdigit(char *c);
int			ft_atoi(const char *str);
int			check_input(int arg, char **str);
int 		ft_reunion(t_data *ginfo);
void		ft_convert_info(t_data *ginfo, char **str, int arg);
void 		*routine(void *ginfo);
bool		ft_create_mutex(t_data *ginfo);
long long 	get_time(long long p_time);
void		udumb(long long time, t_philo *info, t_data *data);
bool 		check_death(t_philo *info, t_data *ginfo);
bool		ft_table(t_data *ginfo, t_philo *info);

#endif