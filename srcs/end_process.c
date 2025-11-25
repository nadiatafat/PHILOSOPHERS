/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadgalle <nadgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:37:38 by nadgalle          #+#    #+#             */
/*   Updated: 2025/03/14 15:36:03 by nadgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_join_thread_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philosopher)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

void	ft_clean(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (i < data->nb_of_philosopher)
			pthread_mutex_destroy(&data->forks[i++]);
		free(data->forks);
	}
	pthread_mutex_destroy(&data->write_mtx);
	pthread_mutex_destroy(&data->dead_mtx);
	pthread_mutex_destroy(&data->start_mtx);
	pthread_mutex_destroy(&data->all_full_mtx);
	i = 0;
	if (data->philos)
	{
		while (i < data->nb_of_philosopher)
			pthread_mutex_destroy(&data->philos[i++].meal_mtx);
		free(data->philos);
	}
	exit(0);
}
