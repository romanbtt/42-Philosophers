/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:59:14 by romanbtt          #+#    #+#             */
/*   Updated: 2021/06/25 15:17:12 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** This function monitor if a philosopher has died.
** If the current time is greater than the limit time a philospher had, it
** will print the message about his death. Ans set the flags to stop the
** simulation.
*/

static bool	monitor_philo_die(t_philo *philo)
{
	if (get_time() > philo->time_out)
	{
		print_action(philo, DIED);
		philo->setting->someone_die = true;
		philo->break_routine = true;
		pthread_mutex_unlock(&philo->is_eating);
		pthread_mutex_unlock(&philo->setting->simulation_running);
		return (true);
	}
	return (false);
}

/*
** The function monitor how many meals a philosopher had.
** It will first check if the optional argument is activated.
**(setting->number_of_time_each_philosophers_must_eat grater than 0)
** And if the number of meals of a philospher is grater or equal than the
** numbers of meals he can has. Then it will set the flags to stop the
** ability of a philospher taking a meal.
*/

static bool	monitor_eat_limit(t_philo *philo)
{
	int	nb_meals;

	nb_meals = philo->setting->number_of_time_each_philosophers_must_eat;
	if (nb_meals > 0)
	{
		if (philo->eat_count >= nb_meals)
		{
			pthread_mutex_unlock(&philo->is_eating);
			pthread_mutex_unlock(&philo->setting->simulation_running);
			philo->break_routine = true;
			return (true);
		}	
	}
	return (false);
}

/*
** This function run forever and check the number of times a philospher can eat
** and if a philospher has died.
** It will only do these verfication is the philospher is not currently eating.
** To avoid the ability of a philospher eating and died in the same time.
*/

void	*monitor(void *parameter)
{
	t_philo	*philo;

	philo = (t_philo *)parameter;
	while (true)
	{
		pthread_mutex_lock(&philo->is_eating);
		if (monitor_eat_limit(philo) == true)
			return ((void *)0);
		if (monitor_philo_die(philo) == true)
			return ((void *)0);
		pthread_mutex_unlock(&philo->is_eating);
		usleep(1);
	}
}
