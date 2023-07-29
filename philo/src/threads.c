/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:23:35 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/29 16:24:44 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			ft_launch_all_threads(t_philo *philo, t_info *info);
int			ft_join_all_threads(t_info *philo);
static int	ft_create_threads(t_philo *philo, size_t i);

int	ft_launch_all_threads(t_philo *philo, t_info *info)
{
	const size_t	n = info->total_philos;

	if (gettimeofday(&info->launch_time, NULL) == -1)
		return (-1);
	if (ft_create_threads(philo, 0) == -1)
		return (-1);
	if (n > 1)
		usleep(100);
	return (ft_create_threads(philo, 1));
}

int	ft_join_all_threads(t_info *info)
{
	const size_t	n = info->total_philos;
	size_t			i;

	i = 0;
	while (i < n)
	{
		if (pthread_join(info->philos_tid[i], NULL) != 0)
			return (-1);
		++i;
	}
	return (0);
}

static int	ft_create_threads(t_philo *philo, size_t i)
{
	const size_t	n = philo->info->total_philos;
	t_info			*info;

	info = philo->info;
	while (i < n)
	{
		if (pthread_create(info->philos_tid + i, NULL, &ft_philo, philo + i) != 0)
			return (-1);
		i += 2;
	}
	return (0);

}
