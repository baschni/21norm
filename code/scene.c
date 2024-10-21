#include <stdlib.h>
#include <stdio.h>

#include "scene.h"
#include "config.h"
#include "map.h"
#include "math.h"
#include "libft.h"
#include "vector.h"
#include "auto_free_fdf.h"

t_vect *find_center(t_map *map)
{
	double len;
	t_vect *center;
	int		row;
	int		col;
	int	*current;

	center = v_empty(3);
	if(!center)
		return (NULL);
	len = 0;
	row = 0;
	col = 0;
	current = map->z;
	while (row < map->height)
	{
		len += 1; //sqrt(pow(row, 2) + pow(col, 2) + pow (*current, 2));
		*(center->values) += col;
		*(center->values + 1) += (map->height - row - 1);
		*(center->values + 2) += *current * MAP_Z_SCALE;
		if ((++col) == map->width)
			row++;
		if (col == map->width)
			col = 0;
		current++;
	}
	if (len == 0)
		return (v_free(center));
	//center = v_scale(1 / len, center);
	// free??
	*(center->values) = v_x(center) / len;
	*(center->values + 1) = v_y(center) / len;
	*(center->values + 2) = v_z(center) / len;
	return (center);
}

t_scene *adjust_camera_orientation_to_direction(t_scene *scene)
{
	t_list *mem;
	t_vect *temp;

	if (!fnew(&mem, T_VECT, (void **) &temp,  v_new3d(0, 0, 1)))
		return auto_free(&mem);
	if (v_isparallel(temp, scene->dir))
	{
		if (!new(&mem, T_VECT, (void **) &(scene->orient_y),  v_new3d(0, 1, 0)))
			return auto_free(&mem);
		if (!new(&mem, T_VECT, (void **) &(scene->orient_x),  v_cross(scene->dir, scene->orient_y)))
			return auto_free(&mem);
	}
	else
	{
		if (!new(&mem, T_VECT, (void **) &(scene->orient_x),  v_cross_normed(scene->dir, temp)))
			return auto_free(&mem);
		if (!new(&mem, T_VECT, (void **) &(scene->orient_y),  v_cross(scene->orient_x, scene->dir)))
			return auto_free(&mem);
	}
	auto_free_but_two(&mem, scene->orient_x, scene->orient_y);
	return (scene);
}

int find_min_distance_for_point(double *d_min, t_vect *point, t_scene *scene)
{
	double d_point_center;
	double x;
	double y;
	t_vect *temp;
	t_vect *p_proj;

	temp = v_subst(point, scene->center);
	if(!temp)
		return (0);
	p_proj = v_proj(temp, scene->dir, &d_point_center);
	v_free(temp);
	if (!p_proj)
		return (0);
	x = fabs(v_mult(p_proj, scene->orient_x));
	y = fabs(v_mult(p_proj, scene->orient_y));
	v_free(p_proj);
	x = x / tan(scene->angle/2) - d_point_center;
	y = y * scene->width / scene->height / tan(scene->angle / 2) - d_point_center;
	//printf("distance from center: %f, d_x: %f, d_y: %f\n", d_point_center, x, y);
	if (x > *d_min)
		*d_min = x;
	if (y > *d_min)
		*d_min = y;
	return (1);
}

t_scene *set_initial_cam_position(t_scene *scene)
{
	t_vect *temp;
	
	temp = v_scale(scene->initial_distance, scene->dir);
	if (!temp)
		return (NULL);
	scene->pos = v_subst(scene->center, temp);
	v_free(temp);
	if (!scene->pos)
		return (NULL);
	return (scene);
}

t_scene *find_cam_position(t_map *map, t_scene *scene)
{
	double	d_min;
	int		row;
	int		col;
	t_vect	*temp;
	int 	*current;

	row = 0;
	col = 0;
	d_min = 0;
	current = map->z;
	while (row < map->height)
	{	
		temp = v_new3d(col, map->height - row - 1, *current * MAP_Z_SCALE);
		if(!find_min_distance_for_point(&d_min, temp, scene))
			return v_free(temp);
		v_free(temp);
		if ((++col) == map->width)
			row++;
		if (col == map->width)
			col = 0;
		current++;
	}
	scene->initial_distance = d_min * 1.1;
	return set_initial_cam_position(scene);
}

void no_return_v_free(void *vect)
{
	v_free(vect);
}

void s_free(t_scene *scene)
{
	if (scene->dir)
		v_free(scene->dir);
	if (scene->orient_x)
		v_free(scene->orient_x);
	if (scene->orient_y)
		v_free(scene->orient_y);
	if (scene->pos)
		v_free(scene->pos);
	if (scene->center)
		v_free(scene->center);
	if (scene->edges3d)
		ft_lstclear(&scene->edges3d, no_return_v_free);
	free(scene);
}

t_scene *new_scene(t_map *map, int width, int height)
{	
	t_list	*mem;
	t_scene *scene;

	if (!fnew(&mem, T_SCENE, &scene, malloc(sizeof(t_scene))))
		return (auto_free(&mem));
	scene->dir = NULL;
	scene->pos = NULL;
	scene->orient_x = NULL;
	scene->orient_y = NULL;
	scene->center = NULL;
	scene->edges3d = NULL;
	scene->width = width;
	scene->height = height;
	scene->angle = INIT_CAM_ANGLE / 180.0 * M_PI;
	if (!new(&mem, T_SCENE, &(scene->dir), \
		v_new3d_normed(INIT_CAM_DIR_X, INIT_CAM_DIR_Y, INIT_CAM_DIR_Z)))
		return (auto_free(&mem));
	if (!adjust_camera_orientation_to_direction(scene))
		return (auto_free(&mem));
	if (!new(&mem, T_VECT, &(scene->center), find_center(map)))
		return (auto_free(&mem));
	if (!find_cam_position(map, scene))
		return (auto_free(&mem));
	free_list_leave_contents(&mem);
	return (scene);

}
