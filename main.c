/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:53:17 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/20 18:44:16 by mazaroua         ###   ########.fr       */
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

	i = data->number_of_philosophers;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	while (i)
		pthread_mutex_init(&data->forks[i--], NULL);
	pthread_mutex_init(&data->write, NULL);
}

void	start_eating(t_philo *philo)
{	
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
	}
	philo->last_meal = curr_time();
	print_state(philo, "is eating");
	ft_usleep(philo->data->time_to_eat * 1000);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->data->dead == 0)
	{
		start_eating(philo);
		print_state(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep * 1000);
		print_state(philo, "is thinking");
	}
	return (NULL);
}

void	creating_philos(t_data *data, t_philo *philos)
{
	int		i;

	i = 0;
	data->start_of_simulation = curr_time();
	data->dead = 0;
	while (i < data->number_of_philosophers)
	{
		philos[i].id = i + 1;
		if (i == 0)
			philos[i].right_fork = &data->forks[data->number_of_philosophers - 1];
		else
			philos[i].right_fork = &data->forks[i - 1];
		philos[i].left_fork = &data->forks[i];
		philos[i].ate = 0;
		philos[i].last_meal = data->start_of_simulation;
		philos[i].data = data;
		pthread_create(&philos[i].philo, NULL, &routine, &philos[i]);
		i++;
	}
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