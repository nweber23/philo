/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 10:03:54 by nweber            #+#    #+#             */
/*   Updated: 2025/08/11 10:04:16 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_amount)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
		{
			printf("Error joining thread %d\n", i);
			return (0);
		}
		i++;
	}
	if (pthread_join(data->monitor_thread, NULL) != 0)
	{
		printf("Error joining monitor thread\n");
		return (0);
	}
	return (1);
}

static void	destroy_mutexes(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->philo_amount)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->data);
}

void	cleanup(t_data *data)
{
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	destroy_mutexes(data);
	data->end = 1;
}
