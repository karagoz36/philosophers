/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:13:33 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/30 16:58:33 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

# ifndef MAX_PHILO
#  define MAX_PHILO 200
# endif

typedef struct timeval	t_timeval;
typedef pthread_mutex_t	t_mutex;
typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	int			eat_cnt;
	long		last_eat;
	t_mutex		*r_fork;
	t_mutex		*l_fork;
	t_data		*data;
}				t_philo;

typedef struct s_data
{
	long int	philo_n;
	int			max_meal;
	int			full_philo_n;
	int			dead_f;
	int			finished_f;
	t_philo		philo[MAX_PHILO];
	long		death_t;
	long		eat_t;
	long		sleep_t;
	int			printed;
	t_timeval	start_t;
	t_mutex		forks[MAX_PHILO];
	t_mutex		check_lock;
	t_mutex		write_lock;
	t_mutex		dead_lock;
	t_mutex		eat_lock;
}				t_data;

int		ft_is_digit(char c);
long	ft_atol(char *str);

void	simulation(t_data *data);
void	*routine(void *arg);
void	ft_log(t_philo *philo, char *msg, long time);
int		calcul_death(t_philo *philo);

void	parse_arg(int argc, char **argv, t_data *data);
void	init_data(t_data *data);
void	init_philos(t_data *data);

long	get_time_in_ms(t_timeval start);
int		check_if_full(t_data *data);
int		check_dead_f(t_data *data);
int		ft_usleep(int mseconds, t_data *data);
void	free_all(t_data *data);

int		check_break(t_philo *philo);
int		handle_one_philo(t_data *data);

#endif
