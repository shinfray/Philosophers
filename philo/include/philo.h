/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 08:48:18 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/14 19:49:27 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <inttypes.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"
# define DEAD "died"
# define HUNGRY 0
# define SATIATED 1

typedef struct timeval	t_timeval;

typedef struct info
{
	size_t			total_philos;
	pthread_t		*philos_tid;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	t_timeval		launch_time;
	uintmax_t		time_to_die;
	uintmax_t		time_to_eat;	
	uintmax_t		time_to_sleep;	
	uintmax_t		meal_goal;	
	_Atomic size_t	hungry_philos_atomic;
	_Atomic bool	is_a_dead_atomic;
	bool			infinite_mode;
	bool			exit_status;
}				t_info;

typedef struct philo
{
	t_info		*info;
	size_t		philo_id;
	t_timeval	last_meal;
	uintmax_t	n_meal;
}				t_philo;

/* ************************************************************************** */
/*		PARSING                                                               */
/* ************************************************************************** */
int			ft_check_arguments(int argc, char **argv, t_info *info);

/* ************************************************************************** */
/*		INITIALIXATION                                                        */
/* ************************************************************************** */
int			ft_initialize(t_info *info, t_philo **philo);
void		*ft_calloc(size_t count, size_t size);

/* ************************************************************************** */
/*		THREADS                                                               */
/* ************************************************************************** */
int			ft_launch_all_threads(t_philo *philo, t_info *info);
int			ft_join_all_threads(t_info *info);

/* ************************************************************************** */
/*		SIMULATION                                                            */
/* ************************************************************************** */
void		*ft_philo(void *arg);
bool		ft_is_a_dead(t_philo *philo, t_info *info);

/* ************************************************************************** */
/*		ACTIONS                                                               */
/* ************************************************************************** */
bool		ft_eat(t_philo *philo, t_info *info);
void		ft_sleep(t_philo *philo, t_info *info);
void		*ft_signal_as_satiated(t_info *info);

/* ************************************************************************** */
/*		TIME_UTILS                                                            */
/* ************************************************************************** */
void		ft_print_ts(t_philo *philo, const char *state);
uintmax_t	ft_get_ts(t_timeval start, t_timeval end);

/* ************************************************************************** */
/*		CLEANING                                                              */
/* ************************************************************************** */
void		ft_clean(t_philo *philo, t_info *info);
void		ft_destroy_forks(pthread_mutex_t *forks, size_t n);

#endif
