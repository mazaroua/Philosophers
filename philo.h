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
	pthread_mutex_t	last_meal;
	pthread_mutex_t	write;
    long            start_of_simulation;
    pthread_mutex_t stop_mutex;
    pthread_mutex_t eaten_mutex;
    pthread_mutex_t ate;
    int             stop;
    int             all_eaten;
}t_data;

typedef struct philo
{
    int             id;
    pthread_t       philo;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    long            last_meal;
    t_data          *data;
    int             ate;
}t_philo;

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		parsing(char **av);
long	curr_time(void);
void	ft_usleep(long time);
int	print_state(t_philo *philo, char *state, int unlock);
int	check(t_philo *philo, t_data *data);

#endif