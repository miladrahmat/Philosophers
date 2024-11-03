/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- < mrahmat-@student.hive.fi >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:47:11 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/11/03 18:13:02 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_think(t_philo *philo)
{
	if (*(int *)philo->dead == TRUE)
		return ;
	print_routine(philo, "is thinking");
}

static void	philo_sleep(t_philo *philo)
{
	if (*(int *)philo->dead == TRUE)
		return ;
	print_routine(philo, "is sleeping");
	usleep(philo->time_to_sleep * 1000);
}

static int	lock_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (*(int *)philo->dead == TRUE)
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
	if (*(int *)philo->dead == TRUE)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (-1);
	}
	print_routine(philo, "has taken a fork");
	return (1);
}

static void	philo_eat(t_philo *philo)
{
	if (lock_forks(philo) < 0)
		return ;
	philo->last_meal = get_curr_time_ms();
	philo->eating = TRUE;
	print_routine(philo, "is eating");
	usleep(philo->time_to_eat * 1000);
	philo->eating = FALSE;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->meals_eaten++;
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		usleep (1);
	while (*(int *)philo->dead == FALSE)
	{
		if (*(int *)philo->dead == FALSE)
			philo_eat(philo);
		if (*(int *)philo->dead == FALSE)
			philo_sleep(philo);
		if (*(int *)philo->dead == FALSE)
			philo_think(philo);
	}
	return (arg);
}
