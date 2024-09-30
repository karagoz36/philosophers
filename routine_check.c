/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:48:31 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/30 16:52:26 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_one_philo(t_data *data)
{
	if (data->philo_n == 1)
	{
		ft_log(data->philo, "has taken fork", get_time_in_ms(data->start_t));
		ft_usleep(data->death_t, data);
		ft_log(data->philo, "died", get_time_in_ms(data->start_t));
		pthread_mutex_lock(&data->dead_lock);
		data->dead_f = 1;
		pthread_mutex_unlock(&data->dead_lock);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	verif_death_f(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->dead_f)
	{
		pthread_mutex_unlock(&data->dead_lock);
		return (EXIT_FAILURE);
	}
	return (pthread_mutex_unlock(&data->dead_lock), EXIT_SUCCESS);
}

int	check_break(t_philo *philo)
{
	if (verif_death_f(philo->data) || check_if_full(philo->data))
	{
		pthread_mutex_lock(&philo->data->check_lock);
		ft_log(philo, "They are full", get_time_in_ms(philo->data->start_t));
		pthread_mutex_unlock(&philo->data->check_lock);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
