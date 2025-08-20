/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:27:12 by nweber            #+#    #+#             */
/*   Updated: 2025/08/20 17:00:27 by nweber           ###   ########.fr       */
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
		printf("Usage: ./philo Numbers_of_Philos time_to_die ");
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

int	main(int argc, char **argv)
{
	t_data	data;

	if (!parse_arg(argc, argv))
		return (printf("Error\n"), 1);
	memset(&data, 0, sizeof(t_data));
	if (!init_data(argc, argv, &data))
		return (printf("Init Error\n"), cleanup(&data), 1);
	if (!philo_amount_checker(data.philos))
		return (cleanup(&data), 0);
	if (!create_threads(&data))
		return (printf("Start Error\n"), cleanup(&data), 1);
	join_threads(&data);
	cleanup(&data);
	exit(EXIT_SUCCESS);
}
