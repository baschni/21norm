/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edges_from_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 01:25:44 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/21 12:06:44 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "libft.h"
#include "map.h"
#include "edge.h"

int	add_edge_to_list(t_list **edges, int start[3], int end[3])
{
	t_list	*new;
	t_edge	*edge;

	edge = e_create3d(start, end);
	if (!edge)
		return (0);
	new = ft_lstnew(edge);
	if (!new)
	{
		e_free(edge);
		return (0);
	}
	ft_lstadd_back(edges, new);
	return (1);
}

int	loop_edges_from_map(t_map *map, t_list **edges)
{
	int	row;
	int	col;
	int	*current;

	row = 0;
	col = 0;
	current = map->z;
	while (row < map->height)
	{
		if (col > 0)
			if (!add_edge_to_list(edges, (int[3]){col - 1, (map->height - row - 1), \
			*(current - 1) * MAP_Z_SCALE}, (int[3]){col, (map->height - row - 1), *current * MAP_Z_SCALE}))
				return (0);
		if (row > 0)
			if (!add_edge_to_list(edges, (int[3]){col, (map->height - row), \
			*(current - map->width) * MAP_Z_SCALE}, (int[3]){col, (map->height - row - 1), *current * MAP_Z_SCALE}))
				return (0);
		if ((++col) == map->width)
			row++;
		if (col == map->width)
			col = 0;
		current++;
	}
	return (1);
}

t_list	*read_edges_from_map(t_map *map)
{
	t_list	*edges;

	edges = (NULL);
	if (!loop_edges_from_map(map, &edges))
	{
		ft_lstclear(&edges, &e_free);
		return (NULL);
	}
	return (edges);
}
