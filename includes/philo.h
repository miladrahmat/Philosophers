/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:39:51 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/10/21 15:23:43 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define TRUE 1
# define FALSE 0
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

/**
 * Structure for each philosopher, containing the information used in each
 * thread.
 * 
 * @param thread Thread initializer.
 * @param id The id of the philosopher.
 * @param eating A flag to see if the philosopher is eating.
 * @param meals_eaten The number of meals the philosopher has eaten.
 * @param times_to_eat The number of times each philosopher must eat
 * before the program ends. (Value of the optional argument given by the user)
 * @param num_philos The number of philosophers created.
 * @param last_meal The time of the last meal eaten by the philosopher
 * (in milliseconds).
 * @param time_to_die The time the philosopher has to start eating again
 * (in milliseconds).
 * @param time_to_eat The time it takes the philosopher to stop eating
 * (in milliseconds).
 * @param time_to_sleep The time it takes the philosopher to stop sleeping
 * (in milliseconds).
 * @param start_time Starting time of the program.
 * @param dead A pointer to the `dead` flag found in `t_prog`.
 * @param fork A mutex for the philosophers fork.
 * @param write_lock A pointer to the `write_lock` mutex found in `t_prog`.
 * @param meal_lock A pointer to the `meal_lock` mutex found in `t_prog`.
 */
typedef struct s_philo
{
	pthread_t		thread;
	size_t			id;
	int				eating;
	size_t			meals_eaten;
	size_t			times_to_eat;
	size_t			num_philos;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				*dead;
	pthread_mutex_t	fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
}	t_philo;

/**
 * A structure for the program, containing every philosopher and mutexes
 * used in the program.
 * 
 * @param dead A death flag to see if any of the philosophers has died.
 * @param write_lock A mutex to to make sure that the printing of the
 * status of the philosophers won't overlap.
 * @param meal_lock A mutex to protect the forks used by the philosopher
 * which is eating.
 * @param philos A structure array containing each philosopher.
 */
typedef struct s_prog
{
	int				dead;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	t_philo			**philos;
}	t_prog;


/******************************************************************************/
/*                                                                            */
/*                                INIT_PHILO.C                                */
/*                                                                            */
/******************************************************************************/

/**
 * Validates that the arguments are numbers that the program can work with.
 * 
 * @param[in] ac The number of arguments.
 * @param[in] av An array of strings containing the arguments.
 * 
 * @returns 1 if the arguments are of the correct type, -1 if not.
 */
int		validate_args(int ac, char **av);
/**
 * Converts the arguments, allocates memory for each philosopher and assigns
 * the correct values to each of them.
 * 
 * @param[in] ac The number of arguments.
 * @param[in] av An array of strings containing the arguments.
 * @param[out] prog The program structure.
 * 
 * @returns 1 in case of success and -1 if allocation fails.
 */
t_prog	*init_philo(char **av, size_t time);

/******************************************************************************/
/*                                                                            */
/*                                  UTILS.C                                   */
/*                                                                            */
/******************************************************************************/

/**
 * Frees the allocated memory.
 * 
 * @param[out] prog The program structure from which to free.
 * @param[in] err An error flag, needs to be less than 0 in case of error.
 * @param[in] index The latest index allocated before an error occured
 * (0 if there wasn't an error).
 * 
 * @returns NULL
 */
t_prog	*free_philos(t_prog *prog, int err, size_t index);

/**
* Computes the length og the given string.
*
* @param[in] str The string to compute.
*
* @returns The number of characters that precede the terminating NULL character.
*/
size_t	ft_strlen(char *str);

/**
* Writes the given string to STDERR.
*
* @param[in] msg The error message to write.
* @param[in] ret_val The return value which the function will exit with.
*/
int		error_msg(char *msg, int ret_val);

/**
 * Converts the given string to unsigned long representation.
 * 
 * @param[in] str The sting to convert.
 * 
 * @returns The converted number.
 */
size_t	ft_atoul(const char *str);

#endif