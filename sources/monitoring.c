/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- < mrahmat-@student.hive.fi >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:16:35 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/11/03 18:13:31 by mrahmat-         ###   ########.fr       */
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
		if (prog->philos[i]->meals_eaten >= prog->philos[i]->times_to_eat)
			philo_done++;
		i++;
	}
	if (philo_done == prog->philos[0]->num_philos)
	{
		prog->dead = TRUE;
		return (1);
	}
	return (0);
}

static int	check_dead(t_prog *prog)
{
	size_t	i;

	i = 0;
	while (prog->philos[i] != NULL)
	{
		if (get_curr_time_ms() - prog->philos[i]->last_meal >= \
			prog->philos[i]->time_to_die && prog->philos[i]->eating == FALSE)
		{
			prog->dead = TRUE;
			print_routine(prog->philos[i], "has died");
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitoring(void *arg)
{
	t_prog	*prog;

	prog = arg;
	while (TRUE)
	{
		if (check_dead(prog) == 1)
			return (arg);
		if (check_max_meal(prog) == 1)
			return (arg);
	}
	return (arg);
}
