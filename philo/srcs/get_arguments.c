/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 10:44:50 by romanbtt          #+#    #+#             */
/*   Updated: 2021/06/25 10:51:52 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** This function return an error if the inputs are out range.
** Numbers of philosophers is less than one. It will die without eating since 
** there is only one fork available.
** Number of philosphers is greater than 200.
** Time to die, time to eat, time to sleep is less than 60 ms.
*/

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

/*
** This function transform in int and put in an array of int.
** A different index j is used if the inputs came from from a one argument or
** several arguments. If it a one argument case. We don't have the name of the
** program as first argument. So we start we an index of 0. Otherwise we start
** with an index of 1.
*/

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

/*
** The function separate the argument with a split if the inputs came as only
** one argument. Then we call separate_arguments to put in an array of int.
*/

static void	one_line_arguments(char **argv, int *args_philo)
{
	char	**args;

	args = ft_split_isspace(argv[1]);
	separate_arguments(args, args_philo, true);
	ft_free_array_string(args);
}

/*
** First, we send the raw inputs to checking.
** Then if the numbers of arguments is 2, we send the argument to the
** separation process of one argument. Otherwise we send them to the
** transformation process in int.
** Then we check the range of the inputs.
*/

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
