/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 11:28:59 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/08 12:19:10 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg);

void	*routine(void *arg)
{
	t_philo	*philo;	

	philo = (t_philo *)arg;
	printf("%zu %d %d %d\n", philo->total_philosophers, philo->time_to_die, philo->time_to_eat, philo->time_to_sleep);
	return (NULL);
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
