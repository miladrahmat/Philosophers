/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:50:20 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/12/17 15:02:32 by mrahmat-         ###   ########.fr       */
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
	size_t	check;
	size_t	i;

	nbr = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		check = nbr;
		nbr *= 10;
		nbr += str[i] - '0';
		if (check != nbr / 10)
			return (0);
		i++;
	}
	return (nbr);
}

void	ft_wait(size_t wait_time, t_philo *philo, int first_wait)
{
	size_t	start_time;

	start_time = get_curr_time_ms();
	if (first_wait == 1 && wait_time > philo->time_to_eat)
		wait_time = philo->time_to_eat;
	while (1)
	{
		if (philo_dead(philo) < 0)
			return ;
		if (get_curr_time_ms() - start_time >= wait_time)
			return ;
		usleep(100);
	}
}

