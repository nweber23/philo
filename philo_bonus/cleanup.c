/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:22:30 by nweber            #+#    #+#             */
/*   Updated: 2026/01/16 12:55:47 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_amount)
	{
		if (data->pids[i] > 0)
			kill(data->pids[i], SIGKILL);
		i++;
	}
}

void	close_semaphores(t_data *data)
{
	if (data->forks)
		sem_close(data->forks);
	if (data->print)
		sem_close(data->print);
	if (data->meal)
		sem_close(data->meal);
	if (data->dead)
		sem_close(data->dead);
	if (data->stop)
		sem_close(data->stop);
}

void	cleanup_semaphores(t_data *data)
{
	close_semaphores(data);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_MEAL);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_STOP);
}

void	child_cleanup(t_data *data)
{
	close_semaphores(data);
	if (data->philos)
		free(data->philos);
	if (data->pids)
		free(data->pids);
}

void	cleanup(t_data *data)
{
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	if (data->pids)
	{
		free(data->pids);
		data->pids = NULL;
	}
	cleanup_semaphores(data);
}
