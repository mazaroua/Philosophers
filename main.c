/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:53:17 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/21 19:32:19 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_info(t_data *data, int ac, char **av)
{
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->n_of_times_each_philo_must_eat = ft_atoi(av[5]);
}

void	init_mutexs(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->check, NULL);
	pthread_mutex_init(&data->stop, NULL);
}

void	lock_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
}

void	unlock_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	start_eating(t_philo *philo)
{	
	lock_fork(philo);
	print_state(philo, "is eating");
	pthread_mutex_lock(&philo->data->check);
	philo->last_meal = curr_time();
	pthread_mutex_unlock(&philo->data->check);
	ft_usleep(philo->data->time_to_eat * 1000);
	philo->ate += 1;
	unlock_fork(philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->id % 2)
			ft_usleep(100);
		start_eating(philo);
		print_state(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep * 1000);
		print_state(philo, "is thinking");
		pthread_mutex_lock(&philo->data->stop);
		if (philo->data->stop_simulation == 1)
			return (NULL);
		pthread_mutex_unlock(&philo->data->stop);
	}
	return (NULL);
}

void	thread_detach(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_detach(philo[i].philo);
		i++;
	}
}

void	creating_philos(t_data *data, t_philo *philos)
{
	int		i;

	i = 0;
	data->start_of_simulation = curr_time();
	while (i < data->number_of_philosophers)
	{
		philos[i].id = i + 1;
		if (i == 0)
			philos[i].right_fork = &data->forks[data->number_of_philosophers - 1];
		else
			philos[i].right_fork = &data->forks[i - 1];
		philos[i].left_fork = &data->forks[i];
		philos[i].ate = 0;
		philos[i].data = data;
		philos[i].last_meal = data->start_of_simulation;
		pthread_create(&philos[i].philo, NULL, &routine, &philos[i]);
		i++;
	}
	thread_detach(philos, data);
}

int main(int ac, char **av)
{
	t_philo	*philos;
	t_data	data;

    if (ac == 5 || ac == 6)
    {
        if (parsing(av))
        {
            get_info(&data, ac, av);
			philos = malloc(sizeof(t_philo) * data.number_of_philosophers);
			init_mutexs(&data);
			creating_philos(&data, philos);
			check(philos);
        }
        else
            printf("Syntax Error\n");
    }
    else
        printf("Number of args should be between 5 or 6\n");
}