/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:53:17 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/18 17:32:11 by mazaroua         ###   ########.fr       */
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

int main(int ac, char **av)
{
	t_data	data;

    if (ac == 5 || ac == 6)
    {
        if (parsing(av))
        {
            get_info(&data, ac, av);
			init_forks(&data);
        }
        else
            printf("Syntax Error\n");
    }
    else
        printf("Number of args should be between 5 or 6\n");
}