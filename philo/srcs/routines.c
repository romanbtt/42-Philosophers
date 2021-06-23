/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:22:55 by romanbtt          #+#    #+#             */
/*   Updated: 2021/06/23 15:38:04 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	routine_eat(t_philo *philosopher)
{
	take_fork(philosopher, philosopher->right_fork);
	take_fork(philosopher, philosopher->left_fork);
	pthread_mutex_lock(&philosopher->is_eating);
	philosopher->eat_count++;
	philosopher->time_last_meal = get_time();
	philosopher->time_out = philosopher->time_last_meal
		+ philosopher->setting->time_to_die;
	print_action(philosopher, EATING);
	usleep(philosopher->setting->time_to_eat * 1000);
	pthread_mutex_unlock(&philosopher->is_eating);
	put_fork_down(philosopher, philosopher->right_fork);
	put_fork_down(philosopher, philosopher->left_fork);
}

static void	routine_sleep(t_philo *philosopher)
{
	print_action(philosopher, SLEEPING);
	usleep(philosopher->setting->time_to_sleep * 1000);
}

static void	routine_think(t_philo *philosopher)
{
	print_action(philosopher, THINKING);
}

void	*routines(void *parameter)
{
	t_philo		*philo;
	t_simul		*setting;
	pthread_t	monitor_thread;

	philo = (t_philo *)parameter;
	setting = philo->setting;
	philo->time_last_meal = get_time();
	philo->time_out = philo->time_last_meal + setting->time_to_die;
	if (pthread_create(&monitor_thread, NULL, &monitor, philo) != 0)
		return ((void *)error(ERR_PTHREAD_CREATE));
	while (philo->break_routine == false && setting->someone_die == false)
	{
		if (philo->setting->number_of_philosophers == 1)
			break ;
		routine_eat(philo);
		routine_sleep(philo);
		routine_think(philo);
	}
	if (pthread_join(monitor_thread, NULL) != 0)
		return ((void *)error(ERR_PTHREAD_JOIN));
	return ((void *)1);
}