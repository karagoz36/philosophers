/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:57:48 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/30 16:03:55 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_full(t_data *data)
{
	pthread_mutex_lock(&data->eat_lock);
	if (data->finished_f)
	{
		pthread_mutex_unlock(&data->eat_lock);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&data->eat_lock);
	return (EXIT_SUCCESS);
}

int	check_dead_f(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->dead_f)
	{
		pthread_mutex_unlock(&data->dead_lock);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&data->dead_lock);
	return (EXIT_SUCCESS);
}

static int	already_printed(t_data *data)
{
	pthread_mutex_lock(&data->write_lock);
	if (data->printed)
	{
		pthread_mutex_unlock(&data->write_lock);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&data->write_lock);
	return (EXIT_SUCCESS);
}

void	ft_log(t_philo *philo, char *msg, long time)
{
	if (check_dead_f(philo->data) == 1)
		return ;
	if (check_if_full(philo->data) && !already_printed(philo->data))
	{
		pthread_mutex_lock(&philo->data->write_lock);
		printf("%ld They are all full\n", time);
		philo->data->printed = 1;
		pthread_mutex_unlock(&philo->data->write_lock);
	}
	else if (check_dead_f(philo->data) && !already_printed(philo->data))
	{
		pthread_mutex_lock(&philo->data->write_lock);
		printf("%ld %d died\n", time, philo->id);
		philo->data->printed = 1;
		pthread_mutex_unlock(&philo->data->write_lock);
	}
	else if (!already_printed(philo->data))
	{
		pthread_mutex_lock(&philo->data->write_lock);
		printf("%ld %d %s\n", time, philo->id, msg);
		pthread_mutex_unlock(&philo->data->write_lock);
	}
}
