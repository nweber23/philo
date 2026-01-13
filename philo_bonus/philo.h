/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:22:06 by nweber            #+#    #+#             */
/*   Updated: 2026/01/13 13:22:09 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <semaphore.h>
# include <fcntl.h>

# define SEM_FORKS "/philo_forks"
# define SEM_PRINT "/philo_print"
# define SEM_MEAL "/philo_meal"
# define SEM_DEAD "/philo_dead"
# define SEM_STOP "/philo_stop"

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int			philo_amount;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			meal_amount;
	int			end;
	long		start_time;
	t_philo		*philos;
	pid_t		*pids;
	sem_t		*forks;
	sem_t		*print;
	sem_t		*meal;
	sem_t		*dead;
	sem_t		*stop;
}				t_data;

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	long		time_since_meal;
	t_data		*data;
	pthread_t	monitor;
}				t_philo;

// Init
int		init_data(int argc, char **argv, t_data *data);
int		init_semaphores(t_data *data);
int		init_philos(t_data *data);

// Cleanup
void	cleanup_semaphores(t_data *data);
void	cleanup(t_data *data);
void	kill_processes(t_data *data);

// Utils
int		ft_atoi(const char *str);
long	get_time(void);
void	ft_usleep(long time, t_philo *philo);
void	print_status(t_philo *philo, const char *status);

// Actions
void	take_forks(t_philo *philo);
void	release_forks(t_philo *philo);
void	eat_and_sleep(t_philo *philo);
void	philo_routine(t_philo *philo);

// Simulation
void	*monitor_death(void *arg);
int		start_simulation(t_data *data);
void	wait_processes(t_data *data);

#endif
