/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/17/19 17:17:51 by baschnit          #+#    #+#             */
/*   Updated: 2024/17/19 17:17:51 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vect	*v_new2d(double x, double y)
{
	t_vect	*new;

	new = v_empty(2);
	if (!new)
		return (NULL);
	*(new->values) = x;
	*(new->values + 1) = y;
	return (new);
}

t_vect	*v_new3d(double x, double y, double z)
{
	t_vect	*new;

	new = v_empty(3);
	if (!new)
		return (NULL);
	*(new->values) = x;
	*(new->values + 1) = y;
	*(new->values + 2) = z;
	return (new);
}

double	v_x(t_vect *vect)
{
	return (*vect->values);
}

double	v_y(t_vect *vect)
{
	return (*(vect->values + 1));
}

double	v_z(t_vect *vect)
{
	return (*(vect->values + 2));
}
