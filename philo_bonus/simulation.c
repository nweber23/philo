/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:21:45 by nweber            #+#    #+#             */
/*   Updated: 2026/01/16 13:19:43 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_died(t_philo *philo, long current_time)
{
	if (philo->data->end)
		return ;
	philo->data->end = 1;
	sem_wait(philo->data->print);
	printf("%ld %d died\n", current_time - philo->data->start_time,
		philo->id + 1);
	sem_post(philo->data->print);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	*monitor_death(void *arg)
{
	t_philo	*philo;
	long	current_time;
	long	time_since_last_meal;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->data->end)
			return (NULL);
		usleep(500);
		sem_wait(philo->data->meal);
		current_time = get_time();
		time_since_last_meal = current_time - philo->time_since_meal;
		sem_post(philo->data->meal);
		if (time_since_last_meal >= philo->data->time_to_die)
		{
			philo_died(philo, current_time);
			return (NULL);
		}
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < data->philo_amount)
	{
		pid = fork();
		if (pid == -1)
		{
			kill_processes(data);
			return (0);
		}
		if (pid == 0)
			philo_routine(&data->philos[i]);
		data->pids[i] = pid;
		i++;
	}
	return (1);
}

void	wait_processes(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->philo_amount)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			kill_processes(data);
			break ;
		}
		i++;
	}
}
