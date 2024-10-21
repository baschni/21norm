/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:52:30 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/21 11:05:09 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <math.h>
#include <stdlib.h>

#include "config.h"
#include "map.h"
#include "libft.h"
#include "edge.h"
#include "scene.h"
#include "edges_from_map.h"
#include "edges_to_screen.h"
#include "auto_free_fdf.h"

#include "debug.h"
#include "mlx.h"
#include <stdio.h>

// void initialise_camera(t_scene *cam, t_map *map);
// void m_free(t_map *map);
// t_list *read_edges_from_map(t_map *map);

// int free_cam_map_edges(camp, map, edges2d, edges3d)
// {
// 	error_message("not enough memory...")
// }

#define ROUND(d) ( (int) ((d) + ((d) > 0 ? 0.5 : - 0.5)) )

typedef struct s_data
{
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	void	*dst;

	if (x < 0 || y < 0)
		return;

	//printf("x: %i y: %i\n", x, y);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	print_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	double	slope;
	int		x;
	int		y;

	x = x0;
	y = y0;
	printf("print line from (%i, %i) to (%i, %i)\n", x0, y0, x1, y1);
	if (x0 == x1)
	{
		while (y != y1)
		{
			my_mlx_pixel_put(data, x, y, color);
			y0 < y1 ? y++ : y--;
		}
		return;
	}

	slope = (double) (y1 - y0) / (double) (x1 - x0);
	while (x != x1)
	{
		my_mlx_pixel_put(data, x, y, color);
		if (x0 < x1)
			x++;
		else
			x--;
		y = ROUND((double) y0 + (double) (x - x0) * slope);
	}
}

void	render_scene(t_scene *scene)
{
	t_list	*edges2d;

	edges2d = project_edges_to_viewport(scene->edges3d, scene);
	print_edges2d(edges2d);

	t_data img;

	img.img = mlx_new_image(scene->mlx, scene->width, scene->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// my_mlx_pixel_put(&img, 10, 10, 0x00FFFFFF);
	// my_mlx_pixel_put(&img, 800, 400, 0x00FFFF00);
	//print_line(&img, 100, 100, 1900, 1000);
	// print_line(&img, 0, 5,  400, 1000, 0x00FF0000);
	// print_line(&img, 15, 5,  15, 1000, 0x00FF0000);
	while (edges2d)
	{
		t_edge *edge;
		edge = edges2d->content;
		(void) edge;
		print_line(&img, round(v_x(edge->start)), round(v_y(edge->start)), round(v_x(edge->end)), round(v_y(edge->end)), 0x00FF0000);
		edges2d = edges2d->next;
	}
	// print_square(&img, 500, 500, 501, 501, 0x00FF0000);
	// print_circle(&img, 750, 750, 250, 0x00FF0000);
	// print_hexagon(&img, 750, 750, 250, 0x00FF0000);
	mlx_put_image_to_window(scene->mlx, scene->mlx_win, img.img, 0, 0);
}

t_scene	*init_scene(char *file, void *mlx)
{
	t_list	*mem;
	t_map	*map;
	t_scene	*scene;
	int		screen_width;
	int		screen_height;

	if (!fnew(&mem, T_MAP, &map, read_map(file)))
		return (auto_free(&mem));
	print_map(map);
	mlx_get_screen_size(mlx, &screen_width, &screen_height);
	screen_width = round(screen_width * INITIAL_SCREEN_COVER);
	screen_height = round(screen_height * INITIAL_SCREEN_COVER);
	if (!new(&mem, T_SCENE, &scene, new_scene(map, screen_width, screen_height)))
		return (auto_free(&mem));
	print_scene(scene);
	if (!new(&mem, T_EDGE_LIST, &(scene->edges3d), read_edges_from_map(map)))
		return (auto_free(&mem));
	return (auto_free_but_two(&mem, scene, scene->edges3d));
}

int	main(void)
{

	t_list* mem;
	t_scene *scene;
	void *mlx;
	void *mlx_win;

	char *file = "42.fdf";

	if (!fnew(&mem, T_MLX, &mlx, mlx_init()))
		return (int_error(auto_free(&mem)));
	if (!new(&mem, T_SCENE, &scene, init_scene(file, mlx)))
		return (int_error(auto_free(&mem)));
	if (!new(&mem, T_WINDOW, &mlx_win, mlx_new_window(mlx, scene->width, \
	scene->height, "fdf")))
		return (int_error(auto_free(&mem)));
	scene->mlx_win = mlx_win;
	// if (!connect_events(mlx_win, scene))
	// 	return int_error(auto_free(&mem));
	render_scene(scene);
	mlx_loop(mlx);
	auto_free(&mem);
	return (0);
}
