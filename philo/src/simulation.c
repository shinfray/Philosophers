/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:38:08 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/26 00:04:42 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*ft_philo(void *arg);
bool		ft_death_checker(t_philo *philo, t_info *info);
static bool	ft_print_death(t_philo *philo, t_info *info);
static void	*ft_one_philo(t_philo *philo);

void	*ft_philo(void *arg)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)arg;
	info = philo->info;
	if (info->total_philos == 1)
		return (ft_one_philo(philo));
	if ((info->total_philos & 1) == 1 && (philo->philo_id & 1) == 1)
		ft_usleep_philo(info, 10);
	while (info->exit_status != EXIT_FAILURE && info->is_a_dead_atomic != true \
			&& info->hungry_philos_atomic > 0)
	{
		ft_print_ts(philo, THINK);
		ft_eat(philo, info);
		ft_sleep(philo, info);
	}
	return (NULL);
}

bool	ft_death_checker(t_philo *philo, t_info *info)
{
	size_t		i;
	uintmax_t	timestamp;
	uintmax_t	last_meal;

	i = 0;
	while (info->hungry_philos_atomic > 0)
	{
		last_meal = (philo + i)->last_meal_atomic;
		timestamp = ft_get_ts(&info->launch_time) - last_meal;
		if (timestamp >= info->time_to_die)
			return (ft_print_death(philo + i, info));
		i = (i + 1) % info->total_philos;
	}
	return (false);
}

static bool	ft_print_death(t_philo *philo, t_info *info)
{
	uintmax_t	timestamp;

	timestamp = ft_get_ts(&info->launch_time);
	pthread_mutex_lock(&info->print_mutex);
	printf("%ju %zu %s\n", timestamp, philo->philo_id, DEAD);
	pthread_mutex_unlock(&info->print_mutex);
	return (true);
}

static void	*ft_one_philo(t_philo *philo)
{
	ft_print_ts(philo, THINK);
	ft_print_ts(philo, FORK);
	return (NULL);
}
