/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 11:28:59 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/29 00:16:57 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info	s_info;
	t_philo	*philo;

	if (ft_check_arguments(argc, argv, &s_info) == -1 \
		|| ft_initialize(&s_info, &philo) == -1)
		return (EXIT_FAILURE);
	if (ft_launch_all_threads(philo, &s_info) == -1)
		s_info.exit_status = EXIT_FAILURE;
	if (s_info.exit_status != EXIT_FAILURE)
		s_info.dead_philo_index = ft_death_checker(philo, &s_info);
	if (s_info.exit_status != EXIT_FAILURE && s_info.dead_philo_index >= 0)
		ft_print_death(philo + s_info.dead_philo_index, &s_info);
	if (ft_join_all_threads(&s_info) == -1)
		s_info.exit_status = EXIT_FAILURE;
	ft_clean(philo, &s_info);
	return (s_info.exit_status);
}
