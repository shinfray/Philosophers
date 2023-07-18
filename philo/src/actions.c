/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:34:41 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/18 17:02:05 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool		ft_eat(t_philo *philo, t_info *info);
void		ft_sleep(t_philo *philo, t_info *info);
void		*ft_signal_as_satiated(t_info *info);
static void	ft_attempt_to_eat_odd(t_philo *philo, t_info *info);
static void	ft_attempt_to_eat_even(t_philo *philo, t_info *info);

bool	ft_eat(t_philo *philo, t_info *info)
{
	if ((philo->philo_id & 1) == 1)
		ft_attempt_to_eat_odd(philo, info);
	else
		ft_attempt_to_eat_even(philo, info);
	if (info->infinite_mode == false)
		++philo->n_meal_atomic;
	if (philo->n_meal_atomic == info->meal_goal)
		return (SATIATED);
	return (HUNGRY);
}

void	*ft_signal_as_satiated(t_info *info)
{
	info->hungry_philos_atomic--;
	return (NULL);
}

void	ft_sleep(t_philo *philo, t_info *info)
{
	ft_print_ts(philo, SLEEP);
	ft_usleep_philo(info, info->time_to_sleep);
}

static void	ft_attempt_to_eat_odd(t_philo *philo, t_info *info)
{
	t_timeval	now;
	size_t		id;
	size_t		n;

	id = philo->philo_id;
	n = info->total_philos;
	pthread_mutex_lock(info->forks + ((id - 1) % n));
	ft_print_ts(philo, FORK);
	pthread_mutex_lock(info->forks + (id % n));
	ft_print_ts(philo, FORK);
	ft_print_ts(philo, EAT);
	gettimeofday(&now, NULL);
	philo->last_meal_atomic = ft_get_ts(info->launch_time, now);
	ft_usleep_philo(info, info->time_to_eat);
	pthread_mutex_unlock(info->forks + ((id - 1) % n));
	pthread_mutex_unlock(info->forks + (id % n));
}

static void	ft_attempt_to_eat_even(t_philo *philo, t_info *info)
{
	t_timeval	now;
	size_t		id;
	size_t		n;

	id = philo->philo_id;
	n = philo->info->total_philos;
	pthread_mutex_lock(info->forks + (id % n));
	ft_print_ts(philo, FORK);
	pthread_mutex_lock(info->forks + ((id - 1) % n));
	ft_print_ts(philo, FORK);
	ft_print_ts(philo, EAT);
	gettimeofday(&now, NULL);
	philo->last_meal_atomic = ft_get_ts(info->launch_time, now);
	ft_usleep_philo(info, info->time_to_eat);
	pthread_mutex_unlock(info->forks + (id % n));
	pthread_mutex_unlock(info->forks + ((id - 1) % n));
}
