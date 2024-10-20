/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/22/19 17:22:44 by baschnit          #+#    #+#             */
/*   Updated: 2024/22/19 17:22:44 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vect	*v_scale(double scale, t_vect* vect)
{
	size_t	i;
	double	*pos_old;
	double	*pos_new;
	t_vect	*new;

	new = v_empty(vect->size);
	if (!new)
		return (NULL);
	pos_old = vect->values;
	pos_new = new->values;
	i = 0;
	while (i < vect->size)
	{
		*pos_new = scale * *pos_old;
		pos_new++;
		pos_old++;
		i++;
	}
	return (new);
}

t_vect	*v_proj(t_vect *distance, t_vect *direction, double *ret_scale)
{
	double	scale;
	t_vect	*scaled;
	t_vect	*proj;

	if (v_iszero(direction) || !v_isnormed(direction))
		return (NULL);
	scale = v_mult(distance, direction) / v_square(direction);
	if (ret_scale)
		*ret_scale = scale;
	scaled = v_scale(scale, direction);
	if (!scaled)
		return (NULL);
	proj = v_subst(distance, scaled);
	free(scaled);
	return (proj);
}

t_vect	*v_norm(t_vect *to_norm)
{
	size_t	i;
	double	length;
	double	*pos_old;
	double	*pos_new;
	t_vect	*new;

	length = v_len(to_norm);
	if (!length)
		return (v_dupl(to_norm));
	new = v_empty(to_norm->size);
	if (!new)
		return (NULL);
	pos_old = to_norm->values;
	pos_new = new->values;
	i = 0;
	while (i < to_norm->size)
	{
		*pos_new = *pos_old / length;
		pos_new++;
		pos_old++;
		i++;
	}
	return (new);
}

t_vect	*v_cross(t_vect *a, t_vect *b)
{
	t_vect	*cross;

	cross = v_empty(3);
	if (!cross)
		return (NULL);
	v_set_x(cross, v_y(a) * v_z(b) - v_z(a) * v_y(b));
	v_set_y(cross, v_z(a) * v_x(b) - v_x(a) * v_z(b));
	v_set_z(cross, v_x(a) * v_y(b) - v_y(a) * v_x(b));
	return (cross);
}

t_vect	*v_cross_normed(t_vect *a, t_vect *b)
{
	t_vect	*res;
	t_vect	*res2;

	res = v_cross(a, b);
	if (!res)
		return (NULL);
	res2 = v_norm(res);
	v_free(res);
	return (res2);
}
