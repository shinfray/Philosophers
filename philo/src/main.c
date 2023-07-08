/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 11:28:59 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/08 11:34:20 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg);

void	*routine(void *arg)
{
	(void)arg;
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
