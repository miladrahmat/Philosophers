/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- < mrahmat-@student.hive.fi >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:38:38 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/12/15 20:13:38 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*sync_simulation(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		pthread_mutex_lock(philo->data_lock);
		if (*philo->simulation == TRUE)
		{
			pthread_mutex_unlock(philo->data_lock);
			break ;
		}
		pthread_mutex_unlock(philo->data_lock);
		usleep(1);
	}
	philo_routine(philo);
	return (arg);
}

static int	join_threads(t_prog	*prog)
{
	size_t	i;

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

static int	create_threads(t_prog *prog)
{
	size_t		i;

	i = 0;
	while (prog->philos[i] != NULL)
	{
		if (pthread_create(&prog->philos[i]->thread, NULL, \
			&sync_simulation, prog->philos[i]) != 0)
		{
			free_philos(prog, 1, 0);
			return (-1);
		}
		i++;
	}
	pthread_mutex_lock(&prog->data_lock);
	prog->simulation = TRUE;
	pthread_mutex_unlock(&prog->data_lock);
	return (1);
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
	t_prog		*prog;

	if (ac < 5 || ac > 6)
		return (error_msg("Invalid number of arguments", 1));
	if (validate_args(ac, av) < 0)
		return (error_msg("Argumets must be positive numbers", 1));
	prog = init_philo(av);
	if (prog == NULL)
		return (error_msg("Failed to initialize program", 1));
	prog->dead = FALSE;
	prog->simulation = FALSE;
	if (create_threads(prog) < 0)
		return (error_msg("Failed to create threads", 1));
	monitoring(prog);
	if (join_threads(prog) < 0)
		return (error_msg("Failed to join threads", 1));
	free_philos(prog, 1, 0);
	return (0);
}
