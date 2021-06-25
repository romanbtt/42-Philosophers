/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 16:28:53 by romanbtt          #+#    #+#             */
/*   Updated: 2021/06/23 15:15:19 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philosopher, char *msg)
{
	time_t	time_stamp;

	if (!philosopher->break_routine && !philosopher->setting->someone_die)
	{	
		time_stamp = get_time() - philosopher->setting->start_simulation;
		pthread_mutex_lock(&philosopher->setting->lock_print);
		printf("%11ld %3d %s\n", time_stamp, philosopher->numero + 1, msg);
		pthread_mutex_unlock(&philosopher->setting->lock_print);
	}
}
