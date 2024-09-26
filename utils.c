/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:27:51 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/26 19:27:11 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_full(t_data *data)
{
	pthread_mutex_lock(&data->finished_lock);
	if (data->finished_f)
		return (pthread_mutex_unlock(&data->finished_lock), EXIT_FAILURE);
	pthread_mutex_lock(&data->finished_lock);
	return (EXIT_SUCCESS);
}

int	check_dead_f(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->dead_f)
		return (pthread_mutex_unlock(&data->dead_lock), EXIT_FAILURE);
	pthread_mutex_lock(&data->dead_lock);
	return (EXIT_SUCCESS);
}

void	ft_log(t_philo *philo, char *msg, long time)
{
	pthread_mutex_lock(&philo->data->write_lock);
	if (check_dead_f(philo->data))
		printf("%ld %d died\n", time, philo->id);
	else if (check_is_full(philo->data))
		printf("%ld They all ate\n", time);
	else if (!check_dead_f(philo->data) && !check_if_full(philo->data))
		printf("%ld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->write_lock);
	//burada kaldimAKSHFAKJSFBAKBFAKF
}

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
