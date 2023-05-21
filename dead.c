/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:39:57 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/21 19:31:12 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check2(t_philo *philo, t_data *data, int i)
{
	pthread_mutex_lock(&data->check);
	if (curr_time() - philo[i].last_meal > data->time_to_die)
	{
		pthread_mutex_lock(&data->stop);
		data->stop_simulation = 1;
		pthread_mutex_unlock(&data->stop);
		pthread_mutex_lock(&data->write);
		printf("%lu %d died\n", curr_time() - data->start_of_simulation, philo[i].id);
		return (0);
	}
	pthread_mutex_unlock(&data->check);
	return (1);
}

int	check(void	*arg)
{
	t_philo	*philo;
	t_data	*data;
	int		i;

	philo = (t_philo *)arg;
	data = philo->data;
	i = 0;
	while (1337)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			ft_usleep(100);
			if (!check2(philo, data, i))
				return (0);
			i++;
		}
	}
	return (0);
}