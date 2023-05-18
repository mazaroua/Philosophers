#ifndef PHILO_H
#define PHILO_H

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

typedef struct data
{
    int				number_of_philosophers;
    int				time_to_die;
    int				time_to_eat;
	int				time_to_sleep;
    int				n_of_times_each_philo_must_eat;
	pthread_mutex_t	*forks;
}t_data;

typedef struct philo
{
    int	id;

}t_philo;

int	ft_atoi(const char *str);
int	ft_isdigit(int c);
int parsing(char **av);


#endif