/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:21:49 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/18 19:34:18 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "map.h"
#include "libft.h"
#include "read_map3.h"

void	*free_line_map_fd(char *line, t_map *map, int fd, char *error_msg)
{
	if (line)
		free(line);
	if (map)
		m_free(map);
	if (fd >= 0)
	{
		close(fd);
	}
	if (error_msg)
	{
		ft_putstr_fd("Error while parsing map: ", STDERR_FILENO);
		ft_putendl_fd(error_msg, STDERR_FILENO);
	}
	return (NULL);
}

void	*free_splits_and_map(t_list **splits, t_map *map, char *error_msg)
{
	ft_lstclear(splits, ft_free_split);
	return (free_line_map_fd(NULL, map, -1, error_msg));
}

t_list	*list_item_from_split_inner(char **split, t_map *map, int fd)
{
	t_list	*new;

	if (map->width != (-1) && ft_split_size(split) != (size_t) map->width)
	{
		ft_free_split(split);
		return (free_line_map_fd(NULL, map, fd, "lines of map have different width"));
	}
	else if (map->width == (-1))
	{
		map->width = ft_split_size(split);
		if (map->width == 0 || map->width > INT_MAX)
		{
			ft_free_split(split);
			return (free_line_map_fd(NULL, map, fd, "empty map or map too large"));
		}
	}
	new = ft_lstnew(split);
	if (!new)
	{
		ft_free_split(split);
		return (free_line_map_fd(NULL, map, fd, "lines of map have different width"));
	}
	return (new);
}

t_list	*list_item_from_split(char *line, char sep, t_map *map, int fd)
{
	char	**split;

	split = ft_split(line, sep);
	if (!split)
		return (free_line_map_fd(line, map, fd, "not enough memory available"));
	free(line);
	return (list_item_from_split_inner(split, map, fd));
}
