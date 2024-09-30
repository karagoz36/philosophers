/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:38:46 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/30 16:06:20 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		ft_log(philo, "has taken left fork", \
		get_time_in_ms(philo->data->start_t));
		pthread_mutex_lock(philo->r_fork);
		ft_log(philo, "has taken right fork", \
		get_time_in_ms(philo->data->start_t));
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		ft_log(philo, "has taken right fork", \
		get_time_in_ms(philo->data->start_t));
		pthread_mutex_lock(philo->l_fork);
		ft_log(philo, "has taken left fork", \
		get_time_in_ms(philo->data->start_t));
	}
}

int	check_break(t_philo *philo)
{
	if (calcul_death_f(philo->data) || check_if_full(philo->data))
	{
		pthread_mutex_lock(&philo->data->check_lock);
		ft_log(philo, "", get_time_in_ms(philo->data->start_t));
		pthread_mutex_unlock(&philo->data->check_lock);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_eat(t_philo *philo)
{
	if (check_break(philo))
		return (EXIT_FAILURE);
	take_forks(philo);
	ft_log(philo, "is eating", get_time_in_ms(philo->data->start_t));
	pthread_mutex_lock(&philo->data->eat_lock);
	philo->last_eat = get_time_in_ms(philo->data->start_t);
	pthread_mutex_unlock(&philo->data->eat_lock);
	ft_usleep(philo->data->eat_t, philo->data);
	pthread_mutex_lock(&philo->data->eat_lock);
	philo->eat_cnt++;
	pthread_mutex_unlock(&philo->data->eat_lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (EXIT_SUCCESS);
}

int	ft_think(t_philo *philo)
{
	if (check_break(philo))
		return (EXIT_FAILURE);
	ft_log(philo, "is thinking", get_time_in_ms(philo->data->start_t));
	ft_usleep(philo->data->death_t - philo->data->eat_t - philo->data->sleep_t - 10, philo->data);
	//??
	return (EXIT_SUCCESS);
}

int	ft_sleep(t_philo *philo)
{
	if (check_break(philo))
		return (EXIT_FAILURE);
	ft_log(philo, "is sleeping", get_time_in_ms(philo->data->start_t));
	ft_usleep(philo->data->sleep_t, philo->data);
	return (EXIT_SUCCESS);
}

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

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (handle_one_philo(philo->data))
		return (NULL);
	while (!calcul_death(philo) && !check_if_full(philo->data))
	{
		if (ft_eat(philo))
			break ;
		if (ft_think(philo))
			break ;
		if (ft_sleep(philo))
			break ;
	}
	return (NULL);
}
