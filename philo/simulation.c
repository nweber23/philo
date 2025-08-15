/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 11:48:51 by nweber            #+#    #+#             */
/*   Updated: 2025/08/15 12:15:49 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_death(data) || check_meal_amount(data))
			break ;
		usleep(1000);
	}
	return (NULL);
}

int	check_death(t_data *data)
{
	long	current_time;
	long	time_since_last_meal;
	int		i;

	i = 0;
	current_time = get_time();
	while (i < data->philo_amount)
	{
		pthread_mutex_lock(&data->data);
		time_since_last_meal = current_time - data->philos[i].time_since_meal;
		if (time_since_last_meal > data->time_to_die)
		{
			pthread_mutex_lock(&data->print_mutex);
			printf("%ld %d died\n", current_time - data->start_time, \
				data->philos[i].id + 1);
			pthread_mutex_unlock(&data->print_mutex);
			data->end = 1;
			pthread_mutex_unlock(&data->data);
			return (1);
		}
		pthread_mutex_unlock(&data->data);
		i++;
	}
	return (0);
}

int	check_meal_amount(t_data *data)
{
	int	i;
	int	meals_finished;

	if (data->meal_amount == -1)
		return (0);
	meals_finished = 0;
	i = 0;
	while (i < data->philo_amount)
	{
		pthread_mutex_lock(&data->data);
		if (data->philos[i].meals_eaten >= data->meal_amount)
			meals_finished++;
		pthread_mutex_unlock(&data->data);
		i++;
	}
	if (meals_finished == data->philo_amount)
	{
		pthread_mutex_lock(&data->data);
		data->end = 1;
		pthread_mutex_unlock(&data->data);
		return (1);
	}
	return (0);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_amount)
	{
		if (pthread_create(&data->philos[i].thread, NULL, \
			philo_routine, &data->philos[i]) != 0)
			return (0);
		i++;
	}
	if (pthread_create(&data->monitor_thread, NULL, \
		monitoring, data) != 0)
		return (0);
	return (1);
}
