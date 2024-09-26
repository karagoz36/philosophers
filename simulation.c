/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:00:31 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/26 18:27:40 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	verif_all_philo_eat(t_data *data)
{
	pthread_mutex_lock(&data->eat_lock);
	if (data->full_philo_n == data->philo_n)
	{
		data->finished_f = 1;
		pthread_mutex_unlock(&data->eat_lock);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&data->eat_lock);
	return (EXIT_SUCCESS);
}

int	if_dead(t_philo *philo)
{
	long	current;
	long	last_eat;

	pthread_mutex_lock(&philo->data->eat_lock);
	last_eat = philo->last_eat;
	pthread_mutex_unlokc(&philo->data->eat_lock);
	current = get_time_in_ms(philo->data->start_t);
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead_f)
		return (pthread_mutex_unlock(&philo->data->dead_lock), EXIT_FAILURE);
	else if (current - last_eat > philo->data->eat_t)
	{
		philo->data->dead_f = 1;
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (EXIT_SUCCESS);
}

void	monitoring(t_data *data)
{
	int	i;

	while (1)
	{
		data->full_philo_n = 0;
		i = -1;
		while (++i < data-> philo_n)
		{
			if (if_dead(&data->philo[i]))
				return ;
			pthread_mutex_lock(&data->finished_lock);
			if (data->max_meal && data->philo[i].eat_cnt >= data->max_meal)
				data->full_philo_n++;
			pthread_mutex_unlock(&data->finished_lock);
		}
		if (verif_all_philo_eat(data))
			return ;
		usleep(100);
	}
}

void	simulation(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_n)
	{
		if (pthread_create(&data->philo[i].thread, NULL, \
				&routine, &data->philo[i]))
			return (free_all(&data), EXIT_FAILURE);
	}
	monitoring(data);
	i = -1;
	while (++i < data->philo_n)
		pthread_join(data->philo[i].thread, NULL);
	//free_all(data->philo);
	return (EXIT_SUCCESS);
}
