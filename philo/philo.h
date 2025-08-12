/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 19:52:13 by nweber            #+#    #+#             */
/*   Updated: 2025/08/12 12:46:16 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				philo_amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_amount;
	int				end;
	long			start_time;
	t_philo			*philos;
	pthread_t		monitor_thread;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	data;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			time_since_meal;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

// Init
int		init_data(int argc, char **argv, t_data *data);

// Cleanup
int		join_threads(t_data *data);
void	cleanup(t_data *data);

// Utils
int		ft_atoi(const char *str);
long	get_time(void);
void	ft_usleep(long time);
void	print_status(t_philo *philo, const char *status);

// Actions
void	take_forks(t_philo *philo);
void	eat_and_sleep(t_philo *philo);
void	*philo_routine(void *arg);

// Simulation
void	*monitoring(void *arg);
int		check_death(t_data *data);
int		check_meal_amount(t_data *data);
int		create_threads(t_data *data);

#endif