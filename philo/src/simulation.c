/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:38:08 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/14 18:18:44 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*ft_philo(void *arg);
bool		ft_is_a_dead(t_philo *philo, t_info *info);

void	*ft_philo(void *arg)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)arg;
	info = philo->info;
	while (philo->n_meal < info->meal_goal \
			&& info->exit_status != EXIT_FAILURE \
			&& info->is_a_dead != true)
	{
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

	i = 0;
	while (info->hungry_philos > 0)
	{
		if ((philo + i)->n_meal == info->meal_goal)
		{
			i = (i + 1) % info->total_philos;
			continue ;
		}
		gettimeofday(&now, NULL);
		timestamp = ft_get_ts((philo + i)->last_meal, now);
		if (timestamp >= info->time_to_die)
		{
			pthread_mutex_lock(&info->print_mutex);
			printf("%ju %zu %s\n", timestamp, philo->philo_id, DEAD);
			pthread_mutex_unlock(&info->print_mutex);
			return (true);
		}
		i = (i + 1) % info->total_philos;
		usleep(10);
	}
	return (false);
}
