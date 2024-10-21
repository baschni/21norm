/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:45:35 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/21 13:01:59 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	v_set_x(t_vect *vect, double x)
{
	*vect->values = x;
}

void v_set_y(t_vect *vect, double y)
{
	*(vect->values + 1) = y;
}

void	v_set_z(t_vect *vect, double z)
{
	*(vect->values + 2) = z;
}

t_vect	*v_new2d_normed(double x, double y)
{
	t_vect	*new;
	double	len;

	new = v_empty(2);
	if (!new)
		return (NULL);
	*(new->values) = x;
	*(new->values + 1) = y;
	len = v_len(new);
	v_set_x(new, x / len);
	v_set_y(new, y / len);
	return (new);
}

t_vect	*v_new3d_normed(double x, double y, double z)
{
	t_vect	*new;
	double	len;

	new = v_empty(3);
	if (!new)
		return (NULL);
	*(new->values) = x;
	*(new->values + 1) = y;
	*(new->values + 2) = z;
	len = v_len(new);
	v_set_x(new, x / len);
	v_set_y(new, y / len);
	v_set_z(new, z / len);
	return (new);
}
