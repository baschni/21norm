/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:22:35 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/21 07:49:26 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map.h"
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "read_map2.h"
#include "read_map3.h"

t_list	*read_first_line(int fd, t_map **map)
{
	char	*first_line;

	if (fd == -1)
		return (free_line_map_fd(NULL, NULL, -1, "file could not be opened"));
	first_line = get_next_line(fd);
	if (!first_line)
		return (free_line_map_fd(first_line, NULL, fd, "empty file or file could not be read"));
	cancel_newline_at_end(first_line);
	*map = malloc(sizeof(t_map));
	if (!*map)
		return (free_line_map_fd(first_line, NULL, fd, "not enough memory available"));
	(*map)->width = -1;
	(*map)->height = -1;
	return (list_item_from_split(first_line, ' ', *map, fd));
}

t_list	*read_remaining_lines(t_list **splits, int fd, t_map *map)
{
	t_list	*new;
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		cancel_newline_at_end(line);
		new = list_item_from_split(line, ' ', map, fd);
		if (!new)
		{
			ft_lstclear(splits, &ft_free_split);
			return (NULL);
		}
		ft_lstadd_back(splits, new);
		line = get_next_line(fd);
	}
	close(fd);
	return (*splits);
}

t_map	*loop_split(char **split, t_list **splits, t_map *map, int *pos)
{
	long	nbr;

	while (*split)
	{
		nbr = ft_atol(*split);
		if (!is_number_str(*split) || nbr > INT_MAX || nbr < INT_MIN)
			return (free_splits_and_map(splits, map, "z-value in file has wrong range or wrong characters"));
		*pos = (int) nbr;
		split++;
		pos++;
	}
	return (map);
}

t_map	*read_splits_to_map(t_list **splits, t_map *map)
{
	t_list	*lline;
	size_t	height;
	char	**split;
	int		*pos;

	height = ft_lstsize(*splits);
	if (height > INT_MAX || height <= 0)
		return (free_splits_and_map(splits, map, "file has too many lines"));
	map->height = height;
	map->z = malloc(sizeof(int) * map->width * map->height);
	if (!map->z)
		return (free_splits_and_map(splits, map, "not enough memory"));
	pos = map->z;
	lline = *splits;
	while (lline)
	{
		split = lline->content;
		if (!loop_split(split, splits, map, pos))
			return (NULL);
		pos = pos + map->width;
		lline = lline->next;
	}
	ft_lstclear(splits, ft_free_split);
	return (map);
}

// check if read had any errors if not assume that NULL is because the file terminated (could also be memory allocation error!)
//transform list to map
// not possible because we dont know if error value can be interpreted!
t_map	*read_map(char *filename)
{
	int		fd;
	t_map	*map;
	t_list	*splits;

	fd = open(filename, O_RDONLY);
	splits = read_first_line(fd, &map);
	if (!map)
		return (NULL);
	splits = read_remaining_lines(&splits, fd, map);
	if (!splits)
		return (NULL);
	map = read_splits_to_map(&splits, map);
	if (!map)
		return (NULL);
	return (map);
}
