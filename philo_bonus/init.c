/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:22:22 by nweber            #+#    #+#             */
/*   Updated: 2026/01/16 13:11:26 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philo_amount);
	if (!data->philos)
		return (0);
	data->pids = malloc(sizeof(pid_t) * data->philo_amount);
	if (!data->pids)
		return (free(data->philos), 0);
	i = 0;
	while (i < data->philo_amount)
	{
		data->philos[i].id = i;
		data->philos[i].meals_eaten = 0;
		data->philos[i].time_since_meal = data->start_time;
		data->philos[i].data = data;
		data->philos[i].routine = 0;
		data->philos[i].monitor = 0;
		data->pids[i] = 0;
		i++;
	}
	return (1);
}

static void	unlink_semaphores(void)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_MEAL);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_STOP);
}

static int	init_sems_part2(t_data *data)
{
	data->dead = sem_open(SEM_DEAD, O_CREAT, 0644, 0);
	if (data->dead == SEM_FAILED)
	{
		sem_close(data->forks);
		sem_close(data->print);
		sem_close(data->meal);
		return (0);
	}
	data->stop = sem_open(SEM_STOP, O_CREAT, 0644, 1);
	if (data->stop == SEM_FAILED)
	{
		sem_close(data->forks);
		sem_close(data->print);
		sem_close(data->meal);
		sem_close(data->dead);
		return (0);
	}
	return (1);
}

int	init_semaphores(t_data *data)
{
	unlink_semaphores();
	data->forks = sem_open(SEM_FORKS, O_CREAT, 0644, data->philo_amount);
	if (data->forks == SEM_FAILED)
		return (0);
	data->print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (data->print == SEM_FAILED)
		return (sem_close(data->forks), 0);
	data->meal = sem_open(SEM_MEAL, O_CREAT, 0644, 1);
	if (data->meal == SEM_FAILED)
	{
		sem_close(data->forks);
		sem_close(data->print);
		return (0);
	}
	return (init_sems_part2(data));
}

int	init_data(int argc, char **argv, t_data *data)
{
	data->philo_amount = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->meal_amount = ft_atoi(argv[5]);
	else
		data->meal_amount = -1;
	data->end = 0;
	data->start_time = get_time();
	if (!init_semaphores(data))
		return (0);
	if (!init_philos(data))
		return (cleanup_semaphores(data), 0);
	return (1);
}
