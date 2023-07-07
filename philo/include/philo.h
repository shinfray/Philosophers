/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 08:48:18 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/07 17:52:09 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <inttypes.h>
# include <stdbool.h>
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

#endif
