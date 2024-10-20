/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/22/19 17:22:44 by baschnit          #+#    #+#             */
/*   Updated: 2024/22/19 17:22:44 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "vector.h"
#include "math.h"
#include "libft.h"

// t_vect *v_new(va_args)
//
{
	//
}

int	v_isortho(t_vect *a, t_vect *b)
{
	if (v_mult(a, b) == 0)
		return (1);
	else
		return (0);
}

int	v_iszero(t_vect *a)
{
	if (v_len(a) == 0.0)
		return (1);
	else
		return (0);
}

int	v_isnormed(t_vect *a)
{
	if (v_len(a) <= 1.0000000000000002 && v_len(a) >= 0.9999999999999998)
		return (1);
	else
		return (0);
}

int	v_isparallel(t_vect *a, t_vect *b)
{
	double	x;
	double	y;
	double	z;

	if (v_iszero(a) && v_iszero(b))
		return (1);
	if (v_x(a) == 0 || v_x(b) == 0)
		x = 0;
	else
		x = v_x(a) / v_x(b);
	if (v_y(a) == 0 || v_y(b) == 0)
		y = 0;
	else
		y = v_y(a) / v_y(b);
	if (v_z(a) == 0 || v_z(b) == 0)
		z = 0;
	else
		z = v_z(a) / v_z(b);
	if ((x == 0 && v_x(a) != v_x(b)) || (y == 0 && v_y(a) != v_y(b)) \
		|| (z == 0 && v_z(a) != v_z(b)))
			return (0);
	if ((x != y && !(x == 0 || y == 0)) || (x != z && !(x == 0 || z == 0)) \
		|| (y != z && !(y == 0 || z == 0)))
			return (0);
	return (1);
}
