/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadgalle <nadgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:48:58 by nadgalle          #+#    #+#             */
/*   Updated: 2025/03/14 15:57:37 by nadgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_take_forks(t_philo *philo)
{
	if (ft_check_dead_flag(philo->data))
		return (0);
	pthread_mutex_lock(philo->first_fork);
	ft_print_action(philo, "has taken a fork");
	if (ft_check_dead_flag(philo->data))
	{
		pthread_mutex_unlock(philo->first_fork);
		return (0);
	}
	pthread_mutex_lock(philo->second_fork);
	ft_print_action(philo, "has taken a fork");
	if (ft_check_dead_flag(philo->data))
	{
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		return (0);
	}
	return (1);
}

int	ft_philo_eat(t_philo *philo)
{
	if (!ft_take_forks(philo))
		return (0);
	ft_print_action(philo, "is eating");
	pthread_mutex_lock(&philo->meal_mtx);
	philo->last_meal = ft_get_time();
	philo->nb_of_meals_eaten++;
	if (philo->data->nb_of_time_to_eat != -1)
	{
		if (philo->nb_of_meals_eaten == philo->data->nb_of_time_to_eat)
			philo->full_flag = 1;
	}
	pthread_mutex_unlock(&philo->meal_mtx);
	if (!ft_sleep(philo->data->time_to_eat, philo))
	{
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		return (0);
	}
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	return (1);
}

int	ft_philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_mtx);
	if (philo->data->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->data->dead_mtx);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->dead_mtx);
	ft_print_action(philo, "is sleeping");
	if (!ft_sleep(philo->data->time_to_sleep, philo))
		return (0);
	return (1);
}

int	ft_philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_mtx);
	if (philo->data->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->data->dead_mtx);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->dead_mtx);
	ft_print_action(philo, "is thinking");
	if (philo->data->nb_of_philosopher % 2 == 1)
	{
		if (philo->data->time_to_die - (philo->data->time_to_eat
				+ philo->data->time_to_sleep) < philo->data->time_to_eat)
			return (1);
		if (!ft_sleep(((philo->data->time_to_eat
						+ philo->data->time_to_sleep)) / 2, philo))
			return (0);
	}
	return (1);
}

int	ft_sleep(long long time_to_sleep, t_philo *philo)
{
	long long	start;
	long long	interval;

	start = ft_get_time();
	interval = ft_get_time() - start;
	while (interval < time_to_sleep)
	{
		pthread_mutex_lock(&philo->data->dead_mtx);
		if (philo->data->dead_flag == 1)
		{
			pthread_mutex_unlock(&philo->data->dead_mtx);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->dead_mtx);
		usleep(100);
		interval = ft_get_time() - start;
	}
	return (1);
}
