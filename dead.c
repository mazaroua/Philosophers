/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:39:57 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/24 19:50:09 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check(t_philo *philo, t_data *data)
{
	int		i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->eaten_mutex);
		if (data->all_eaten == data->n_of_times_each_philo_must_eat)
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->eaten_mutex);

		if (pthread_mutex_lock(&data->last_meal) != 0)
			return (0);
		if (curr_time() - philo[i].last_meal > data->time_to_die)
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			print_state(philo, "\x1B[31mdied", 0);
			return (0);
		}
		if (pthread_mutex_unlock(&data->last_meal) != 0)
			return (0);
		i++;
		if (i == data->number_of_philosophers)
			i = 0;
	}
	return (1);
}