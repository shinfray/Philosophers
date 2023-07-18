/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:23:35 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/18 15:08:05 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_launch_all_threads(t_philo *philo, t_info *info);
int		ft_join_all_threads(t_info *philo);

int	ft_launch_all_threads(t_philo *philo, t_info *info)
{
	const size_t	n = info->total_philos;
	size_t			i;

	i = 0;
	while (i < n)
	{
		if (pthread_create(info->philos_tid + i, NULL, &ft_philo, philo++) != 0)
			return (-1);
		++i;
	}
	return (0);
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
