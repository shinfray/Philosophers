/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 08:48:18 by shinfray          #+#    #+#             */
/*   Updated: 2023/11/02 15:38:38 by shinfray         ###   ########.fr       */
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
	_Atomic ssize_t	dead_philo_index;
	useconds_t		sleep_value;
	bool			infinite_mode;
	bool			exit_status;
}				t_info;

typedef struct philo
{
	t_info				*info;
	size_t				id;
	_Atomic uintmax_t	last_meal_atomic;
	_Atomic uintmax_t	n_meal_atomic;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
}				t_philo;

/* ************************************************************************** */
/*		PARSING                                                               */
/* ************************************************************************** */
int			ft_check_arguments(int argc, char **argv, t_info *info);

/* ************************************************************************** */
/*		INITIALIXATION                                                        */
/* ************************************************************************** */
int			ft_initialize(t_info *info, t_philo **philo);

/* ************************************************************************** */
/*		THREADS                                                               */
/* ************************************************************************** */
int			ft_launch_all_threads(t_philo *philo, t_info *info);
int			ft_join_all_threads(t_info *info);

/* ************************************************************************** */
/*		SIMULATION                                                            */
/* ************************************************************************** */
void		*ft_philo(void *arg);
ssize_t		ft_death_checker(t_philo *philo, t_info *info);
void		ft_print_death(t_philo *philo, t_info *info);

/* ************************************************************************** */
/*		ACTIONS                                                               */
/* ************************************************************************** */
void		ft_eat(t_philo *philo, t_info *info);
void		ft_sleep(t_philo *philo, t_info *info);

/* ************************************************************************** */
/*		TIME_UTILS                                                            */
/* ************************************************************************** */
int			ft_usleep_philo(t_info *info, uintmax_t ms);
void		ft_print_ts(t_philo *philo, const char *state);
uintmax_t	ft_get_ts(t_timeval *start);

/* ************************************************************************** */
/*		CLEANING                                                              */
/* ************************************************************************** */
void		ft_clean(t_philo *philo, t_info *info);
void		ft_destroy_forks(pthread_mutex_t *forks, size_t n);

#endif
