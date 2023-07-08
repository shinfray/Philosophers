/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 08:47:20 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/08 10:05:44 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*routine(void *arg);

// void	*routine(void *arg)
// {
// 	(void)arg;
// 	return (NULL);
// }

int	main(int argc, char **argv)
{
	t_philo	s_philo;
	
	if (ft_check_arguments(argc, argv, &s_philo) == -1)
		return (1);
	if (ft_initialize(&s_philo) == -1)
		return (2);
	// if (pthread_create(&t1, NULL, &routine, NULL) != 0)
	// 	return (1);
	// if (pthread_join(t2, NULL) != 0)	
	// 	return (4);
	ft_clean(&s_philo);
	return (0);
}
