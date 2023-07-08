/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 08:48:18 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/08 11:35:25 by shinfray         ###   ########.fr       */
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

typedef struct philo
{
	pthread_t		*philosophers;
	pthread_mutex_t	*forks;
	size_t			total_philosophers;
	uint32_t		time_to_die;
	uint32_t		time_to_eat;	
	uint32_t		time_to_sleep;	
	uint32_t		meal_goal;	
	bool			infinite_mode;
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
void	ft_destroy_mutexes(pthread_mutex_t *forks, size_t n);
void	ft_free_all(t_philo *philo);

/* ************************************************************************** */
/*		THREADS                                                               */
/* ************************************************************************** */
int		ft_launch_all_threads(t_philo *philo);
int		ft_join_all_threads(t_philo *philo);


void	*routine(void *arg);

#endif
