/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:32:49 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/18 19:33:28 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "map.h"

int	m_get_z(t_map *map, int x, int y)
{
	int	*z;

	z = map->z + map->width * y + x;
	return (*z);
}

int	*m_get_z_ptr(t_map *map, int x, int y)
{
	int	*z;

	z = map->z + map->width * y + x;
	return (z);
}

void	m_set_z(t_map *map, int x, int y, int z)
{
	*(map->z + map->width * y + x) = z;
}

void	m_free(t_map *map)
{
	if (map->height > 0 && map->width > 0)
		free(map->z);
	free(map);
}
