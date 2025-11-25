/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadgalle <nadgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:42:09 by nadgalle          #+#    #+#             */
/*   Updated: 2025/03/14 15:51:16 by nadgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_check_full(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philosopher)
	{
		pthread_mutex_lock(&data->philos[i].meal_mtx);
		if (data->philos[i].full_flag != 1)
		{
			pthread_mutex_unlock(&data->philos[i].meal_mtx);
			return (0);
		}
		pthread_mutex_unlock(&data->philos[i].meal_mtx);
		i++;
	}
	pthread_mutex_lock(&data->all_full_mtx);
	data->all_full_flag = 1;
	pthread_mutex_unlock(&data->all_full_mtx);
	return (1);
}

int	ft_check_full_flag(t_data *data)
{
	pthread_mutex_lock(&data->all_full_mtx);
	if (data->all_full_flag == 1)
	{
		pthread_mutex_unlock(&data->all_full_mtx);
		return (1);
	}
	pthread_mutex_unlock(&data->all_full_mtx);
	return (0);
}

static int	ft_check_death(t_philo *philo)
{
	long long	time_last_meal;
	long long	begining;

	pthread_mutex_lock(&philo->meal_mtx);
	time_last_meal = ft_get_time_diff(philo->last_meal, ft_get_time());
	pthread_mutex_unlock(&philo->meal_mtx);
	if (time_last_meal >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->dead_mtx);
		philo->data->dead_flag = 1;
		pthread_mutex_unlock(&philo->data->dead_mtx);
		pthread_mutex_lock(&philo->data->start_mtx);
		begining = philo->data->begining;
		pthread_mutex_unlock(&philo->data->start_mtx);
		usleep(1000);
		pthread_mutex_lock(&philo->data->write_mtx);
		printf("%lld %d died\n",
			ft_get_time_diff(begining, ft_get_time()), philo->philo_id);
		pthread_mutex_unlock(&philo->data->write_mtx);
		return (0);
	}
	return (1);
}

int	ft_check_dead_flag(t_data *data)
{
	pthread_mutex_lock(&data->dead_mtx);
	if (data->dead_flag == 1)
	{
		pthread_mutex_unlock(&data->dead_mtx);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_mtx);
	return (0);
}

void	*ft_monitor_routine(void *data_val)
{
	t_data	*data;
	int		i;

	data = (t_data *)data_val;
	while (1)
	{
		i = 0;
		if (ft_check_full(data) == 1)
		{
			return (NULL);
		}
		while (i < data->nb_of_philosopher)
		{
			if (!ft_check_death(&data->philos[i]))
				return (NULL);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}
