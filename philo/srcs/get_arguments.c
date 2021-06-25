/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 10:44:50 by romanbtt          #+#    #+#             */
/*   Updated: 2021/06/23 15:00:18 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_range(int *args_philo)
{
	if (args_philo[0] < 1)
		return (error(ERR_PHILO_1));
	if (args_philo[0] > 200)
		return (error(ERR_PHILO_200));
	if (args_philo[1] < 60)
		return (error(ERR_ARG_DIE));
	if (args_philo[2] < 60)
		return (error(ERR_ARG_EAT));
	if (args_philo[3] < 60)
		return (error(ERR_ARG_SLEEP));
	return (true);
}

static void	separate_arguments(char **argv, int *args_philo, bool from_one_line)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (from_one_line == true)
		j = 0;
	while (argv[j] != NULL)
		args_philo[i++] = ft_atoi(argv[j++]);
}

static void	one_line_arguments(char **argv, int *args_philo)
{
	char	**args;

	args = ft_split_isspace(argv[1]);
	separate_arguments(args, args_philo, true);
	ft_free_array_string(args);
}

bool	get_arguments(int argc, char **argv, int *args_philo)
{
	if (check_arguments(argv, argc) == false)
		return (false);
	if (argc == 2)
		one_line_arguments(argv, args_philo);
	else
		separate_arguments(argv, args_philo, false);
	if (check_range(args_philo) == false)
		return (false);
	return (true);
}
