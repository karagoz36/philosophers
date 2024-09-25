/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:27:51 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/25 14:48:57 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_in_ms(t_timeval start)
{
	long		elapsed_ms;
	t_timeval	current;

	gettimeofday(&current, NULL);
	elapsed_ms = (current.tv_sec - start.tv_sec) * 1000;
	elapsed_ms += (current.tv_usec - start.tv_usec) / 1000;
	return (elapsed_ms);
}

int	ft_is_digit(char c)
{
	if (c > '9' || c < '0')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

long	ft_atol(char *str)
{
	long	number;
	long	sign;
	int		i;

	number = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		number = (number * 10 + str[i] - '0');
		i++;
	}
	return (sign * number);
}
