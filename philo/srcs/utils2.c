/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 10:46:05 by romanbtt          #+#    #+#             */
/*   Updated: 2021/06/22 22:36:02 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	if (!dst || !src)
		return (0);
	len = ft_strlen(src);
	i = 0;
	if (size != 0)
	{
		while (src[i] && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}

static char	*ft_strdup(const char *s)
{
	void	*ptr;
	size_t	len;

	len = ft_strlen(s) + 1;
	ptr = malloc(len * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, len);
	return (ptr);
}

static char	*put_in_str(long nb, int size, char *s)
{
	while (nb != 0)
	{
		if ((nb % 10) < 10)
			s[size - 1] = (nb % 10) + 48;
		else
			s[size - 1] = (nb % 10) + 55;
		nb /= 10;
		size--;
	}
	return (s);
}

char	*ft_ltoa(long nb)
{
	long	tmp;
	int		size;
	char	*str;

	tmp = nb;
	size = 0;
	str = 0;
	if (nb == 0)
		return (ft_strdup("0"));
	while (nb)
	{
		nb /= 10;
		size++;
	}
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	str = put_in_str(tmp, size, str);
	return (str);
}
