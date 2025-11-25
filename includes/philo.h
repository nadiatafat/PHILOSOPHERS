/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadgalle <nadgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:46:05 by nadgalle          #+#    #+#             */
/*   Updated: 2025/03/14 16:05:46 by nadgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				philo_id;
	long long		last_meal;
	int				nb_of_meals_eaten;
	int				full_flag;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	pthread_mutex_t	meal_mtx;
	struct s_data	*data;
}			t_philo;

typedef struct s_data
{
	long long		begining;
	int				nb_of_philosopher;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_time_to_eat;
	int				total_meals_eaten;
	int				dead_flag;
	int				all_full_flag;
	pthread_mutex_t	start_mtx;
	pthread_mutex_t	all_full_mtx;
	pthread_mutex_t	dead_mtx;
	pthread_mutex_t	write_mtx;
	pthread_mutex_t	*forks;
	t_philo			*philos;	
}			t_data;

//init process
void		parse_input_data(t_data *data, char **av);
int			init_data(t_data *data);

//philo routine;
int			ft_philo_eat(t_philo *philo);
int			ft_philo_sleep(t_philo *philo);
int			ft_philo_think(t_philo *philo);
void		*ft_philo_routine(void *philosopher);
void		dinner(t_data *data, pthread_t monitor);

//monitoring
int			ft_check_full_flag(t_data *data);
int			ft_check_dead_flag(t_data *data);
void		*ft_monitor_routine(void *data_val);

//utils
int			ft_sleep(long long time_to_sleep, t_philo *philo);
void		ft_print_action(t_philo *philo, char *philo_action);
long long	ft_get_time_diff(long start, long end);
long long	ft_get_time(void);
void		ft_exit_error(char *msg, t_data *data);

// end process
void		ft_join_thread_philos(t_data *data);
void		ft_clean(t_data *data);

#endif