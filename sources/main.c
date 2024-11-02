/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- < mrahmat-@student.hive.fi >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:38:38 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/11/02 17:00:18 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	prog->dead = FALSE;
	while (prog->philos[i] != NULL)
	{
		pthread_create(&prog->philos[i]->thread, NULL, \
			&philo_routine, prog->philos[i]);
		usleep(1);
		i++;
	}
	monitoring(prog);
	i = 0;
	while (prog->philos[i] != NULL)
		pthread_join(prog->philos[i++]->thread, NULL);
	free_philos(prog, 1, 0);
	return (0);
}
