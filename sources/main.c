/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- < mrahmat-@student.hive.fi >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:38:38 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/11/09 13:46:10 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	join_threads(t_prog	*prog, pthread_t monitor_thread)
{
	size_t	i;

	if (pthread_join(monitor_thread, NULL) != 0)
	{
		free_philos(prog, 1, 0);
		return (-1);
	}
	i = 0;
	while (prog->philos[i] != NULL)
	{
		if (pthread_join(prog->philos[i]->thread, NULL) != 0)
		{
			free_philos(prog, 1, 0);
			return (-1);
		}
		i++;
	}
	return (0);
}

static pthread_t	create_threads(t_prog *prog)
{
	pthread_t	monitor_thread;
	size_t		i;

	i = 0;
	if (pthread_create(&monitor_thread, NULL, &monitoring, prog) != 0)
	{
		free_philos(prog, 1, 0);
		return (0);
	}
	while (prog->philos[i] != NULL)
	{
		if (pthread_create(&prog->philos[i]->thread, NULL, \
			&philo_routine, prog->philos[i]) != 0)
		{
			free_philos(prog, 1, 0);
			return (0);
		}
		i++;
	}
	return (monitor_thread);
}

static int	validate_args(int ac, char **av)
{
	int		num_args;
	int		av_i;
	size_t	str_i;

	num_args = ac;
	av_i = 1;
	while (av_i < num_args)
	{
		str_i = 0;
		while (av[av_i][str_i] != '\0')
		{
			if (av[av_i][str_i] < '0' || av[av_i][str_i] > '9')
				return (-1);
			str_i++;
		}
		av_i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	pthread_t	monitor_thread;
	t_prog		*prog;

	if (ac < 5 || ac > 6)
		return (error_msg("Invalid number of arguments", 1));
	if (validate_args(ac, av) < 0)
		return (error_msg("Argumets must be positive numbers", 1));
	prog = init_philo(av);
	if (prog == NULL)
		return (error_msg("Failed to initialize program", 1));
	prog->dead = FALSE;
	monitor_thread = create_threads(prog);
	if (monitor_thread == 0)
		return (error_msg("Failed to create threads", 1));
	if (join_threads(prog, monitor_thread) < 0)
		return (error_msg("Failed to join threads", 1));
	free_philos(prog, 1, 0);
	return (0);
}
