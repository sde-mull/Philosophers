#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>

typedef struct s_data
{
	int 			forks;
	int 			nbr_philo;
	long long 		time_eat;
	long long		time_sleep;
	long long 		time_die;
	int 			nbr_eat;
	struct s_philo 		*locker;
	long long 		p_time;
	pthread_mutex_t *eat;
	pthread_mutex_t death;
	pthread_mutex_t hobby;
	pthread_mutex_t time;
} t_data;

typedef struct s_philo
{
	int 			id;
	long long 		last_meal;
	int				times_eaten;
	pthread_t		philo_init;
	t_data			*info;
	int				dead;
	int 			eated;
	long long 		c_time;
} t_philo;



int			ft_isdigit(char *c);
int			ft_atoi(const char *str);
int			check_input(int arg, char **str);
int 		ft_reunion(t_data *ginfo);
bool		ft_convert_info(t_data *ginfo, char **str, int arg);
void 		*routine(void *ginfo);
bool		ft_create_mutex(t_data *ginfo);
long long 	get_time(void);
void		udumb(long long time, t_philo *info, t_data *ginfo);
bool 		check_death(t_philo *info, t_data *ginfo);
bool		ft_table(t_data *ginfo, t_philo *info);
void		print_step(char *str, t_philo *info, t_data *ginfo);
bool		init_philo(t_data *ginfo);
long long timediff(long long past, long long present);

#endif