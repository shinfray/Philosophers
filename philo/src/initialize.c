/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:02:04 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/25 15:13:22 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			ft_initialize(t_info *info, t_philo **philo);
static void	*ft_calloc(size_t count, size_t size);
static int	ft_alloc_all(t_info *info, t_philo **philo);
static void	ft_set_philo_info(t_info *info, t_philo **philo);
static int	ft_init_mutexes(t_info *info);

int	ft_initialize(t_info *info, t_philo **philo)
{
	info->exit_status = EXIT_SUCCESS;
	info->is_a_dead_atomic = false;
	if (ft_alloc_all(info, philo) == -1)
	{
		write(2, "Error: Failed to allocate memory\n", 33);
		return (-1);
	}
	if (ft_init_mutexes(info) == -1)
	{
		write(2, "Error: Failed to initialize mutexes\n", 36);
		free(info->forks);
		free(info->philos_tid);
		return (-1);
	}
	return (0);
}

static void	*ft_calloc(size_t count, size_t size)
{
	const size_t	f_size = size * count;
	void			*ptr;

	ptr = malloc(f_size);
	if (ptr != NULL)
		memset(ptr, 0, f_size);
	return (ptr);
}

static int	ft_alloc_all(t_info *info, t_philo **philo)
{
	const size_t	n = info->total_philos;

	info->philos_tid = ft_calloc(n, sizeof(*info->philos_tid));
	if (info->philos_tid == NULL)
		return (-1);
	info->forks = ft_calloc(n, sizeof(*info->forks));
	if (info->forks == NULL)
	{
		free(info->philos_tid);
		return (-1);
	}
	*philo = ft_calloc(n, sizeof(**philo));
	if (*philo == NULL)
	{
		free(info->philos_tid);
		free(info->forks);
		return (-1);
	}
	ft_set_philo_info(info, philo);
	return (0);
}

static void	ft_set_philo_info(t_info *info, t_philo **philo)
{
	size_t	i;

	i = 0;
	while (i < info->total_philos)
	{
		(*philo + i)->info = info;
		(*philo + i)->philo_id = i + 1;
		++i;
	}
}

static int	ft_init_mutexes(t_info *info)
{
	size_t	i;

	if (pthread_mutex_init(&info->print_mutex, NULL) != 0)
		return (-1);
	i = 0;
	while (i < info->total_philos)
	{
		if (pthread_mutex_init(info->forks + i, NULL) != 0)
		{
			ft_destroy_forks(info->forks, i);
			pthread_mutex_destroy(&info->print_mutex);
			return (-1);
		}
		++i;
	}
	return (0);
}
