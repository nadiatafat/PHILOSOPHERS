/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadgalle <nadgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:44:26 by nadgalle          #+#    #+#             */
/*   Updated: 2025/03/14 16:03:52 by nadgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_exit_error(char *msg, t_data *data)
{
	printf("%s\n", msg);
	if (data)
	{
		free(data->forks);
		free(data->philos);
	}
	exit(EXIT_FAILURE);
}

long long	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		ft_exit_error("Gettimeofday failure.", NULL);
	return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
}

long long	ft_get_time_diff(long start, long end)
{
	return (end - start);
}

void	ft_print_action(t_philo *philo, char *philo_action)
{
	long long	begining;

	if (ft_check_dead_flag(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->start_mtx);
	begining = philo->data->begining;
	pthread_mutex_unlock(&philo->data->start_mtx);
	pthread_mutex_lock(&philo->data->write_mtx);
	printf("%lld %d %s\n",
		ft_get_time_diff(begining, ft_get_time()),
		philo->philo_id, philo_action);
	pthread_mutex_unlock(&philo->data->write_mtx);
}
