/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:04:04 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/11/15 17:04:25 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_mutexes(t_prog *prog)
{
	size_t	i;

	i = 0;
	if (prog->forks != NULL)
	{
		while (i < prog->philos[0]->num_philos)
			pthread_mutex_destroy(&prog->forks[i++]);
	}
	pthread_mutex_destroy(&prog->write_lock);
	pthread_mutex_destroy(&prog->dead_lock);
	pthread_mutex_destroy(&prog->meal_lock);
}

t_prog	*free_philos(t_prog *prog, int err, size_t index)
{
	size_t	i;

	destroy_mutexes(prog);
	if (err < 0)
	{
		i = index;
		while (i > 0)
			free(prog->philos[i--]);
		free(prog->philos[i]);
	}
	else
	{
		i = 0;
		while (prog->philos[i] != NULL)
			free(prog->philos[i++]);
		free(prog->philos[i]);
	}
	free(prog->philos);
	free(prog->forks);
	free(prog);
	return (NULL);
}
