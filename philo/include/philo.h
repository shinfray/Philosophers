/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 08:48:18 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/10 17:45:31 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <inttypes.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"
# define DEAD "died"

typedef struct philo
{
	struct timeval	launch_time;
	struct timeval	now;
	pthread_t		*philosophers;
	pthread_mutex_t	*forks;
	size_t			total_philosophers;
	uintmax_t		time_to_die;
	uintmax_t		time_to_eat;	
	uintmax_t		time_to_sleep;	
	uintmax_t		meal_goal;	
	bool			infinite_mode;
	pthread_mutex_t	print_ts;
}				t_philo;

/* ************************************************************************** */
/*		PARSING                                                               */
/* ************************************************************************** */
int		ft_check_arguments(int argc, char **argv, t_philo *philo);

/* ************************************************************************** */
/*		INITIALIXATION                                                        */
/* ************************************************************************** */
int		ft_initialize(t_philo *philo);

/* ************************************************************************** */
/*		CLEANING                                                              */
/* ************************************************************************** */
void	ft_clean(t_philo *philo);
void	ft_destroy_forks(pthread_mutex_t *forks, size_t n);
void	ft_free_all(t_philo *philo);

/* ************************************************************************** */
/*		THREADS                                                               */
/* ************************************************************************** */
int		ft_launch_all_threads(t_philo *philo);
int		ft_join_all_threads(t_philo *philo);


void	*routine(void *arg);

#endif
