/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:53:17 by mazaroua          #+#    #+#             */
/*   Updated: 2023/06/02 18:18:18 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write);
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
            if (!get_info(&data, ac, av))
				return (0);
			philos = malloc(sizeof(t_philo) * data.number_of_philosophers);
			if (!init_mutexs(&data))
				return (0);
			creating_philos(&data, philos);
			if (!check(philos, &data))
			{
				// destroy_mutexes(&data);
				return (0);
			}
        }
        else
            printf("Syntax Error\n");
    }
    else
        printf("Number of args should be between 5 or 6\n");
}