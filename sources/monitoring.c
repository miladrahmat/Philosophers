/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- < mrahmat-@student.hive.fi >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:16:35 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/11/02 17:02:28 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* static int	check_max_meal(t_prog *prog)
{
	size_t	i;

	i = 0;
	while (prog->philos[i] != NULL)
	{
		if (prog->philos[i]->meals_eaten >= prog->philos[i]->times_to_eat)
		{
			prog->dead = TRUE;
			return (1);
		}
		i++;
	}
	return (0);
} */

static int	check_dead(t_prog *prog)
{
	size_t	i;
	size_t	time;

	i = 0;
	time = get_curr_time_ms();
	while (prog->philos[i] != NULL)
	{
		if (time - prog->philos[i]->last_meal >= prog->philos[i]->time_to_die \
			&& prog->philos[i]->eating == FALSE)
		{
			prog->dead = TRUE;
			print_routine(prog->philos[i], "has died");
			return (1);
		}
		i++;
	}
	return (0);
}

int	monitoring(t_prog *prog)
{
	while (TRUE)
	{
		if (check_dead(prog) == 1)
			return (1);
		/* if (check_max_meal(prog) == 1)
			return (0); */
	}
	return (0);
}
