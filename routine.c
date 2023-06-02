/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:18:28 by mazaroua          #+#    #+#             */
/*   Updated: 2023/06/02 18:39:07 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (philo->data->stop == 1)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	if (philo->ate == philo->data->n_of_times_each_philo_must_eat)
	{
		pthread_mutex_lock(&philo->data->eaten_mutex);
		philo->data->all_eaten += 1;
		pthread_mutex_unlock(&philo->data->eaten_mutex);
		return (0);
	}
		lock_forks(philo);
		print_state(philo, "\x1B[32mis eating", 1);
		philo->ate += 1;
		pthread_mutex_lock(&philo->last_meal_mutex);
		philo->last_meal = curr_time();
		pthread_mutex_unlock(&philo->last_meal_mutex);
		ft_usleep(philo->data->time_to_eat);
		unlock_forks(philo);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1337)
	{
		if (!start_eating(philo))
			return (NULL);
		print_state(philo, "\033[37;1mis sleeping", 1);
		ft_usleep(philo->data->time_to_sleep);
		print_state(philo, "\033[37;1mis thinking", 1);
	}
	return (NULL);
}