/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:04:08 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/12/10 14:02:47 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	assign_values(char **av, t_philo **philo, size_t id)
{
	size_t	time;

	(*philo)->id = id;
	(*philo)->time_to_die = ft_atoul(av[2]);
	if ((*philo)->time_to_die == 0)
		return (-1);
	(*philo)->time_to_eat = ft_atoul(av[3]);
	if ((*philo)->time_to_eat == 0)
		return (-1);
	(*philo)->time_to_sleep = ft_atoul(av[4]);
	if ((*philo)->time_to_sleep == 0)
		return (-1);
	if (av[5] != NULL)
		(*philo)->times_to_eat = ft_atoul(av[5]);
	else
		(*philo)->times_to_eat = -1;
	if ((*philo)->times_to_eat == 0)
		return (-1);
	(*philo)->meals_eaten = 0;
	time = get_curr_time_ms();
	(*philo)->start_time = time;
	(*philo)->last_meal = time;
	(*philo)->eating = FALSE;
	return (0);
}

void	assign_pointers(t_prog **prog, size_t index, size_t last_index)
{
	(*prog)->philos[index]->num_philos = last_index + 1;
	(*prog)->philos[index]->dead = &(*prog)->dead;
	(*prog)->philos[index]->write_lock = &(*prog)->write_lock;
	(*prog)->philos[index]->meal_lock = &(*prog)->meal_lock;
	(*prog)->philos[index]->dead_lock = &(*prog)->dead_lock;
	(*prog)->philos[index]->l_fork = &(*prog)->forks[index];
	if (index == 0)
		(*prog)->philos[index]->r_fork = &(*prog)->forks[last_index];
	else
		(*prog)->philos[index]->r_fork = &(*prog)->forks[index - 1];
}

int	init_forks(t_prog *prog, size_t last_index)
{
	size_t	i;

	i = 0;
	while (i < last_index)
	{
		if (pthread_mutex_init(&prog->forks[i], NULL) != 0)
			return (-1);
		i++;
	}
	return (1);
}

t_prog	*init_prog(size_t num_philos)
{
	t_prog	*prog;

	prog = malloc(sizeof(t_prog));
	if (prog == NULL)
		return (NULL);
	memset(prog, 0, sizeof(t_prog));
	if (pthread_mutex_init(&prog->write_lock, NULL) != 0)
		return (free_philos(prog, -1, 0));
	if (pthread_mutex_init(&prog->meal_lock, NULL) != 0)
		return (free_philos(prog, -1, 0));
	if (pthread_mutex_init(&prog->dead_lock, NULL) != 0)
		return (free_philos(prog, -1, 0));
	prog->philos = malloc((num_philos + 1) * sizeof(t_philo *));
	if (prog->philos == NULL)
		return (free_philos(prog, -1, 0));
	memset(prog->philos, 0, (num_philos + 1) * sizeof(t_philo *));
	prog->forks = malloc((num_philos + 1) * sizeof(pthread_mutex_t));
	if (prog->forks == NULL)
		return (free_philos(prog, -1, 0));
	memset(prog->forks, 0, (num_philos + 1) * sizeof(pthread_mutex_t));
	if (init_forks(prog, num_philos) < 0)
		return (free_philos(prog, -1, 0));
	return (prog);
}

t_prog	*init_philo(char **av)
{
	size_t	num_philos;
	size_t	philo_i;
	t_prog	*prog;

	num_philos = ft_atoul(av[1]);
	if (num_philos == 0)
		return (NULL);
	prog = init_prog(num_philos);
	if (prog == NULL)
		return (NULL);
	philo_i = 0;
	while (philo_i < num_philos)
	{
		prog->philos[philo_i] = malloc(sizeof(t_philo));
		if (prog->philos[philo_i] == NULL)
			return (free_philos(prog, -1, philo_i));
		if (assign_values(av, &prog->philos[philo_i], philo_i + 1) < 0)
			return (free_philos(prog, -1, philo_i));
		assign_pointers(&prog, philo_i, num_philos - 1);
		philo_i++;
	}
	prog->philos[num_philos] = NULL;
	return (prog);
}
