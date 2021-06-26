/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:03:01 by romanbtt          #+#    #+#             */
/*   Updated: 2021/06/25 12:06:52 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** This function attempt to join all the threads if there are terminated.
*/

static bool	join_threads(pthread_t *threads, int nb_philos)
{
	int		i;
	void	*ret;

	i = 0;
	ret = NULL;
	while (i < nb_philos)
	{
		if (pthread_join(threads[i], &ret) != 0)
		{
			free(threads);
			return (error(ERR_PTHREAD_JOIN));
		}
		if ((int)ret == 0)
			return (false);
		i++;
	}
	return (true);
}

/*
** Start_simulation allocate some memories for each threads of philospher.
** We lock the simulation_running mutex. Ans set the time of the start of
** the simulation.
** Then for each philosphers, we create a thread and lauch the routine.
** We all the threads are create, we call the join_threads function
** to wait all the threads terminate before return in the main function.
*/

bool	start_simulation(t_philo *philos, t_simul *simulation)
{
	pthread_t	*threads;
	int			i;

	i = 0;
	threads = malloc(sizeof(pthread_t *) * simulation->number_of_philosophers);
	if (threads == NULL)
		return (error(ERR_MALLOC));
	pthread_mutex_lock(&simulation->simulation_running);
	simulation->start_simulation = get_time();
	while (i < simulation->number_of_philosophers)
	{
		if (pthread_create(&threads[i], NULL, &routines, &philos[i]) != 0)
			return (error(ERR_PTHREAD_CREATE));
		i++;
		usleep(50);
	}
	if (join_threads(threads, simulation->number_of_philosophers) == false)
		return (false);
	free(threads);
	return (true);
}
