/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:02:00 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/14 19:45:45 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		ft_clean(t_philo *philo, t_info *info);
void		ft_destroy_forks(pthread_mutex_t *forks, size_t n);
static void	ft_free_all(t_philo *philo, t_info *info);

void	ft_clean(t_philo *philo, t_info *info)
{
	pthread_mutex_destroy(&info->print_mutex);
	ft_destroy_forks(info->forks, info->total_philos);
	ft_free_all(philo, info);
}

void	ft_destroy_forks(pthread_mutex_t *forks, size_t n)
{
	while (n-- > 0)
		pthread_mutex_destroy(forks++);
}

void	ft_free_all(t_philo *philo, t_info *info)
{
	free(info->forks);
	free(info->philos_tid);
	free(philo);
}
