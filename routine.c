/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:38:46 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/26 18:30:31 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat(t_philo *philo)
{
	if (check_break(philo))
		return (EXIT_FAILURE);
	take_forks(philo);
	// pthread_mutex_lock(&philo->data->eat_lock);
	philo->last_eat = get_time_in_ms(philo->data->start_t);
	// pthread_mutex_unlock(&philo->data->eat_lock);
	ft_log(philo, "is eating", get_time_in_ms(philo->data->start_t));
	ft_usleep(philo->data);
	put_down_forks(philo);
	//??
	// pthread_mutex_lock(&philo->data->eat_lock);
	philo->eat_cnt++;
	// pthread_mutex_unlock(&philo->data->eat_lock);
	return (EXIT_SUCCESS);
}

int	ft_think(t_philo *philo)
{
	if (check_break(philo))
		return (EXIT_FAILURE);
	ft_log(philo, "is thinking", get_time_in_ms(philo->data->start_t));
	return (EXIT_SUCCESS);
}

int	ft_sleep(t_philo *philo)
{
	if (check_break(philo))
		return (EXIT_FAILURE);
	ft_log(philo, "is thinking", get_time_in_ms(philo->data->start_t));
	ft_usleep(philo->data);
	return (EXIT_SUCCESS);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (if_dead(philo))
			return ;
		if (ft_eat(philo))
			return ;
		if (ft_think(philo))
			return ;
		if (ft_sleep(philo))
			return ;
	}
}
