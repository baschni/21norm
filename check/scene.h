/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:26:44 by baschnit          #+#    #+#             */
/*   Updated: 2024/12/02 19:43:29 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <pthread.h>

# include "vector.h"
# include "map.h"
# include "edge.h"
# include "libft.h"
# include "canvas.h"

typedef struct s_view
{
	double	angle;
	t_vect	*dir;
	t_vect	*orient_x;
	t_vect	*orient_y;
	t_vect	*pos;
	t_vect	*center;

	double	cam_dist;
	double	scale_parallel;
	int		projection_mode;
}	t_view;

typedef struct s_scene
{
	void			*mlx;
	void			*mlx_win;
	unsigned int	width;
	unsigned int	height;
	size_t			edges;

	t_view			initial;
	t_view			render;
	t_view			target;

	int				is_rendering;
	int				render_request;

	t_edge			**edges3d;
	t_canvas		*previous_canvas;
	t_canvas		*canvas;
}	t_scene;

t_view		*adjust_camera_orientation_to_direction(t_view *view);
t_scene		*init_scene(t_map *map, void *mlx, double z_scale);
t_scene		*new_scene(t_map *map, int width, int height, double z_scale);
t_scene		*find_cam_position(t_map *map, t_scene *scene, double z_scale);
t_scene		*set_cam_position(t_scene *scene, t_view *view, t_vect **pos);
int			copy_view(t_view *source, t_view *target);
int			set_parallel_scale(double *scale, t_edge **edges, t_scene *scene);
void		project_edges_to_image(t_edge **edges3d, \
t_scene *scene, t_canvas *canvas);

void		init_view(t_view *view);
int			copy_view(t_view *source, t_view *target);
t_canvas	*create_empty_canvas(t_scene *scene);

void		free_canvas(t_canvas *canvas, t_scene *scene);
void		free_view(t_view *view);
void		free_scene(t_scene *scene);

#endif