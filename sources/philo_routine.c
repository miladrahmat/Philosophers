/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:47:11 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/11/04 12:01:55 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*(int *)philo->dead == TRUE)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (-1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (1);
}

static void	philo_think(t_philo *philo)
{
	if (philo_dead(philo) < 0)
		return ;
	print_routine(philo, "is thinking");
}

static void	philo_sleep(t_philo *philo)
{
	if (philo_dead(philo) < 0)
		return ;
	print_routine(philo, "is sleeping");
	usleep(philo->time_to_sleep * 1000);
}

static void	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (lock_forks_even(philo) < 0)
			return ;
	}
	else
	{
		if (lock_forks_odd(philo) < 0)
			return ;
	}
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_curr_time_ms();
	philo->meals_eaten++;
	philo->eating = TRUE;
	pthread_mutex_unlock(philo->meal_lock);
	print_routine(philo, "is eating");
	usleep(philo->time_to_eat * 1000);
	philo->eating = FALSE;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		usleep (500);
	while (philo_dead(philo) > 0)
	{
		if (philo_dead(philo) > 0)
			philo_eat(philo);
		if (philo_dead(philo) > 0)
			philo_sleep(philo);
		if (philo_dead(philo) > 0)
			philo_think(philo);
		if (philo->id % 2 != 0)
			usleep(500);
	}
	return (arg);
}
