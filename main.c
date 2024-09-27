/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:14:10 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/27 19:38:56 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (++i <= data->philo_n)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->eat_lock);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->check_lock);
}

int	check_arg(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		return (printf("Philo numbers time to die time to eat time to sleep\n")
			, EXIT_FAILURE);
	i = 0;
	while (argv[++i])
		if (ft_atol(argv[i]) <= 0)
			return (printf("Only positive numbers!"), EXIT_FAILURE);
	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			if (ft_is_digit(argv[i][j]))
				return (printf("Only numbers!"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}


int	main(int argc, char **argv)
{
	t_data		data;

	if (check_arg(argc, argv))
		return (EXIT_FAILURE);
	parse_arg(argc, argv, &data);
	init_data(&data);
	init_philos(&data);
	simulation(&data);
	return (EXIT_SUCCESS);
}
