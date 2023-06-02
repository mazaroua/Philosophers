/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:39:57 by mazaroua          #+#    #+#             */
/*   Updated: 2023/06/02 18:38:48 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check(t_philo *philo, t_data *data)
{
	int		i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (data->n_of_times_each_philo_must_eat != -1)
		{
			pthread_mutex_lock(&data->eaten_mutex);
			if (data->all_eaten == data->number_of_philosophers)
				return (0);
			pthread_mutex_unlock(&data->eaten_mutex);
		}
		pthread_mutex_lock(&philo[i].last_meal_mutex);
		if (curr_time() - philo[i].last_meal > data->time_to_die)
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			return (print_state(philo, "\x1B[31mdied", 0), 0);
		}
		pthread_mutex_unlock(&philo[i].last_meal_mutex);
		i++;
		if (i == data->number_of_philosophers)
			i = 0;
	}
	return (1);
}
