/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:16:35 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/12/13 18:36:57 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_max_meal(t_prog *prog)
{
	size_t	i;
	size_t	philo_done;

	i = 0;
	philo_done = 0;
	if (prog->philos[0]->times_to_eat == -1)
		return (0);
	while (prog->philos[i] != NULL)
	{
		pthread_mutex_lock(&prog->meal_lock);
		if (prog->philos[i]->meals_eaten >= prog->philos[i]->times_to_eat)
			philo_done++;
		pthread_mutex_unlock(&prog->meal_lock);
		i++;
	}
	pthread_mutex_lock(&prog->meal_lock);
	if (philo_done == prog->philos[0]->num_philos)
	{
		prog->dead = TRUE;
		pthread_mutex_unlock(&prog->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&prog->meal_lock);
	return (0);
}

static int	check_dead(t_prog *prog)
{
	size_t	i;

	i = 0;
	while (prog->philos[i] != NULL)
	{
		pthread_mutex_lock(&prog->meal_lock);
		if (get_curr_time_ms() - prog->philos[i]->last_meal >= \
			prog->philos[i]->time_to_die)
		{
			pthread_mutex_unlock(&prog->meal_lock);
			print_routine(prog->philos[i], "died", 1);
			return (1);
		}
		pthread_mutex_unlock(&prog->meal_lock);
		i++;
	}
	return (0);
}

void	*monitoring(void *arg)
{
	t_prog	*prog;

	prog = arg;
	while (prog->simulation == FALSE)
		usleep(10);
	while (TRUE)
	{
		if (check_dead(prog) == 1)
			return (arg);
		if (check_max_meal(prog) == 1)
			return (arg);
	}
	return (arg);
}
