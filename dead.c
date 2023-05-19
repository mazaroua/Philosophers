/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:39:57 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/19 21:51:40 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check2(t_philo *philo, t_data *data, int i)
{
	if (curr_time() - philo[i].last_meal > data->time_to_die)
	{
		data->stop = 1;
        print_state(philo, "died");
		return (0);
	}
	return (1);
}

void	*check(void	*arg)
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
			if (!check2(philo, data, i))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}