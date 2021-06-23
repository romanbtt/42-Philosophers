/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:54:27 by romanbtt          #+#    #+#             */
/*   Updated: 2021/06/22 22:16:08 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philosopher, int index_fork)
{
	pthread_mutex_lock(&philosopher->setting->forks[index_fork]);
	print_action(philosopher, TAKE_FORK);
}

void	put_fork_down(t_philo *philosopher, int index_fork)
{
	pthread_mutex_unlock(&philosopher->setting->forks[index_fork]);
}
