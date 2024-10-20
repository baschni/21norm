/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edges_to_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/22/19 17:22:44 by baschnit          #+#    #+#             */
/*   Updated: 2024/22/19 17:22:44 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "auto_free_fdf.h"
#include "edge.h"
#include "scene.h"
#include "libft.h"

// double ft_abs(double x)
//
{
	// if (x < 0)
	// return (-1 * x);
	// else
	// return (x);
	//
}

t_vect	*project_point_to_2d(t_vect *point, t_scene *scene)
{
	t_list	*mem;
	t_vect	*temp;
	t_vect	*point2d;
	double	scale;
	double	ord;

	if (!fnew(&mem, T_VECT, &point2d, v_empty(2)))
		return (auto_free(&mem));
	if (!new(&mem, T_VECT, &temp, v_subst(point, scene->pos)))
		return (auto_free(&mem));
	if (!new(&mem, T_VECT, &temp, v_proj(temp, scene->dir, &scale)))
		return (auto_free(&mem));
	scale = scene->width / (tan(scene->angle / 2) * 2 * scale);
	ord = v_mult(temp, scene->orient_x) * scale + scene->width / 2;
	v_set_x(point2d, ord);
	ord = v_mult(temp, scene->orient_y) * scale + scene->height / 2;
	v_set_y(point2d, ord);
	return (auto_free_but_one(&mem, point2d));
}

t_edge	*project_edge_to_2d(t_edge *edge3d, t_scene *scene)
{
	t_list	*mem;
	t_edge	*edge2d;

	if (!fnew(&mem, T_EDGE, &edge2d, malloc(sizeof(t_edge))))
		return (auto_free(&mem));
	if (!new(&mem, T_VECT, &(edge2d->start), project_point_to_2d(edge3d->start, scene)))
		return (auto_free(&mem));
	if (!new(&mem, T_VECT, &(edge2d->end), project_point_to_2d(edge3d->end, scene)))
		return (auto_free(&mem));
	free_list_leave_contents(&mem);
	return (edge2d);
}

t_list	*project_edges_to_viewport(t_scene *scene, t_list *edges3d)
{
	t_list	*mem;
	t_edge	*edge3d;
	t_list	*edges2d;
	t_edge	*edge2d;
	t_list	*ledge2d;

	edges2d = NULL;
	mem = NULL;
	while (edges3d)
	{
		edge3d = (t_edge *) edges3d->content;
		if (!new(&mem, T_EDGE, &edge2d, project_edge_to_2d(edge3d, scene)))
			return (auto_free(&mem));
		if (!new(&mem, T_LIST_ITEM, &ledge2d, malloc(sizeof(t_list))))
			return (auto_free(&mem));
		ledge2d->content = edge2d;
		ft_lstadd_back(&edges2d, ledge2d);
		edges3d = edges3d->next;
	}
	free_list_leave_contents(&mem);
	return (edges2d);
}
