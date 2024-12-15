/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- < mrahmat-@student.hive.fi >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:47:11 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/12/15 20:47:19 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->data_lock);
	if (*(int *)philo->dead == TRUE)
	{
		pthread_mutex_unlock(philo->data_lock);
		return (-1);
	}
	pthread_mutex_unlock(philo->data_lock);
	return (1);
}

static void	philo_think(t_philo *philo)
{
	print_routine(philo, "is thinking", 0);
}

static void	philo_sleep(t_philo *philo)
{
	print_routine(philo, "is sleeping", 0);
	ft_wait(philo->time_to_sleep, philo, 0);
}

static void	philo_eat(t_philo *philo)
{
	if (lock_forks_odd(philo) < 0)
		return ;
	pthread_mutex_lock(philo->data_lock);
	philo->meals_eaten++;
	philo->last_meal = get_curr_time_ms();
	pthread_mutex_unlock(philo->data_lock);
	print_routine(philo, "is eating", 0);
	ft_wait(philo->time_to_eat, philo, 0);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	philo_think(philo);
	if (philo->id % 2 == 0)
		ft_wait(philo->time_to_eat - 5, philo, 1);
	while (philo_dead(philo) > 0)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (arg);
}
