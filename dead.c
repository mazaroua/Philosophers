/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:39:57 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/26 16:09:02 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check(t_philo *philo, t_data *data)
{
	int		i;
	int		ate;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&philo->data->ate);
		ate = philo[i].ate;
		pthread_mutex_unlock(&philo->data->ate);
		pthread_mutex_lock(&data->eaten_mutex);
		if (data->all_eaten == data->number_of_philosophers)
			return (0);
		pthread_mutex_unlock(&data->eaten_mutex);

		pthread_mutex_lock(&data->last_meal);
	
		if (curr_time() - philo[i].last_meal > data->time_to_die
		&& ate != data->n_of_times_each_philo_must_eat)
		{
			print_state(philo, "\x1B[31mdied", 0);
			return (0);
		}
		pthread_mutex_unlock(&data->last_meal);
		i++;
		if (i == data->number_of_philosophers)
			i = 0;
	}
	return (1);
}