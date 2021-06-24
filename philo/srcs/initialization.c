/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 11:04:36 by romanbtt          #+#    #+#             */
/*   Updated: 2021/06/22 21:56:37 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

bool	initialization(t_philo **philos, t_simul *simulation, int *args_philo)
{
	if (init_simulation(simulation, args_philo) == false)
		return (false);
	if (init_philosophers(philos, simulation) == false)
		return (false);
	return (true);
}
