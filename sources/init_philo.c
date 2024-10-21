/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:04:08 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/10/21 15:31:27 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_values(char **av, t_philo **philo, size_t id, size_t time)
{
	(*philo)->id = id;
	(*philo)->time_to_die = ft_atoul(av[2]);
	(*philo)->time_to_eat = ft_atoul(av[3]);
	(*philo)->time_to_sleep = ft_atoul(av[4]);
	if (av[5] != NULL)
		(*philo)->times_to_eat = ft_atoul(av[5]);
	(*philo)->meals_eaten = 0;
	(*philo)->start_time = time;
	(*philo)->eating = FALSE;
}

t_prog	*init_philo(char **av, size_t time)
{
	size_t	num_philos;
	size_t	philo_i;
	t_prog	*prog;

	num_philos = ft_atoul(av[1]);
	prog = malloc(sizeof(t_prog));
	if (prog == NULL)
		return (NULL);
	prog->philos = malloc((num_philos + 1) * sizeof(t_philo *));
	if (prog->philos == NULL)
		return (free_philos(prog, -1, 0));
	philo_i = 0;
	while (philo_i < num_philos)
	{
		prog->philos[philo_i] = malloc(sizeof(t_philo));
		if (prog->philos[philo_i] == NULL)
			return (free_philos(prog, -1, philo_i));
		assign_values(av, &prog->philos[philo_i], philo_i + 1, time);
		prog->philos[philo_i]->dead = &prog->dead;
		philo_i++;
	}
	prog->philos[num_philos] = NULL;
	return (prog);
}

int	validate_args(int ac, char **av)
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
			if (av[av_i][str_i] < '0' && av[av_i][str_i] > '9')
				return (-1);
			str_i++;
		}
		av_i++;
	}
	return (1);
}
