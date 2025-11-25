/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadgalle <nadgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:45:40 by nadgalle          #+#    #+#             */
/*   Updated: 2025/03/14 16:24:28 by nadgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static long	ft_atol(char *av)
{
	long			i;
	long			n;
	unsigned long	result;

	i = 0;
	n = 1;
	result = 0;
	while ((av[i] >= 9 && av[i] <= 13) || av[i] == ' ')
		i++;
	if (av[i] == '-' || av[i] == '+')
	{
		if (av[i] == '-')
			n = -1;
		i++;
	}
	while (av[i] && (av[i] >= '0' && av[i] <= '9'))
	{
		result = result * 10 + (av[i] - '0');
		i++;
	}
	return ((long)result * n);
}

static int	ft_is_number(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] < '0' || av[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_is_in_limits(char *av)
{
	long	nb;

	nb = ft_atol(av);
	if (nb < 0 || nb > INT_MAX)
		return (0);
	return (1);
}

static int	ft_check_argument(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!ft_is_number(av[i]) || !ft_is_in_limits(av[i]))
			return (0);
		i++;
	}
	return (1);
}

void	parse_input_data(t_data *data, char **av)
{
	if (ft_check_argument(av))
	{
		data->nb_of_philosopher = (int)ft_atol(av[1]);
		data->time_to_die = (int)ft_atol(av[2]);
		data->time_to_eat = (int)ft_atol(av[3]);
		data->time_to_sleep = (int)ft_atol(av[4]);
		if (data->time_to_die < 60 || data->time_to_eat < 60
			|| data->time_to_sleep < 60)
			ft_exit_error("Timestamps must be greater than 60ms.", NULL);
		if (av[5])
			data->nb_of_time_to_eat = (int)ft_atol(av[5]);
		else
			data->nb_of_time_to_eat = -1;
	}
	else
		ft_exit_error("Invalid agument.", NULL);
}
