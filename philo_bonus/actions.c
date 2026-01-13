/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:22:37 by nweber            #+#    #+#             */
/*   Updated: 2026/01/13 13:22:42 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork");
}

void	release_forks(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	eat_and_sleep(t_philo *philo)
{
	sem_wait(philo->data->meal);
	philo->time_since_meal = get_time();
	philo->meals_eaten++;
	sem_post(philo->data->meal);
	print_status(philo, "is eating");
	ft_usleep(philo->data->time_to_eat, philo);
	release_forks(philo);
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo);
}

static int	check_end(t_philo *philo)
{
	if (philo->data->meal_amount != -1
		&& philo->meals_eaten >= philo->data->meal_amount)
		return (1);
	return (0);
}

void	philo_routine(t_philo *philo)
{
	philo->time_since_meal = get_time();
	if (pthread_create(&philo->monitor, NULL, monitor_death, philo) != 0)
		exit(1);
	pthread_detach(philo->monitor);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2, philo);
	else
		ft_usleep(philo->data->time_to_eat / 4, philo);
	while (1)
	{
		if (check_end(philo))
			exit(0);
		take_forks(philo);
		eat_and_sleep(philo);
		print_status(philo, "is thinking");
		ft_usleep((philo->data->time_to_eat
				- philo->data->time_to_sleep) / 2 + 2, philo);
	}
}
