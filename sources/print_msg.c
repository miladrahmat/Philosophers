/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:17:29 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/11/15 18:02:34 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(char *msg, int ret_val)
{
	if (msg == NULL || *msg == '\0')
		return (ret_val);
	write(2, msg, ft_strlen(msg));
	return (ret_val);
}

void	print_routine(t_philo *philo, char *str, int dead)
{
	pthread_mutex_lock(philo->write_lock);
	if (dead == 1)
	{
		pthread_mutex_lock(philo->dead_lock);
		*philo->dead = TRUE;
		pthread_mutex_unlock(philo->dead_lock);
	}
	else if (philo_dead(philo) < 0)
	{
		pthread_mutex_unlock(philo->write_lock);
		return ;
	}
	printf("%zu %zu %s\n", get_curr_time_ms() - philo->start_time, \
		philo->id, str);
	pthread_mutex_unlock(philo->write_lock);
}
