/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 11:49:39 by nweber            #+#    #+#             */
/*   Updated: 2025/08/20 20:04:20 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken the left fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken the right fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken the right fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken the left fork");
	}
}

void	eat_and_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data);
	philo->time_since_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->data);
	print_status(philo, "is eating");
	ft_usleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2, philo);
	else
		ft_usleep(philo->data->time_to_eat / 4, philo);
	while (2)
	{
		pthread_mutex_lock(&philo->data->data);
		if (philo->data->end)
		{
			pthread_mutex_unlock(&philo->data->data);
			break ;
		}
		pthread_mutex_unlock(&philo->data->data);
		take_forks(philo);
		eat_and_sleep(philo);
		print_status(philo, "is thinking");
		ft_usleep((philo->data->time_to_eat - \
			philo->data->time_to_sleep) / 2 + 2, philo);
	}
	return (NULL);
}
