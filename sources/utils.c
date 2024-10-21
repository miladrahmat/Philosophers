/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:50:20 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/10/21 14:58:55 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
    return (i);
}

int	error_msg(char *msg, int ret_val)
{
	if (msg == NULL || *msg == '\0')
		return (ret_val);
	write(2, msg, ft_strlen(msg));
	return (ret_val);
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

t_prog	*free_philos(t_prog *prog, int err, size_t index)
{
	size_t	i;

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
	free(prog);
	return (NULL);
}
