/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:47:11 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/12/10 11:39:00 by mrahmat-         ###   ########.fr       */
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
	print_routine(philo, "is thinking", 0);
}

static void	philo_sleep(t_philo *philo)
{
	if (philo_dead(philo) < 0)
		return ;
	print_routine(philo, "is sleeping", 0);
	ft_wait(philo->time_to_sleep, philo);
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
	philo->meals_eaten++;
	philo->eating = TRUE;
	pthread_mutex_unlock(philo->meal_lock);
	print_routine(philo, "is eating", 0);
	ft_wait(philo->time_to_eat, philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_curr_time_ms();
	philo->eating = FALSE;
	pthread_mutex_unlock(philo->meal_lock);
	if (philo->id % 2 == 0)
		unlock_forks_even(philo);
	else
		unlock_forks_odd(philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		ft_wait(philo->time_to_eat, philo);
	while (philo_dead(philo) > 0)
	{
		if (philo_dead(philo) > 0)
			philo_think(philo);
		if (philo_dead(philo) > 0)
			philo_eat(philo);
		if (philo_dead(philo) > 0)
			philo_sleep(philo);
	}
	return (arg);
}
