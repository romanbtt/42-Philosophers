/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:54:27 by romanbtt          #+#    #+#             */
/*   Updated: 2021/06/25 10:53:13 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Take_fork lock a fork passed in parameter and print the right action.
*/

void	take_fork(t_philo *philosopher, int index_fork)
{
	pthread_mutex_lock(&philosopher->setting->forks[index_fork]);
	print_action(philosopher, TAKE_FORK);
}

/*
** Put_fork_down unlock a fork passed in parameter.
*/

void	put_fork_down(t_philo *philosopher, int index_fork)
{
	pthread_mutex_unlock(&philosopher->setting->forks[index_fork]);
}
