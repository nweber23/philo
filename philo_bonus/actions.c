/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:22:37 by nweber            #+#    #+#             */
/*   Updated: 2026/01/16 13:19:43 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static void	child_exit(t_philo *philo, int status)
{
	sem_wait(philo->data->meal);
	philo->data->end = 1;
	sem_post(philo->data->meal);
	pthread_join(philo->monitor, NULL);
	child_cleanup(philo->data);
	exit(status);
}

static void	philo_loop(t_philo *philo)
{
	while (1)
	{
		if (philo->data->end)
			child_exit(philo, 1);
		if (check_end(philo))
			child_exit(philo, 0);
		take_forks(philo);
		if (philo->data->end)
			child_exit(philo, 1);
		eat_and_sleep(philo);
		if (philo->data->end)
			child_exit(philo, 1);
		print_status(philo, "is thinking");
		ft_usleep((philo->data->time_to_eat
				- philo->data->time_to_sleep) / 2 + 2, philo);
	}
}

void	philo_routine(t_philo *philo)
{
	philo->time_since_meal = get_time();
	if (pthread_create(&philo->monitor, NULL, monitor_death, philo) != 0)
	{
		child_cleanup(philo->data);
		exit(1);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2, philo);
	else
		ft_usleep(philo->data->time_to_eat / 4, philo);
	philo_loop(philo);
}
