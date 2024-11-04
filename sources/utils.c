/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:50:20 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/11/04 11:45:50 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_curr_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (error_msg("Failed to get current time", 1));
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_atoul(const char *str)
{
	size_t	nbr;
	size_t	i;

	nbr = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr *= 10;
		nbr += str[i] - '0';
		i++;
	}
	return (nbr);
}

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
