/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:41:11 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/30 02:07:24 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int					ft_usleep_philo(t_info *info, uintmax_t ms);
void				ft_print_ts(t_philo *philo, const char *state);
uintmax_t			ft_get_ts(t_timeval *start);
static uintmax_t	ft_convert_tod(t_timeval *timeval);

int	ft_usleep_philo(t_info *info, uintmax_t ms)
{
	uintmax_t	ts;
	t_timeval	start;
	t_timeval	now;

	ts = 0;
	gettimeofday(&start, NULL);
	while (ts <= ms)
	{
		if (info->dead_philo_index >= 0 || info->hungry_philos_atomic == 0)
			return (-1);
		usleep(100);
		gettimeofday(&now, NULL);
		ts = ft_get_ts(&start);
	}
	return (0);
}

void	ft_print_ts(t_philo *philo, const char *state)
{
	t_info		*info;
	uintmax_t	timestamp;

	info = philo->info;
	pthread_mutex_lock(&info->print_mutex);
	timestamp = ft_get_ts(&info->launch_time);
	if (info->hungry_philos_atomic > 0 && info->dead_philo_index < 0 \
		&& info->exit_status != EXIT_FAILURE)
		printf("%ju %zu %s\n", timestamp, philo->id, state);
	pthread_mutex_unlock(&info->print_mutex);
}

uintmax_t	ft_get_ts(t_timeval *start)
{
	t_timeval	now;

	gettimeofday(&now, NULL);
	return (ft_convert_tod(&now) - ft_convert_tod(start));
}

static uintmax_t	ft_convert_tod(t_timeval *timeval)
{
	return ((uintmax_t)((timeval->tv_sec * 1000) + (timeval->tv_usec / 1000)));
}
