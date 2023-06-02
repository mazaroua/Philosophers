/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:17:17 by mazaroua          #+#    #+#             */
/*   Updated: 2023/06/02 18:33:48 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_info(t_data *data, int ac, char **av)
{
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->n_of_times_each_philo_must_eat = ft_atoi(av[5]);
		if (!data->n_of_times_each_philo_must_eat)
			return (0);
	}
	else
		data->n_of_times_each_philo_must_eat = -1;
	return (1);
}

int	init_mutexs(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->write, NULL) != 0)
		return (0);
	pthread_mutex_init(&data->eaten_mutex, NULL);
	pthread_mutex_init(&data->stop_mutex, NULL);
	return (1);
	
}

void	detach_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->number_of_philosophers)
		pthread_detach(philo[i++].philo);
}

int	creating_philos(t_data *data, t_philo *philos)
{
	int		i;

	i = 0;
	data->start_of_simulation = curr_time();
	data->all_eaten = 0;
	while (i < data->number_of_philosophers)
	{
		philos[i].id = i + 1;
		if (i == 0)
			philos[i].right_fork = &data->forks[data->number_of_philosophers - 1];
		else
			philos[i].right_fork = &data->forks[i - 1];
		philos[i].left_fork = &data->forks[i];
		philos[i].ate = 0;
		philos[i].last_meal = curr_time();
		philos[i].data = data;
		pthread_mutex_init(&philos[i].last_meal_mutex, NULL);
		if (pthread_create(&philos[i].philo, NULL, &routine, &philos[i]) != 0)
			return (0);
		i++;
	}
	detach_threads(philos);
	return (1);
}

