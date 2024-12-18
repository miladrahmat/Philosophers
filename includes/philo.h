/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:39:51 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/12/18 13:19:27 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define TRUE 1
# define FALSE 0
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

/**
 * Structure for each philosopher, containing the information used in each
 * thread.
 * 
 * @param thread Thread initializer.
 * @param id The id of the philosopher.
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
 * @param simulation A pointer to the `simulation` flag found in `t_prog`.
 * @param dead A pointer to the `dead` flag found in `t_prog`.
 * @param l_fork A mutex for the philosophers left hand fork.
 * @param r_fork A mutex for the philosophers right hand fork.
 * @param data_lock A pointer to the `data_lock` mutex found in `t_prog`.
 * @param write_lock A pointer to the `write_lock` mutex found in `t_prog`.
 */
typedef struct s_philo
{
	pthread_t		thread;
	size_t			id;
	int				meals_eaten;
	int				times_to_eat;
	size_t			num_philos;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				*simulation;
	int				*dead;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*data_lock;
	pthread_mutex_t	*write_lock;
}	t_philo;

/**
 * A structure for the program, containing every philosopher and mutexes
 * used in the program.
 * 
 * @param simulation A flag indicating when the all the threads have been created
 * and the simulation can start.
 * @param dead A death flag to see if any of the philosophers has died.
 * @param data_lock A mutex to make sure that changing/checking the shared data
 * between the philosophers won't overlap
 * @param write_lock A mutex to make sure that one philosopher is 
 * writing at a time.
 * @param forks A  mutex array for forks.
 * @param philos A structure array containing each philosopher.
 */
typedef struct s_prog
{
	int				simulation;
	int				dead;
	pthread_mutex_t	data_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
	t_philo			**philos;
}	t_prog;

/******************************************************************************/
/*                                                                            */
/*                                INIT_PHILO.C                                */
/*                                                                            */
/******************************************************************************/

/**
 * Converts the arguments, allocates memory for each philosopher and assigns
 * the correct values to each of them.
 * 
 * @param[in] av An array of strings containing the arguments.
 * 
 * @returns The initialized t_prog structure on success,
 * on failure returns `NULL`.
 */
t_prog	*init_philo(char **av);

/******************************************************************************/
/*                                                                            */
/*                               PHILO_ROUTINE.C                              */
/*                                                                            */
/******************************************************************************/

/**
 * Function (passed to pthread_create) to go through the philosophers routine.
 * 
 * @param[in] arg The philosopher stucture.
 * 
 * @returns The given parameter.
 */
void	*philo_routine(void *arg);

/**
 * Checks the dead flag found in `t_philo`.
 * 
 * @param[in] philo The philosopher struct.
 * 
 * @returns 1 if none of the philosophers are dead,
 * -1 if a philosopher has died.
 */
int		philo_dead(t_philo *philo);

/******************************************************************************/
/*                                                                            */
/*                                 GRAB_FORKS.C                               */
/*                                                                            */
/******************************************************************************/

/**
 * A function to grab forks for philosophers with even ids
 * 
 * @param[out] philo The philosopher structure.
 * 
 * @returns 1 if locking the forks were successfull, -1 in case of an error.
 */
int		lock_forks_even(t_philo *philo);

/**
 * A function to grab forks for philosophers with odd ids
 * 
 * @param[out] philo The philosopher structure.
 * 
 * @returns 1 if locking the forks were successfull, -1 in case of an error.
 */
int		lock_forks_odd(t_philo *philo);

/**
 * A function to unlock fork mutexes for philosophers with even ids.
 * 
 * @param[out] philo The philosopher structure.
 */
void	unlock_forks_even(t_philo *philo);

/**
 * A function to unlock fork mutexes for philosophers with odd ids.
 * 
 * @param[out] philo The philosopher structure.
 */
void	unlock_forks_odd(t_philo *philo);

/******************************************************************************/
/*                                                                            */
/*                                MONITORING.C                                */
/*                                                                            */
/******************************************************************************/

/**
 * Checks if any of the philosophers should be dead and modifies the dead flag
 * found in ´t_prog´ (passed to pthread_create).
 * 
 * @param[in] arg The program structure containing each philosopher.
 * 
 * @returns 1 if a philosopher died or 0 if each philosopher has eaten the
 * maximum amount of times (optional argument given to the program).
 */
void	*monitoring(void *arg);

/******************************************************************************/
/*                                                                            */
/*                                 PRINT_MSG.C                                */
/*                                                                            */
/******************************************************************************/

/**
* Writes the given string to STDERR.
*
* @param[in] msg The error message to write.
* @param[in] ret_val The return value which the function will exit with.
*/
int		error_msg(char *msg, int ret_val);

/**
 * Prints the routine message.
 * 
 * @param[in] philo The philosopher writing.
 * @param[in] str The message to write.
 * @param[in] dead A flag to see if a philosopher should be dead.
 */
void	print_routine(t_philo *philo, char *str, int dead);

/******************************************************************************/
/*                                                                            */
/*                                  CLEANUP.C                                 */
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

/******************************************************************************/
/*                                                                            */
/*                                  UTILS.C                                   */
/*                                                                            */
/******************************************************************************/

/**
* Computes the length og the given string.
*
* @param[in] str The string to compute.
*
* @returns The number of characters that precede the terminating NULL character.
*/
size_t	ft_strlen(char *str);

/**
 * Converts the given string to unsigned long representation.
 * 
 * @param[in] str The sting to convert.
 * 
 * @returns The converted number.
 */
size_t	ft_atoul(const char *str);

/**
 * Gets the current time and converts it to milliseconds.
 * 
 * @returns The current time in milliseconds.
 */
size_t	get_curr_time_ms(void);

/**
 * A custom wait function that also checks if a philosopher has died.
 * 
 * @param[in] wait_time The time to wait in milliseconds.
 * @param[in] philo The philosopher struct.
 * @param[in] first_wait A flag indicating the first wait.
 */
void	ft_wait(size_t wait_time, t_philo *philo, int first_wait);

#endif
