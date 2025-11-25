/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadgalle <nadgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:38:03 by nadgalle          #+#    #+#             */
/*   Updated: 2025/03/14 16:25:24 by nadgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_init_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->start_mtx);
	philo->data->begining = ft_get_time();
	pthread_mutex_lock(&philo->meal_mtx);
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(&philo->meal_mtx);
	pthread_mutex_unlock(&philo->data->start_mtx);
}

static void	*ft_one_philo(t_philo *philo)
{
	ft_print_action(philo, "has taken a fork");
	if (!ft_sleep(philo->data->time_to_sleep - 1, philo))
		return (NULL);
	pthread_mutex_lock(&philo->data->dead_mtx);
	philo->data->dead_flag = 1;
	pthread_mutex_unlock(&philo->data->dead_mtx);
	return (NULL);
}

static int	ft_routine(t_philo *philo)
{
	if (!ft_philo_eat(philo))
		return (0);
	if (!ft_philo_sleep(philo))
		return (0);
	if (!ft_philo_think(philo))
		return (0);
	return (1);
}

void	*ft_philo_routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	ft_init_routine(philo);
	if (philo->philo_id % 2 == 0)
	{
		if (!ft_sleep((philo->data->time_to_die - (philo->data->time_to_eat
						+ philo->data->time_to_sleep)) / 2, philo))
			return (0);
	}
	if (philo->data->nb_of_philosopher == 1)
		return (ft_one_philo(philo));
	while (1)
	{
		if (ft_check_dead_flag(philo->data))
			break ;
		if (ft_check_full_flag(philo->data))
			break ;
		if (philo->full_flag)
			break ;
		if (!ft_routine(philo))
			break ;
	}
	return (NULL);
}

void	dinner(t_data *data, pthread_t monitor)
{
	int	i;

	i = 0;
	data->begining = ft_get_time();
	pthread_mutex_lock(&data->start_mtx);
	while (i < data->nb_of_philosopher)
	{
		if (pthread_create(&data->philos[i].thread, NULL
				, ft_philo_routine, &data->philos[i]) != 0)
			ft_exit_error("Failed to create thread.", data);
		i++;
	}
	pthread_mutex_unlock(&data->start_mtx);
}
