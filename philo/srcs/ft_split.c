/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 10:46:32 by romanbtt          #+#    #+#             */
/*   Updated: 2021/06/22 21:34:02 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	len_s;
	size_t	i;

	ptr = (char *)malloc(len + 1 * sizeof(char));
	if (s == NULL || ptr == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	i = 0;
	while (start < len_s && i < len)
		ptr[i++] = s[start++];
	ptr[i] = '\0';
	return (ptr);
}

static size_t	ft_countchar(const char *str, int opt_delimit)
{
	size_t	i;

	i = 0;
	if (opt_delimit)
	{
		while (str[i] && !ft_isspace(str[i]))
			i++;
	}
	else
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
	}
	return (i);
}

static size_t	ft_countword(const char *str)
{
	size_t	i;
	size_t	nb_words;

	i = 0;
	nb_words = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		while (str[i] && !ft_isspace(str[i]))
			i++;
		nb_words++;
		while (str[i] && ft_isspace(str[i]))
			i++;
	}
	return (nb_words);
}

char	**ft_split_isspace(char const *s)
{
	char	**array;
	size_t	nb_words;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	nb_words = ft_countword(s);
	array = malloc((nb_words + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (i < nb_words)
	{
		s += ft_countchar(s, 0);
		array[i] = ft_substr(s, 0, ft_countchar(s, 1));
		if (!array[i])
			return (NULL);
		s += ft_countchar(s, 1) + ft_countchar(s, 0);
		i++;
	}
	array[i] = NULL;
	return (array);
}
