/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:06:51 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/20 17:36:04 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, char *state)
{

	pthread_mutex_lock(&philo->data->write);
	printf("%lu %d %s\n", curr_time() - \
	philo->data->start_of_simulation, philo->id, state);
	pthread_mutex_unlock(&philo->data->write);
}

int	ft_atoi(const char *str)
{
	int						i;
	int						result;
	int						sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

long	curr_time(void)
{
	struct timeval	tv;
	long			curr_time;

	gettimeofday(&tv, NULL);
	curr_time = ((tv.tv_sec * 1000000) + tv.tv_usec) / 1000;
	return (curr_time);
}

void	ft_usleep(long time)
{
	long int	start;

	start = curr_time() * 1000;
	while (((curr_time() * 1000) - start) < time)
		usleep(50);
	return ;
}
