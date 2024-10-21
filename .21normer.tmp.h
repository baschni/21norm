/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .21normer.tmp.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:27:05 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/21 08:18:27 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDGE_H
# define EDGE_H

# include "vector.h"

typedef struct s_edge
{
	t_vect	*start;
	t_vect	*end;
}	t_edge;

void			e_free(void *edge);
t_edgeasdfasdf	*e_create(t_vect *start, t_vect *end);
t_edge			*e_create3d(int start[3], int end[3]);

#endif