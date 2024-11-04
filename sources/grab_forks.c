/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:53:13 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/11/04 11:53:35 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lock_forks_even(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (philo_dead(philo) < 0)
	{
		pthread_mutex_unlock(philo->r_fork);
		return (-1);
	}
	print_routine(philo, "has taken a fork");
	if (philo->num_philos == 1)
	{
		usleep(philo->time_to_die * 1000);
		pthread_mutex_unlock(philo->r_fork);
		return (-1);
	}
	pthread_mutex_lock(philo->l_fork);
	if (philo_dead(philo) < 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (-1);
	}
	print_routine(philo, "has taken a fork");
	return (1);
}

int	lock_forks_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (philo_dead(philo) < 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		return (-1);
	}
	print_routine(philo, "has taken a fork");
	if (philo->num_philos == 1)
	{
		usleep(philo->time_to_die * 1000);
		pthread_mutex_unlock(philo->l_fork);
		return (-1);
	}
	pthread_mutex_lock(philo->r_fork);
	if (philo_dead(philo) < 0)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (-1);
	}
	print_routine(philo, "has taken a fork");
	return (1);
}
