/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:27:12 by nweber            #+#    #+#             */
/*   Updated: 2025/08/10 20:31:26 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_arg(argc, argv, &data) != 0)
		return (printf("Error\n"), 1);
	if (init_data(&data) != 0)
		return (printf("Init Error\n"), 1);
	if (start_simulation(&data) != 0)
		return (printf("Start Error\n"), cleanup(&data), 1);
	cleanup(&data);
	return (0);
}
