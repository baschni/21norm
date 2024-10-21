/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:47:56 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/21 07:45:13 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "vector.h"

double	v_len(t_vect *a)
{
	return (sqrt(v_square(a)));
}

double	v_mult(t_vect *a, t_vect *b)
{
	size_t	i;
	double	res;
	double	*pos_a;
	double	*pos_b;

	res = 0;
	if (a->size != b->size)
		return (0);
	pos_a = a->values;
	pos_b = b->values;
	i = 0;
	while (i < a->size)
	{
		res += *pos_a * *pos_b;
		pos_a++;
		pos_b++;
		i++;
	}
	return (res);
}

double	v_square(t_vect *a)
{
	return (v_mult(a, a));
}

t_vect	*v_add(t_vect *a, t_vect *b)
{
	size_t	i;
	t_vect	*new;
	double	*pos_a;
	double	*pos_b;
	double	*pos_new;

	if (a->size != b->size)
		return (0);
	new = v_empty(a->size);
	if (!new)
		return (NULL);
	pos_a = a->values;
	pos_b = b->values;
	pos_new = new->values;
	while (i < a->size)
	{
		*pos_new = *pos_a + *pos_b;
		pos_a++;
		pos_b++;
		pos_new++;
		i++;
	}
	return (new);
}

t_vect	*v_subst(t_vect *a, t_vect *b)
{
	size_t	i;
	t_vect	*new;
	double	*pos_a;
	double	*pos_b;
	double	*pos_new;

	if (a->size != b->size)
		return (0);
	new = v_empty(a->size);
	if (!new)
		return (NULL);
	pos_a = a->values;
	pos_b = b->values;
	pos_new = new->values;
	i = 0;
	while (i < a->size)
	{
		*pos_new = *pos_a - *pos_b;
		pos_a++;
		pos_b++;
		pos_new++;
		i++;
	}
	return (new);
}
