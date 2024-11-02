/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- < mrahmat-@student.hive.fi >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:47:11 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/11/02 17:29:44 by mrahmat-         ###   ########.fr       */
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
	usleep(philo->time_to_sleep);
}

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (*(int *)philo->dead == TRUE)
		return ;
	print_routine(philo, "has taken a fork");
	pthread_mutex_lock(&philo->l_fork);
	if (*(int *)philo->dead == TRUE)
		return ;
	print_routine(philo, "has taken a fork");
	philo->last_meal = get_curr_time_ms();
	print_routine(philo, "is eating");
	philo->eating = TRUE;
	usleep(philo->time_to_eat);
	philo->meals_eaten++;
	philo->eating = FALSE;
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		usleep(1);
	while (*(int *)philo->dead == FALSE \
		&& philo->times_to_eat != (int)philo->meals_eaten)
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
