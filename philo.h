#ifndef PHILO_H
#define PHILO_H

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct data
{
    int				number_of_philosophers;
    long			time_to_die;
    int				time_to_eat;
	int				time_to_sleep;
    int				n_of_times_each_philo_must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	eaten_mutex;
    long            start_of_simulation;
    int             all_eaten;
    int             stop;
    pthread_mutex_t stop_mutex;
}t_data;

typedef struct philo
{
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    pthread_mutex_t last_meal_mutex;
    t_data          *data;
    int             id;
    pthread_t       philo;
    long            last_meal;
    int             ate;
}t_philo;

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		parsing(char **av);
long	curr_time(void);
void	ft_usleep(long time);
int	print_state(t_philo *philo, char *state, int unlock);
int	get_info(t_data *data, int ac, char **av);
int	init_mutexs(t_data *data);
int	creating_philos(t_data *data, t_philo *philos);
void	*routine(void *arg);
int	check(t_philo *philo, t_data *data);

#endif