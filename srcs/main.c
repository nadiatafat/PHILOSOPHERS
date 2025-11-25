/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadgalle <nadgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:49:39 by nadgalle          #+#    #+#             */
/*   Updated: 2025/03/14 16:27:15 by nadgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	monitor;

	if (ac == 6 || ac == 5)
	{
		parse_input_data(&data, av);
		init_data(&data);
		dinner(&data, monitor);
		if (pthread_create(&monitor, NULL, ft_monitor_routine, &data) != 0)
			ft_exit_error("Failed to create thread.", &data);
		pthread_join(monitor, NULL);
		ft_join_thread_philos(&data);
		ft_clean(&data);
	}
	else
	{
		ft_exit_error("Invalid number of argument.", NULL);
	}
	return (0);
}
