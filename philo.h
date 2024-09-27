/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:13:33 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/27 20:00:05 by tkaragoz         ###   ########.fr       */
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

typedef enum e_activity
{
	EAT,
	THINK,
	SLEEP,
	FORK,
	DIED,
	OVER
}			t_activity;

typedef struct s_philo
{
	pthread_t	thread;			// Philosopher's thread
	int			id;				// Philosopher's unique ID
	int			eat_cnt;		// Number of times the philosopher has eaten
	long		last_eat;	// Timestamp when the philosopher will die if not eaten
	t_mutex		*r_fork;		// Pointer to the right fork mutex
	t_mutex		*l_fork;		// Pointer to the left fork mutex
	t_data		*data;			// Pointer to shared data

}				t_philo;

typedef struct s_data
{
	long int	philo_n;			// Number of philosophers
	int			max_meal;			// Number of meals required (optional)
	int			full_philo_n;		//Number of philosophers who have finished eating
	int			dead_f;				// Flag indicating if a philosopher has died
	int			finished_f;			//
	t_philo		philo[MAX_PHILO];	// Array of philosophers
	long		death_t;			// Time to die (in milliseconds)
	long		eat_t;				// Time to eat (in milliseconds)
	long		sleep_t;			// Time to sleep (in milliseconds)
	t_timeval	start_t;			// Simulation start time
	t_mutex		forks[MAX_PHILO];	// Array of fork mutexes
	t_mutex		check_lock;		// Mutex for checking conditions
	t_mutex		write_lock;			// Mutex for writing/logging
	t_mutex		dead_lock;			// Mutex for dead flag
	t_mutex		eat_lock;
	//t_mutex		finished_lock;			// Mutex for eating flag
}				t_data;

int		ft_is_digit(char c);
long	ft_atol(char *str);
long	get_time_in_ms(t_timeval start);
void	simulation(t_data *data);
void	*routine(void *arg);
void	ft_log(t_philo *philo, char *msg, long time);
int		if_dead(t_philo *philo);


void	parse_arg(int argc, char **argv, t_data *data);
void	init_data(t_data *data);
void	init_philos(t_data *data);

int	if_dead_f(t_data *data);
int	check_if_full(t_data *data);

int	ft_usleep(int mseconds, t_data *data);

void	free_all(t_data *data);


#endif
