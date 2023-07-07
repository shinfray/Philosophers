/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 08:47:20 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/07 18:09:15 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*routine(void *arg);

// void	*routine(void *arg)
// {
// 	(void)arg;
// 	return (NULL);
// }
uint32_t	ft_strtoul(const char *str, int *err_status);
int	ft_set_philo(t_philo *philo, int argc, char **argv);

uint32_t	ft_strtoul(const char *str, int *err_status)
{
	uint32_t	result;
	uint32_t	copy;

	*err_status = (*str == '\0');
	if (*err_status != 0)
		return (0);
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		copy = result;
		result = result * 10 + (uint32_t)(*str++ - '0');
		*err_status = (result < copy);
		if (*err_status != 0)
			return (0);
	}
	*err_status = (*str != '\0');
	return (result);
}

int	ft_set_philo(t_philo *philo, int argc, char **argv)
{
	int	err_status;

	err_status = 0;
	philo->total_philosophers = ft_strtoul((const char *)argv[1], &err_status);
	if (err_status != 0)
		return (-1);
	philo->time_to_die = ft_strtoul((const char *)argv[2], &err_status);
	if (err_status != 0)
		return (-1);
	philo->time_to_eat = ft_strtoul((const char *)argv[3], &err_status);
	if (err_status != 0)
		return (-1);
	philo->time_to_sleep = ft_strtoul((const char *)argv[4], &err_status);
	if (err_status != 0)
		return (-1);
	philo->infinite_mode = (argc == 6);
	if (argc == 6)
		philo->meal_goal = ft_strtoul((const char *)argv[5], &err_status);
	if (err_status != 0)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	s_philo;
	
	(void)argv;
	(void)s_philo;
	if (argc < 5 || argc > 6)
	{
		write(2, "Wrong number of argumet\n", 24);
		return (1);
	}
	ft_set_philo(&s_philo, argc, argv);
	// if (pthread_create(&t1, NULL, &routine, NULL) != 0)
	// 	return (1);
	// if (pthread_join(t2, NULL) != 0)	
	// 	return (4);
	return (0);
}
