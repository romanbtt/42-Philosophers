/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 10:42:22 by romanbtt          #+#    #+#             */
/*   Updated: 2021/06/25 10:38:37 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
** Simulation's struct store the general setting of the simulation.
** Philosophers's struct store the variables needed by each philosopher.
** Args_philo store the inputs of the program in an array of int.
** Memset initialize all int of args_philo with the value of -1 because the
** last parameter is optional. It will facilitate the way to know if the
** optional parameter is pass or not.
** Get_arguments function is called to get the inputs and checked them.
** Initialization initiates the two struct with the inputs values.
** Start_simulation starts the threads to launch the simulation.
** A mutex is used to block the running thread until the simulation is not
** finished. (Only a security since pthread_join is used to wait for
** all threads).
** Finally free_before_exit is called to free and destroy memories allocation
** and mutexes.
*/

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
