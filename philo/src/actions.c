/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:34:41 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/29 15:58:18 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		ft_eat(t_philo *philo, t_info *info);
void		ft_sleep(t_philo *philo, t_info *info);
static void	ft_attempt_to_eat(t_philo *philo, t_info *info);

void	ft_eat(t_philo *philo, t_info *info)
{
	if (info->dead_philo_index >= 0)
		return ;
	ft_attempt_to_eat(philo, info);
	if (info->infinite_mode == false)
		++philo->n_meal_atomic;
	if (info->infinite_mode == false && philo->n_meal_atomic == info->meal_goal)
		info->hungry_philos_atomic--;
}

void	ft_sleep(t_philo *philo, t_info *info)
{
	if (info->dead_philo_index >= 0)
		return ;
	ft_print_ts(philo, SLEEP);
	ft_usleep_philo(info, info->time_to_sleep);
}

static void	ft_attempt_to_eat(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print_ts(philo, FORK);
	pthread_mutex_lock(philo->right_fork);
	ft_print_ts(philo, FORK);
	ft_print_ts(philo, EAT);
	philo->last_meal_atomic = ft_get_ts(&info->launch_time);
	ft_usleep_philo(info, info->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
