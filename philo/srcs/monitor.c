/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:59:14 by romanbtt          #+#    #+#             */
/*   Updated: 2021/06/23 16:51:21 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
