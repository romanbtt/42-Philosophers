/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 11:04:36 by romanbtt          #+#    #+#             */
/*   Updated: 2021/06/25 11:25:24 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** This function malloc and create some memories to each philosophers's struct.
** Then in a while loop we init each struct with :
** - Numero of the philosopher
** - Index of the right fork and left fork. (left fork is the index + 1 modulo
** the number of philosopher to obtain a 0 to the last philosopher.)
** - Eat_count to 0 for each.
** - A pointer to the simulation's struct to each.
** - A flag break_routine to each.
** - The mutexes of forks.
** - A mutex (is_eating) who will serve as a flag to know if a philosopher is
** eating ot not because we don't want a philospher eat and die as the same
** time.
*/

static bool	init_philosophers(t_philo **philosophers, t_simul *simulation)
{
	t_philo	*tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(t_philo) * simulation->number_of_philosophers);
	if (tmp == NULL)
		return (error(ERR_MALLOC));
	while (i < simulation->number_of_philosophers)
	{
		tmp[i].numero = i;
		tmp[i].right_fork = i;
		tmp[i].left_fork = (i + 1) % simulation->number_of_philosophers;
		tmp[i].eat_count = 0;
		tmp[i].setting = simulation;
		tmp[i].break_routine = false;
		pthread_mutex_init(&simulation->forks[i], NULL);
		pthread_mutex_init(&tmp[i].is_eating, NULL);
		i++;
	}
	*philosophers = tmp;
	return (true);
}

/*
** This function initialize the simuation struct with the inputs of the
**program.
** It mallocs soem memories to store the fork's mutexes.
** Then initialize the lock_print mutex who will serve to control the printing
** flow. (Ex. Two threads who wants to print is the same time.)
** And initialize the simulation_running's mutex to block the program at a
** certain point in the program. (Ex. If the main thread reach the free
** function before all the threads has not terminated.)
*/

static bool	init_simulation(t_simul *simulation, int *args_philo)
{
	int	number_of_forks;

	simulation->number_of_philosophers = args_philo[0];
	number_of_forks = simulation->number_of_philosophers;
	simulation->time_to_die = args_philo[1];
	simulation->time_to_eat = args_philo[2];
	simulation->time_to_sleep = args_philo[3];
	simulation->number_of_time_each_philosophers_must_eat = args_philo[4];
	simulation->forks = malloc(sizeof(t_mutex) * number_of_forks);
	simulation->someone_die = false;
	if (simulation->forks == NULL)
		return (error(ERR_MALLOC));
	pthread_mutex_init(&simulation->lock_print, 0);
	pthread_mutex_init(&simulation->simulation_running, 0);
	return (true);
}

/*
** Simple function to call init_simulation and init_philosophers.
*/

bool	initialization(t_philo **philos, t_simul *simulation, int *args_philo)
{
	if (init_simulation(simulation, args_philo) == false)
		return (false);
	if (init_philosophers(philos, simulation) == false)
		return (false);
	return (true);
}
