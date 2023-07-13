/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 11:28:59 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/13 21:08:41 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg);
void	ft_print_ts(t_philo *philo, const char *state);
uintmax_t	ft_convert_tod(t_timeval timeval);
uintmax_t	ft_get_ts(t_timeval start, t_timeval end);
void	ft_attempt_to_eat_odd(t_philo *philo);
void	ft_attempt_to_eat_even(t_philo *philo);

void	ft_attempt_to_eat_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->info->forks + ((philo->philo_id - 1) % philo->info->total_philosophers));
	ft_print_ts(philo, FORK);
	pthread_mutex_lock(philo->info->forks + (philo->philo_id % philo->info->total_philosophers));
	ft_print_ts(philo, FORK);
	ft_print_ts(philo, EAT);
	gettimeofday(&philo->last_meal, NULL);
	usleep((useconds_t)(philo->info->time_to_eat * 1000));
	pthread_mutex_unlock(philo->info->forks + ((philo->philo_id - 1) % philo->info->total_philosophers));
	pthread_mutex_unlock(philo->info->forks + (philo->philo_id % philo->info->total_philosophers));
}

void	ft_attempt_to_eat_even(t_philo *philo)
{
	pthread_mutex_lock(philo->info->forks + (philo->philo_id % philo->info->total_philosophers));
	ft_print_ts(philo, FORK);
	pthread_mutex_lock(philo->info->forks + ((philo->philo_id - 1) % philo->info->total_philosophers));
	ft_print_ts(philo, FORK);
	ft_print_ts(philo, EAT);
	gettimeofday(&philo->last_meal, NULL);
	usleep((useconds_t)(philo->info->time_to_eat * 1000));
	pthread_mutex_unlock(philo->info->forks + (philo->philo_id % philo->info->total_philosophers));
	pthread_mutex_unlock(philo->info->forks + ((philo->philo_id - 1) % philo->info->total_philosophers));
}

void	*routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

	while (philo->n_meal < philo->info->meal_goal)
	{
		ft_print_ts(philo, THINK);
		if ((philo->philo_id & 1) == 1)
			ft_attempt_to_eat_odd(philo);
		else
			ft_attempt_to_eat_even(philo);
		if (philo->info->infinite_mode == false)
			++philo->n_meal;
		ft_print_ts(philo, SLEEP);
		usleep((useconds_t)(philo->info->time_to_sleep * 1000));
	}
	return (NULL);
}

uintmax_t	ft_convert_tod(t_timeval timeval)
{
	return ((uintmax_t)(timeval.tv_sec * 1000 + timeval.tv_usec / 1000));
}

uintmax_t	ft_get_ts(t_timeval start, t_timeval end)
{
	return (ft_convert_tod(end) - ft_convert_tod(start));
}

void	ft_print_ts(t_philo *philo, const char *state)
{
	uintmax_t	timestamp;
	t_timeval	now;

	pthread_mutex_lock(&philo->info->print_ts);
	gettimeofday(&now, NULL);
	timestamp = ft_get_ts(philo->info->launch_time, now);
	printf("%ju %zu %s\n", timestamp, philo->philo_id, state);
	pthread_mutex_unlock(&philo->info->print_ts);
}

int	main(int argc, char **argv)
{
	t_info	s_info;
	t_philo	*philo;

	if (ft_check_arguments(argc, argv, &s_info) == -1 \
		|| ft_initialize(&s_info, &philo) == -1)
		return (EXIT_FAILURE);
	if (gettimeofday(&s_info.launch_time, NULL) == -1 \
		|| ft_launch_all_threads(&s_info, philo) == -1 \
		|| ft_join_all_threads(&s_info) == -1)
		s_info.exit_status = EXIT_FAILURE;
	ft_clean(philo, &s_info);
	return (s_info.exit_status);
}
