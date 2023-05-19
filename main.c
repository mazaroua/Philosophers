/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:53:17 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/19 21:55:29 by mazaroua         ###   ########.fr       */
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

void	init_forks(t_data *data)
{
	int	i;

	i = data->number_of_philosophers;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_of_times_each_philo_must_eat);
	while (i)
		pthread_mutex_init(&data->forks[i--], NULL);
}

void	start_eating(t_philo *philo)
{
	if (philo->data->stop == 1)
			return ;
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	ft_usleep(philo->data->time_to_eat * 1000);
	philo->last_meal = curr_time();
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->data->stop = 0;
	while (philo->data->stop == 0)
	{
		if (philo->id % 2 == 0)
			ft_usleep(100);
		start_eating(philo);
		if (philo->data->stop == 1)
			return (NULL);
		print_state(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep * 1000);
		if (philo->data->stop == 1)
			return (NULL);
		print_state(philo, "is thinking");
	}
	return (NULL);
}

void	creating_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	i = 0;
	data->start_of_simulation = curr_time();
	while (i < data->number_of_philosophers)
	{
		philos[i].id = i + 1;
		if (i == 0)
			philos[i].right_fork = &data->forks[data->number_of_philosophers - 1];
		else
			philos[i].right_fork = &data->forks[i];
		philos[i].left_fork = &data->forks[i + 1];
		philos[i].last_meal = curr_time();
		philos[i].data = data;
		pthread_create(&philos[i].philo, NULL, &routine, &philos[i]);
		i++;
	}
	pthread_create(&data->check_is_dead, NULL, &check, philos);
	while (i)
	{
		pthread_join(philos[i].philo, NULL);
		i--;
	}
	pthread_join(data->check_is_dead, NULL);
}

int main(int ac, char **av)
{
	t_data	data;

    if (ac == 5 || ac == 6)
    {
        if (parsing(av))
        {
			pthread_mutex_init(&data.write, NULL);
            get_info(&data, ac, av);
			init_forks(&data);
			creating_philos(&data);
        }
        else
            printf("Syntax Error\n");
    }
    else
        printf("Number of args should be between 5 or 6\n");
	return (0);
}