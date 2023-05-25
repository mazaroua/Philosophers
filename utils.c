/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:06:51 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/24 16:42:05 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_state(t_philo *philo, char *state, int unlock)
{
	if (pthread_mutex_lock(&philo->data->write) != 0)
		return (0);
	printf("\e[1m\e[94m%lu\e[93m %d %s\n\e[0m", curr_time() - \
	philo->data->start_of_simulation, philo->id, state);
	if (unlock)
	{
		if (pthread_mutex_unlock(&philo->data->write) != 0)
		return (0);
	}
	return (1);
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

	start = curr_time();
	while (((curr_time()) - start) < time)
		usleep(100);
	return ;
}
