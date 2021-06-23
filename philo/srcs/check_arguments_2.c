/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 22:36:57 by romanbtt          #+#    #+#             */
/*   Updated: 2021/06/22 22:46:47 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_number_arguments(char **argv)
{
	int	nb_args;
	int	j;

	nb_args = 0;
	j = 0;
	while (argv[j++] != NULL)
		nb_args++;
	if (nb_args < 4 || nb_args > 5)
		return (false);
	return (true);
}

bool	check_digits(char *argv[])
{
	int		i;
	int		j;
	bool	neg;

	i = 0;
	neg = false;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][0] == '-' && !neg)
			{
				j++;
				neg = true;
			}
			if (!ft_isdigit(argv[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
