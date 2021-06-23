/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 10:42:22 by romanbtt          #+#    #+#             */
/*   Updated: 2021/06/23 12:03:53 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_simul	simulation;
	t_philo	*philosophers;
	int		args_philo[5];

	memset(args_philo, -1, sizeof(args_philo));
	if (get_arguments(argc, argv, args_philo) == true)
	{
		if (initialization(&philosophers, &simulation, args_philo) == false)
			return (1);
		if (start_simulation(philosophers, &simulation) == false)
		{
			free_before_exit(philosophers, &simulation);
			return (1);
		}
		pthread_mutex_lock(&simulation.simulation_running);
		free_before_exit(philosophers, &simulation);
	}
	else
		return (1);
	return (0);
}
