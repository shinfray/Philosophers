/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:41:11 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/18 17:50:42 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int					ft_usleep_philo(t_info *info, uintmax_t ms);
void				ft_print_ts(t_philo *philo, const char *state);
uintmax_t			ft_get_ts(t_timeval *start, t_timeval *end);
static uintmax_t	ft_convert_tod(t_timeval *timeval);

int	ft_usleep_philo(t_info *info, uintmax_t ms)
{
	while (ms-- > 0)
	{
		if (info->is_a_dead_atomic == true)
			return (-1);
		usleep(1000);
	}
	return (0);
}

void	ft_print_ts(t_philo *philo, const char *state)
{
	t_info		*info;
	uintmax_t	timestamp;
	t_timeval	now;

	info = philo->info;
	if (info->is_a_dead_atomic == true \
		|| info->exit_status == EXIT_FAILURE)
		return ;
	pthread_mutex_lock(&info->print_mutex);
	gettimeofday(&now, NULL);
	timestamp = ft_get_ts(&info->launch_time, &now);
	printf("%ju %zu %s\n", timestamp, philo->philo_id, state);
	pthread_mutex_unlock(&info->print_mutex);
}

uintmax_t	ft_get_ts(t_timeval *start, t_timeval *end)
{
	return (ft_convert_tod(end) - ft_convert_tod(start));
}

static uintmax_t	ft_convert_tod(t_timeval *timeval)
{
	return ((uintmax_t)((timeval->tv_sec * 1000) + (timeval->tv_usec / 1000)));
}
