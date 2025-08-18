/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:32:03 by nweber            #+#    #+#             */
/*   Updated: 2025/08/18 09:49:28 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;
	int	i;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long time)
{
	long	start_time;

	start_time = get_time();
	while (get_time() - start_time < time)
		usleep(1000);
}

void	print_status(t_philo *philo, const char *status)
{
	long	time;

	pthread_mutex_lock(&philo->data->data);
	time = get_time() - philo->data->start_time;
	pthread_mutex_unlock(&philo->data->data);
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->end)
	{
		printf("%ld %d %s\n", time, philo->id + 1, status);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	philo_amount_checker(t_philo *philo)
{
	long	current_time;

	if (philo->data->philo_amount == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		current_time = get_time();
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d died\n", current_time - philo->data->start_time, \
			philo->data->philos[0].id + 1);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (0);
	}
	return (1);
}