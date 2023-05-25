/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:53:17 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/25 20:01:10 by mazaroua         ###   ########.fr       */
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
	else
		data->n_of_times_each_philo_must_eat = -1;
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
	if (pthread_mutex_init(&data->stop_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->write, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->last_meal, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->eaten_mutex, NULL) != 0)
		return (0);
	return (1);
}

int	lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if(pthread_mutex_lock(philo->right_fork) != 0)
			return (0);
		if (!print_state(philo, "\033[37;1mhas taken a fork", 1))
			return (0);
		if (pthread_mutex_lock(philo->left_fork) != 0)
			return (0);
		if (!print_state(philo, "\033[37;1mhas taken a fork", 1))
			return (0);
	}
	else
	{
		if (pthread_mutex_lock(philo->left_fork) != 0)
			return (0);
		if (!print_state(philo, "\033[37;1mhas taken a fork", 1))
			return (0);
		if (pthread_mutex_lock(philo->right_fork) != 0)
			return (0);
		if (!print_state(philo, "\033[37;1mhas taken a fork", 1))
			return (0);
	}
	return (1);
}

int	unlock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_unlock(philo->right_fork) != 0)
			return (0);
		if (pthread_mutex_unlock(philo->left_fork) != 0)
			return (0);
	}
	else
	{
		if (pthread_mutex_unlock(philo->left_fork) != 0)
			return (0);
		if (pthread_mutex_unlock(philo->right_fork) != 0)
			return (0);
	}
	return (1);
}

int	start_eating(t_philo *philo)
{	
	if (philo->ate == philo->data->n_of_times_each_philo_must_eat)
	{
		pthread_mutex_lock(&philo->data->eaten_mutex);
		philo->data->all_eaten += 1;
		pthread_mutex_unlock(&philo->data->eaten_mutex);
		return (0);
	}
	if (!lock_forks(philo))
		return (0);
	if (!print_state(philo, "\x1B[32mis eating", 1))
		return (0);
	if (pthread_mutex_lock(&philo->data->last_meal) != 0)
		return (0);
	philo->last_meal = curr_time();
	if (pthread_mutex_unlock(&philo->data->last_meal) != 0)
		return (0);
	ft_usleep(philo->data->time_to_eat);
	if (!unlock_forks(philo))
		return (0);
	philo->ate += 1;
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1337)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		if (philo->data->stop)
			return (NULL);
		pthread_mutex_unlock(&philo->data->stop_mutex);
		if (!start_eating(philo))
			return (NULL);
		if (!print_state(philo, "\033[37;1mis sleeping", 1))
			return (NULL);
		ft_usleep(philo->data->time_to_sleep);
		if (!print_state(philo, "\033[37;1mis thinking", 1))
			return (NULL);
	}
	return (NULL);
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
	data->stop = 0;
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
		if (pthread_create(&philos[i].philo, NULL, &routine, &philos[i]) != 0)
			return (0);
		i++;
	}
	detach_threads(philos);
	return (1);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->last_meal);
	pthread_mutex_destroy(&data->eaten_mutex);
	free(data->forks);
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
			if (!init_mutexs(&data))
				return (0);
			if (!creating_philos(&data, philos) || !check(philos, philos[0].data))
			{
				destroy_mutexes(&data);
				free(philos);
				return (0);
			}
        }
        else
            printf("Syntax Error\n");
    }
    else
        printf("Number of args should be between 5 or 6\n");
}