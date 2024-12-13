/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:17:29 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/12/13 18:37:13 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(char *msg, int ret_val)
{
	if (msg == NULL || *msg == '\0')
		return (ret_val);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (ret_val);
}

void	print_routine(t_philo *philo, char *str, int dead)
{
	if (philo_dead(philo) < 0)
		return ;
	else if (dead == 1)
	{
		pthread_mutex_lock(philo->meal_lock);
		*philo->dead = TRUE;
		pthread_mutex_unlock(philo->meal_lock);
	}
	pthread_mutex_lock(philo->meal_lock);
	printf("%zu %zu %s\n", get_curr_time_ms() - philo->start_time, \
		philo->id, str);
	pthread_mutex_unlock(philo->meal_lock);
}
