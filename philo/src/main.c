/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 11:28:59 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/08 11:31:24 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg);
int		ft_launch_all_threads(t_philo *philo);
int		ft_join_all_threads(t_philo *philo);

void	*routine(void *arg)
{
	(void)arg;
	return (NULL);
}

int	ft_launch_all_threads(t_philo *philo)
{
	const size_t	n = philo->total_philosophers;
	size_t			i;

	i = 0;
	while (i < n)
	{
		if (pthread_create(philo->philosophers + i, NULL, &routine, NULL) != 0)
			return (-1);
		++i;
	}
	return (0);
}

int	ft_join_all_threads(t_philo *philo)
{
	const size_t	n = philo->total_philosophers;
	size_t			i;

	i = 0;
	while (i < n)
	{
		if (pthread_join(philo->philosophers[i], NULL) != 0)
			return (-1);
		++i;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	s_philo;

	if (ft_check_arguments(argc, argv, &s_philo) == -1 \
		|| ft_initialize(&s_philo) == -1)
		return (1);
	if (ft_launch_all_threads(&s_philo) == -1 \
		|| ft_join_all_threads(&s_philo) == -1)
	{
		ft_clean(&s_philo);
		return (-1);
	}
	ft_clean(&s_philo);
	return (0);
}
