/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 05:30:45 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/21 07:39:58 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edge.h"
#include "vector.h"

#include <stdlib.h>

void	e_free(void *vedge)
{
	t_edge			*edge;
	edge = (t_edge *) vedge;
	v_free(edge->start);
	v_free(edge->end);
	free(edge);
}

t_edge	*e_create(t_vect *start, t_vect *end)
{
	t_edge	*edge;

	edge = malloc(sizeof(t_edge));
	edge->start = start;
	edge->end = end;
	return (edge);
}

t_edge	*e_create3d(int istart[3], int iend[3])
{
	t_vect	*start;
	t_vect	*end;
	t_edge	*edge;

	start = v_new3d(istart[0], istart[1], istart[2]);
	if (!start)
		return (NULL);
	end = v_new3d(iend[0], iend[1], iend[2]);
	if (!end)
	{
		v_free(start);
		return (NULL);
	}
	edge = e_create(start, end);
	if (!edge)
	{
		v_free(start);
		v_free(end);
		return (NULL);
	}
	return (edge);
}
