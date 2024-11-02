/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- < mrahmat-@student.hive.fi >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:04:08 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/11/02 17:14:36 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	assign_values(char **av, t_philo **philo, size_t id, size_t time)
{
	(*philo)->id = id;
	(*philo)->time_to_die = ft_atoul(av[2]);
	(*philo)->time_to_eat = ft_atoul(av[3]) * 1000;
	(*philo)->time_to_sleep = ft_atoul(av[4]) * 1000;
	if (av[5] != NULL)
		(*philo)->times_to_eat = ft_atoul(av[5]);
	else
		(*philo)->times_to_eat = -1;
	(*philo)->meals_eaten = 0;
	(*philo)->start_time = time;
	(*philo)->last_meal = time;
	(*philo)->eating = FALSE;
	if (pthread_mutex_init(&(*philo)->l_fork, NULL) != 0)
		return (-1);
	return (0);
}

void	assign_pointers(t_prog **prog, size_t index, size_t last_index)
{
	(*prog)->philos[index]->dead = &(*prog)->dead;
	(*prog)->philos[index]->write_lock = &(*prog)->write_lock;
	(*prog)->philos[index]->meal_lock = &(*prog)->meal_lock;
	if (index != 0)
		(*prog)->philos[index]->r_fork = &(*prog)->philos[index - 1]->l_fork;
	if (index == last_index)
		(*prog)->philos[0]->r_fork = &(*prog)->philos[index]->l_fork;
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
	if (pthread_mutex_init(&prog->meal_lock, NULL) != 0)
		return (free_philos(prog, -1, 0));
	if (pthread_mutex_init(&prog->write_lock, NULL) != 0)
		return (free_philos(prog, -1, 0));
	while (philo_i < num_philos)
	{
		prog->philos[philo_i] = malloc(sizeof(t_philo));
		if (prog->philos[philo_i] == NULL)
			return (free_philos(prog, -1, philo_i));
		if (assign_values(av, &prog->philos[philo_i], philo_i + 1, time) < 0)
			return (free_philos(prog, -1, 0));
		assign_pointers(&prog, philo_i, num_philos - 1);
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
