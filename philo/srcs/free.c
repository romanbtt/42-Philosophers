/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 16:25:00 by romanbtt          #+#    #+#             */
/*   Updated: 2021/06/25 11:05:16 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** This function destroy all the mutexes and free the memories allocated 
** previously.
*/

void	free_before_exit(t_philo *philo, t_simul *simulation)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&simulation->lock_print);
	pthread_mutex_destroy(&simulation->simulation_running);
	while (i < simulation->number_of_philosophers)
	{
		pthread_mutex_destroy(&simulation->forks[i]);
		pthread_mutex_destroy(&philo[i].is_eating);
		i++;
	}
	free(simulation->forks);
	free(philo);
}

/*
** Simeple function to freed and nulled an element.
*/

static void	ft_free(void *elem)
{
	if (elem)
	{
		free(elem);
		elem = NULL;
	}
}

/*
** This function to freed and array of array of char.
*/

void	ft_free_array_string(char **arr)
{
	int		len;
	int		i;

	len = 0;
	while (arr[len])
		len++;
	i = 0;
	while (i < len)
		ft_free(arr[i++]);
	ft_free(arr);
}
