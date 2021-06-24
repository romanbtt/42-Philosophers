/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 10:45:06 by romanbtt          #+#    #+#             */
/*   Updated: 2021/06/22 22:38:02 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	lenght_array(char *array[])
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

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

static void	free_to_check(int argc, char **to_check)
{
	if (argc == 2)
		ft_free_array_string(to_check);
}

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
