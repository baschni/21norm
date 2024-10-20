/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:26:44 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/18 19:28:29 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vector.h"
# include "map.h"
# include "edge.h"
# include "libft.h"

typedef struct s_scene
{
	void			*mlx;
	void			*mlx_win;
	unsigned int	width;
	unsigned int	height;

	double			angle;
	t_vect			*dir;
	t_vect			*orient_x;
	t_vect			*orient_y;
	t_vect			*pos;

	t_vect			*center;
	double			initial_distance;

	t_list			*edges3d;
}	t_scene;

t_scene	*new_scene(t_map *map, int width, int height);
void	s_free(t_scene *scene);

#endif