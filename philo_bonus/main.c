/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:22:15 by nweber            #+#    #+#             */
/*   Updated: 2026/01/13 13:24:46 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_positives(char *str)
{
	int	i;
	int	num;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	num = ft_atoi(str);
	if (num <= 0)
		return (0);
	return (1);
}

static int	parse_arg(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo_bonus Numbers_of_Philos time_to_die ");
		printf("time_to_eat time_to_sleep [numbers_of_meals]\n");
		return (0);
	}
	if (!check_positives(argv[1]) || !check_positives(argv[2])
		|| !check_positives(argv[3]) || !check_positives(argv[4]))
		return (0);
	if (argc == 6 && !check_positives(argv[5]))
		return (0);
	return (1);
}

static int	single_philo(t_data *data)
{
	if (data->philo_amount == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(data->time_to_die * 1000);
		printf("%d 1 died\n", data->time_to_die);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!parse_arg(argc, argv))
		return (printf("Error\n"), 1);
	memset(&data, 0, sizeof(t_data));
	if (!init_data(argc, argv, &data))
		return (printf("Init Error\n"), cleanup(&data), 1);
	if (single_philo(&data))
		return (cleanup(&data), 0);
	if (!start_simulation(&data))
		return (printf("Start Error\n"), cleanup(&data), 1);
	wait_processes(&data);
	cleanup(&data);
	return (0);
}
