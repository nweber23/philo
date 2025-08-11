/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 10:07:30 by nweber            #+#    #+#             */
/*   Updated: 2025/08/11 10:19:35 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philo_amount);
	if (!data->philos)
		return (0);
	i = 0;
	while (i < data->philo_amount)
	{
		data->philos[i].id = i;
		data->philos[i].meals_eaten = 0;
		data->philos[i].time_since_meal = data->start_time;
		data->philos[i].data = data;
		data->philos[i].left_fork = data->forks[i];
		data->philos[i].right_fork = data->forks[(i + 1) % data->philo_amount];
		i++;
	}
	return (1);
}

static int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_amount);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->philo_amount)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			printf("Error initializing fork mutex %d\n", i);
			free(data->forks);
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (printf("Error initializing print mutex\n"), \
		free(data->forks), 0);
	if (pthread_mutex_init(&data->data, NULL) != 0)
		return (printf("Error initializing data mutex\n"), \
		pthread_mutex_destroy(&data->print_mutex), free(data->forks), 0);
	return (1);
}
