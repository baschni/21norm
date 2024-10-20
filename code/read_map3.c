/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/54/19 16:54:28 by baschnit          #+#    #+#             */
/*   Updated: 2024/54/19 16:54:28 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	else if (c >= '\t' && c <= '\r')
		return (1);
	else
		return (0);
}

int	is_number_str(char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (i == 0)
		{
			if (*s != '-' && !ft_isdigit(*s))
				return (0);
		}
		else if (!ft_isdigit(*s))
		{
			return (0);
		}
		s++;
		i++;
	}
	return (1);
}

long	ft_atol(const char *nptr)
{
	long	sign;
	long	n;

	if (!nptr)
		return (0);
	while (ft_isspace(*nptr))
		nptr++;
	sign = 1;
	if (*nptr == '-' || *nptr == '+')
		sign = 1 + '+' - (*(nptr++));
	n = 0;
	while (ft_isdigit(*nptr))
	{
		n = n * 10 + (*nptr - '0');
		nptr++;
	}
	return (n * sign);
}

size_t	ft_split_size(char **split)
{
	size_t	len;

	len = 0;
	while (*split)
	{
		len++;
		split++;
	}
	return (len);
}

// take from libft
void	ft_free_split(void *vtable)
{
	char	**table;
	char	**temp;

	table = (char **) vtable;
	temp = table;
	while (*table)
	{
		free(*table);
		table++;
	}
	free(temp);
}

void	cancel_newline_at_end(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (!len)
		return ;
	line = line + len - 1;
	if (*line == '\n')
		*line = '\0';
}
