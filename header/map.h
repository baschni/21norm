/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:02:58 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/18 19:30:28 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct s_map
{
	int	width;
	int	height;
	int	*z;
}	t_map;

t_map	*read_map(char *filename);

void	m_free(t_map *map);
int		m_get_z(t_map *map, int x, int y);
int		*m_get_z_ptr(t_map *map, int x, int y);
void	m_set_z(t_map *map, int x, int y, int z);

#endif