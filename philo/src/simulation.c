/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:38:08 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/18 16:58:32 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*ft_philo(void *arg);
bool		ft_is_a_dead(t_philo *philo, t_info *info);
static void	*ft_one_philo(t_philo *philo);

void	*ft_philo(void *arg)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)arg;
	info = philo->info;
	while (philo->n_meal_atomic < info->meal_goal \
			&& info->exit_status != EXIT_FAILURE \
			&& info->is_a_dead_atomic != true)
	{
		if (info->total_philos == 1)
			return (ft_one_philo(philo));
		ft_print_ts(philo, THINK);
		if (ft_eat(philo, info) == SATIATED)
			return (ft_signal_as_satiated(info));
		ft_sleep(philo, info);
	}
	return (NULL);
}

bool	ft_is_a_dead(t_philo *philo, t_info *info)
{
	size_t		i;
	t_timeval	now;
	uintmax_t	timestamp;
	uintmax_t	last_meal;

	i = 0;
	while (info->hungry_philos_atomic > 0)
	{
		if ((philo + i)->n_meal_atomic == info->meal_goal)
		{
			i = (i + 1) % info->total_philos;
			continue ;
		}
		last_meal = (philo + i)->last_meal_atomic;
		gettimeofday(&now, NULL);
		timestamp = ft_get_ts(info->launch_time, now) - last_meal;
		if (timestamp >= info->time_to_die)
		{
			timestamp = ft_get_ts((philo + i)->info->launch_time, now);
			pthread_mutex_lock(&info->print_mutex);
			printf("%ju %zu %s\n", timestamp, (philo + i)->philo_id, DEAD);
			pthread_mutex_unlock(&info->print_mutex);
			return (true);
		}
		i = (i + 1) % info->total_philos;
	}
	return (false);
}

static void	*ft_one_philo(t_philo *philo)
{
	ft_print_ts(philo, THINK);
	ft_print_ts(philo, FORK);
	return (NULL);
}
