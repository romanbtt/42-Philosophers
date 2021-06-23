/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:03:01 by romanbtt          #+#    #+#             */
/*   Updated: 2021/06/23 16:59:23 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	join_threads(pthread_t *threads, int nb_philos)
{
	int	i;
	void *ret;

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
	}
	if (join_threads(threads, simulation->number_of_philosophers) == false)
		return (false);
	free(threads);
	return (true);
}
