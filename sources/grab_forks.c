/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- < mrahmat-@student.hive.fi >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:53:13 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/12/15 20:05:19 by mrahmat-         ###   ########.fr       */
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
	print_routine(philo, "has taken a fork", 0);
	pthread_mutex_lock(philo->l_fork);
	if (philo_dead(philo) < 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (-1);
	}
	print_routine(philo, "has taken a fork", 0);
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
	print_routine(philo, "has taken a fork", 0);
	if (philo->num_philos == 1)
	{
		ft_wait(philo->time_to_die, philo);
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
	print_routine(philo, "has taken a fork", 0);
	return (1);
}

void	unlock_forks_even(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	unlock_forks_odd(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}
