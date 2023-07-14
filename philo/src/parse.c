/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 09:49:21 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/14 19:37:06 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int					ft_check_arguments(int argc, char **argv, t_info *info);
static uintmax_t	ft_strtoumax(const char *str, int *err_status);
static int			ft_retrieve_arguments(t_info *info, int argc, char **argv);

int	ft_check_arguments(int argc, char **argv, t_info *info)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "Error: Wrong number of argument\n", 32);
		return (-1);
	}
	if (ft_retrieve_arguments(info, argc, argv) == -1)
	{
		write(2, "Error: Arguments not well formated\n", 35);
		return (-1);
	}
	if (info->total_philos == 0)
	{
		write(2, "Error: at least one philosopher needed\n", 39);
		return (-1);
	}
	if (argc == 6 && info->meal_goal < 1)
	{
		write(2, "Error: at least one meal needed\n", 32);
		return (-1);
	}
	return (0);
}

static uintmax_t	ft_strtoumax(const char *str, int *err_status)
{
	uintmax_t	result;
	uintmax_t	copy;

	*err_status = (*str == '\0');
	if (*err_status != 0)
		return (0);
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		copy = result;
		result = result * 10 + (uintmax_t)(*str++ - '0');
		*err_status = (result < copy);
		if (*err_status != 0)
			return (0);
	}
	*err_status = (*str != '\0');
	return (result);
}

static int	ft_retrieve_arguments(t_info *info, int argc, char **argv)
{
	int	err_status;

	err_status = 0;
	info->total_philos = ft_strtoumax((const char *)argv[1], &err_status);
	if (err_status != 0)
		return (-1);
	info->hungry_philos = info->total_philos;
	info->time_to_die = ft_strtoumax((const char *)argv[2], &err_status);
	if (err_status != 0)
		return (-1);
	info->time_to_eat = ft_strtoumax((const char *)argv[3], &err_status);
	if (err_status != 0)
		return (-1);
	info->time_to_sleep = ft_strtoumax((const char *)argv[4], &err_status);
	if (err_status != 0)
		return (-1);
	info->infinite_mode = !(argc == 6);
	if (argc == 6)
		info->meal_goal = ft_strtoumax((const char *)argv[5], &err_status);
	else
		info->meal_goal = 1;
	if (err_status != 0)
		return (-1);
	return (0);
}
