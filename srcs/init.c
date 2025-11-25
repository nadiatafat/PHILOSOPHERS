/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadgalle <nadgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:35:39 by nadgalle          #+#    #+#             */
/*   Updated: 2025/03/07 10:35:39 by nadgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philosopher)
	{
		data->philos[i].philo_id = i + 1;
		data->philos[i].last_meal = ft_get_time();
		data->philos[i].nb_of_meals_eaten = 0;
		data->philos[i].full_flag = 0;
		if (i % 2 == 0)
		{
			data->philos[i].first_fork = &data->forks[i];
			data->philos[i].second_fork = &data->forks[(i + 1)
				% data->nb_of_philosopher];
		}
		else
		{
			data->philos[i].first_fork = &data->forks[(i + 1)
				% data->nb_of_philosopher];
			data->philos[i].second_fork = &data->forks[i];
		}
		pthread_mutex_init(&data->philos[i].meal_mtx, NULL);
		data->philos[i].data = data;
		i++;
	}
}

static void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philosopher)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

int	init_data(t_data *data)
{
	data->begining = ft_get_time();
	data->total_meals_eaten = 0;
	data->dead_flag = 0;
	data->all_full_flag = 0;
	pthread_mutex_init(&data->start_mtx, NULL);
	pthread_mutex_init(&data->all_full_mtx, NULL);
	pthread_mutex_init(&data->dead_mtx, NULL);
	pthread_mutex_init(&data->write_mtx, NULL);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->nb_of_philosopher);
	if (!data->forks)
		return (1);
	init_forks(data);
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->nb_of_philosopher);
	if (!data->philos)
	{
		free(data->forks);
		return (1);
	}
	init_philosophers(data);
	return (0);
}
