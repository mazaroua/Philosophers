/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:03:11 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/18 17:10:13 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_if_num(char *arg)
{
	int	i;

	i = 0;
	if (!arg[0])
		return (0);
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int parsing(char **av)
{
    int i;

    i = 1;
    while (av[i])
    {
        if (!check_if_num(av[i]))
            return (0);
		i++;
    }
	return (1);
}