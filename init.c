/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:21:58 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/25 14:48:45 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	parse_arg(int argc, char **argv, t_data *data)
{
	memset(data, 0, sizeof(t_data));
	data->philo_n = ft_atol(argv[1]);
	data->death_t = ft_atol(argv[2]);
	data->eat_t = ft_atol(argv[3]);
	data->sleep_t = ft_atol(argv[4]);
	data->max_meal = 0;
	if (argc == 6)
		data->max_meal = ft_atol(argv[5]);
}

void	init_data(t_data *data)
{
	int	i;

	data->dead_f = 0;
	data->finished_f = 0;
	//data->one time | philo eat max;
	i = -1;
	while (++i < data->philo_n)
		pthread_mutex_init(&data->forks[i], NULL);
	//pthread_mutex_init(&data->check_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->eat_lock, NULL);
	gettimeofday(&data->start_t, NULL);
}

void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_n)
	{
		data->philo[i].id = i + 1;
		data->philo[i].eat_cnt = 0;
		data->philo[i].eating = 0;
		data->philo[i].data = data;
		data->philo[i].last_eat = get_time_in_ms(data->start_t);
		data->philo[i].l_fork = &data->forks[i];
		data->philo[i].r_fork = &data->forks[(i+1) % data->philo_n];
	}
}
