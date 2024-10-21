/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:48:20 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/18 19:36:09 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "vector.h"
#include "libft.h"

t_vect	*v_empty(size_t n)
{
	double	*values;
	t_vect	*new;

	if (n == 0)
		return (NULL);
	values = ft_calloc(sizeof(double), n);
	if (!values)
		return (NULL);
	new = malloc(sizeof(t_vect));
	if (!new)
	{
		free(values);
		return (NULL);
	}
	new->values = values;
	new->size = n;
	return (new);
}

void	*v_free(t_vect *a)
{
	free(a->values);
	free(a);
	return (NULL);
}

t_vect	*v_dupl(t_vect *a)
{
	size_t	i;
	double	*pos_old;
	double	*pos_new;
	t_vect	*new;

	new = v_empty(a->size);
	if (!new)
		return (NULL);
	pos_old = a->values;
	pos_new = new->values;
	while (i < a->size)
	{
		*pos_new = *pos_old;
		pos_new++;
		pos_old++;
		i++;
	}
	return (new);
}

void	v_copy(t_vect *a, t_vect *b)
{
	size_t	i;
	double	*pos_a;
	double	*pos_b;

	pos_a = a->values;
	pos_b = b->values;
	i = 0;
	while (i < a->size)
	{
		*pos_a = *pos_b;
		pos_a++;
		pos_b++;
		i++;
	}
}

void	v_set(t_vect **a, t_vect *b)
{
	v_free(*a);
	*a = b;
}
