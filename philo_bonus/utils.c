/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:21:55 by nweber            #+#    #+#             */
/*   Updated: 2026/01/13 13:22:01 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	ft_usleep(long time, t_philo *philo)
{
	long	start_time;

	(void)philo;
	start_time = get_time();
	while (get_time() - start_time < time)
		usleep(500);
}

void	print_status(t_philo *philo, const char *status)
{
	long	time;

	sem_wait(philo->data->print);
	time = get_time() - philo->data->start_time;
	printf("%ld %d %s\n", time, philo->id + 1, status);
	sem_post(philo->data->print);
}
