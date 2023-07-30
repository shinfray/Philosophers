/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:38:08 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/30 02:02:09 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*ft_philo(void *arg);
ssize_t		ft_death_checker(t_philo *philo, t_info *info);
void		ft_print_death(t_philo *philo, t_info *info);
static void	*ft_one_philo(t_philo *philo);

void	*ft_philo(void *arg)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)arg;
	info = philo->info;
	philo->left_fork = info->forks + (philo->philo_id % info->total_philos);
	philo->right_fork = info->forks + ((philo->philo_id - 1) % info->total_philos);
	if (info->total_philos == 1)
		return (ft_one_philo(philo));
	if ((philo->philo_id & 1) == 0)
		ft_usleep_philo(info, info->time_to_eat / 2);
	while (info->exit_status != EXIT_FAILURE && info->dead_philo_index < 0 \
			&& info->hungry_philos_atomic > 0)
	{
		ft_print_ts(philo, THINK);
		ft_eat(philo, info);
		ft_sleep(philo, info);
	}
	return (NULL);
}

ssize_t	ft_death_checker(t_philo *philo, t_info *info)
{
	ssize_t		i;
	uintmax_t	timestamp;
	uintmax_t	last_meal;

	i = 0;
	while (info->hungry_philos_atomic > 0)
	{
		last_meal = (philo + i)->last_meal_atomic;
		timestamp = ft_get_ts(&info->launch_time) - last_meal;
		if (timestamp >= info->time_to_die)
			return (i);
		i = (i + 1) % (ssize_t)info->total_philos;
		usleep(100);
	}
	return (-1);
}

void	ft_print_death(t_philo *philo, t_info *info)
{
	uintmax_t	timestamp;

	pthread_mutex_lock(&info->print_mutex);
	timestamp = ft_get_ts(&info->launch_time);
	printf("%ju %zu %s\n", timestamp, philo->philo_id, DEAD);
	pthread_mutex_unlock(&info->print_mutex);
}

static void	*ft_one_philo(t_philo *philo)
{
	ft_print_ts(philo, THINK);
	ft_print_ts(philo, FORK);
	return (NULL);
}
