/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:00:31 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/30 16:06:31 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	verif_all_philo_eat(t_data *data)
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

int	calcul_death(t_philo *philo)
{
	long	current;

	pthread_mutex_lock(&philo->data->eat_lock);
	current = get_time_in_ms(philo->data->start_t);
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead_f)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		pthread_mutex_unlock(&philo->data->eat_lock);
		return (EXIT_FAILURE);
	}
	else if (current - philo->last_eat > philo->data->death_t)
	{
		pthread_mutex_lock(&philo->data->write_lock);
		printf("%ld %d died\n", get_time_in_ms(philo->data->start_t), philo->id);
		philo->data->dead_f = 1;
		pthread_mutex_unlock(&philo->data->write_lock);
		pthread_mutex_unlock(&philo->data->dead_lock);
		pthread_mutex_unlock(&philo->data->eat_lock);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	pthread_mutex_unlock(&philo->data->eat_lock);
	return (EXIT_SUCCESS);
}

void	monitoring(t_data *data)
{
	int	i;

	while (1)
	{
		pthread_mutex_lock(&data->eat_lock);
		data->full_philo_n = 0;
		pthread_mutex_unlock(&data->eat_lock);
		i = -1;
		while (++i < data-> philo_n)
		{
			if (calcul_death(&data->philo[i]))
				return ;
			pthread_mutex_lock(&data->eat_lock);
			if (data->max_meal && data->philo[i].eat_cnt >= data->max_meal)
				data->full_philo_n++;
			pthread_mutex_unlock(&data->eat_lock);
		}
		if (verif_all_philo_eat(data))
			return ;
		usleep(100);
	}
}

void	simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_n)
	{
		if (pthread_create(&data->philo[i].thread, NULL, \
				&routine, &data->philo[i]))
			return (free_all(data));
		i++;
	}
	monitoring(data);
	i = 0;
	while (i < data->philo_n)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	free_all(data);
}
