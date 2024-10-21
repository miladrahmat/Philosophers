/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:38:38 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/10/21 15:25:05 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	get_curr_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (error_msg("Failed to get current time", 1));
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	main(int ac, char **av)
{
	t_prog	*prog;
	size_t	i;
	size_t	time;

	if (ac < 5 || ac > 6)
		return (error_msg("Invalid number of arguments", 1));
	time = get_curr_time_ms();
	if (time == 1)
		return (1);
	if (validate_args(ac, av) < 0)
		return (error_msg("Argumets must be numbers", 1));
	prog = init_philo(av, time);
	if (prog == NULL)
		return (error_msg("Failed to initialize program", 1));
	i = 0;
	while (prog->philos[i] != NULL)
	{
		printf("id: %zu, die: %zu, eat: %zu, sleep: %zu eat times: %zu start time: %zu\n", prog->philos[i]->id, \
			prog->philos[i]->time_to_die, prog->philos[i]->time_to_eat, prog->philos[i]->time_to_sleep, \
			prog->philos[i]->times_to_eat, prog->philos[i]->start_time);
			i++;
	}
	free_philos(prog, 1, 0);
}
