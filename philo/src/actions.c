/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:34:41 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/25 14:58:47 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		ft_eat(t_philo *philo, t_info *info);
void		ft_sleep(t_philo *philo, t_info *info);
static void	ft_attempt_to_eat(t_philo *philo, t_info *info);

void	ft_eat(t_philo *philo, t_info *info)
{
	ft_attempt_to_eat(philo, info);
	if (info->infinite_mode == false)
		++philo->n_meal_atomic;
	if (philo->n_meal_atomic == info->meal_goal)
		info->hungry_philos_atomic--;
}

void	ft_sleep(t_philo *philo, t_info *info)
{
	ft_print_ts(philo, SLEEP);
	ft_usleep_philo(info, info->time_to_sleep);
}

static void	ft_attempt_to_eat(t_philo *philo, t_info *info)
{
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	left = info->forks + (philo->philo_id % info->total_philos);
	right = info->forks + ((philo->philo_id - 1) % info->total_philos);
	if ((info->total_philos & 1) == 0 && (philo->philo_id & 1) == 1)
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
	philo->last_meal_atomic = ft_get_ts(&info->launch_time);
	ft_usleep_philo(info, info->time_to_eat);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
}
