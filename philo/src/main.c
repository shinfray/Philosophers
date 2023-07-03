/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 08:47:20 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/03 17:31:19 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mail = 0;

void	*routine(void *arg)
{
	int	i = 0;
	(void)arg;
	while (i++ < 5000000)
		mail++;
	return (NULL);
}

int	main(void)
{
	pthread_t	t1;
	pthread_t	t2;
	
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_join(t1, NULL) != 0)	
		return (3);
	if (pthread_join(t2, NULL) != 0)	
		return (4);
	printf("%d\n", mail);
	return (0);
}
