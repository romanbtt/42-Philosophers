/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 10:45:06 by romanbtt          #+#    #+#             */
/*   Updated: 2021/06/25 11:02:37 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** This function return the sizw of an array.
*/

static int	lenght_array(char *array[])
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

/*
** This function return an error if an element of a array of char is greater 
** than max_int of negative.
*/

static bool	check_neg_and_max_int(char **argv)
{
	long	*arr;
	int		i;

	i = 0;
	arr = malloc(sizeof(long) * lenght_array(argv));
	if (!arr)
		return (error(ERR_MALLOC));
	while (argv[i])
	{
		arr[i] = ft_atol(argv[i]);
		if (arr[i] > 2147483647)
		{
			free(arr);
			return (error(ERR_MAX_INT));
		}
		if (arr[i++] < 0)
		{
			free(arr);
			return (error(ERR_NEG));
		}
	}
	free(arr);
	return (true);
}

/*
** This function free an array of array of char only if argc is equal to 2.
** We check that, because we allocate some memories in the check_arguments's
** function only if argc is equal to 2.
*/

static void	free_to_check(int argc, char **to_check)
{
	if (argc == 2)
		ft_free_array_string(to_check);
}

/*
** We first check if we deal with a one line arguments or not.
** If it is a one_line argument we call the split function. If not
** we move the pointer by one of argv and start with the second parameter.
** (First is the name of the program.)
** Then we send the array of array to _check to the functions of checking.
*/

bool	check_arguments(char **argv, int argc)
{
	char	**to_check;

	if (argc == 2)
		to_check = ft_split_isspace(argv[1]);
	else
		to_check = argv + 1;
	if (check_digits(to_check) == false)
	{
		free_to_check(argc, to_check);
		return (error(ERR_DIGIT));
	}
	if (check_neg_and_max_int(to_check) == false)
	{
		free_to_check(argc, to_check);
		return (false);
	}	
	if (check_number_arguments(to_check) == false)
	{	
		free_to_check(argc, to_check);
		return (error(ERR_NB_ARGS));
	}
	free_to_check(argc, to_check);
	return (true);
}
