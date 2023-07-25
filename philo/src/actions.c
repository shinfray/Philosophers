/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:34:41 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/25 12:40:57 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool		ft_eat(t_philo *philo, t_info *info);
void		ft_sleep(t_philo *philo, t_info *info);
void		*ft_signal_as_satiated(t_info *info);
static void	ft_attempt_to_eat_even(t_philo *philo, t_info *info);
static void	ft_attempt_to_eat_odd(t_philo *philo, t_info *info);

bool	ft_eat(t_philo *philo, t_info *info)
{
	if ((info->total_philos & 1) == 0)
		ft_attempt_to_eat_even(philo, info);
	else
		ft_attempt_to_eat_odd(philo, info);
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

static void	ft_attempt_to_eat_even(t_philo *philo, t_info *info)
{
	t_timeval		now;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	left = info->forks + (philo->philo_id % info->total_philos);
	right = info->forks + ((philo->philo_id - 1) % info->total_philos);
	if ((philo->philo_id & 1) == 1)
	{
		first = right;
		second = left;
	}
	else
	{
		first = left;
		second = right;
	}
	pthread_mutex_lock(first);
	ft_print_ts(philo, FORK);
	pthread_mutex_lock(second);
	ft_print_ts(philo, FORK);
	ft_print_ts(philo, EAT);
	gettimeofday(&now, NULL);
	philo->last_meal_atomic = ft_get_ts(&info->launch_time, &now);
	ft_usleep_philo(info, info->time_to_eat);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
}

static void	ft_attempt_to_eat_odd(t_philo *philo, t_info *info)
{
	t_timeval		now;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	left = info->forks + (philo->philo_id % info->total_philos);
	right = info->forks + ((philo->philo_id - 1) % info->total_philos);
	if ((philo->philo_id & 1) == 1)
	{
		first = right;
		second = left;
	}
	else
	{
		first = left;
		second = right;
	}
	pthread_mutex_lock(first);
	ft_print_ts(philo, FORK);
	pthread_mutex_lock(second);
	ft_print_ts(philo, FORK);
	ft_print_ts(philo, EAT);
	gettimeofday(&now, NULL);
	philo->last_meal_atomic = ft_get_ts(&info->launch_time, &now);
	ft_usleep_philo(info, info->time_to_eat);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
}
