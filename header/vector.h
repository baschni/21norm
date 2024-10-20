/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:26:33 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/18 22:06:43 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdlib.h>

typedef struct s_vect
{
	double	*values;
	size_t	size;
}	t_vect;

t_vect		*v_add(t_vect *a, t_vect *b);
void		v_copy(t_vect *a, t_vect *b);
t_vect		*v_dupl(t_vect *a);
t_vect		*v_empty(size_t n);
void		*v_free(t_vect *a);

int			v_isnormed(t_vect *a);
int			v_isortho(t_vect *a, t_vect *b);
int			v_iszero(t_vect *a);
int			v_isparallel(t_vect *a, t_vect *b);

t_vect		*v_subst(t_vect *a, t_vect *b);
double		v_mult(t_vect *a, t_vect *b);
double		v_square(t_vect *a);
double		v_len(t_vect *a);

t_vect		*v_new2d(double x, double y);
t_vect		*v_new3d(double x, double y, double z);
t_vect		*v_new2d_normed(double x, double y);
t_vect		*v_new3d_normed(double x, double y, double z);

t_vect		*v_scale(double scale, t_vect *vect);
t_vect		*v_norm(t_vect *to_norm);
t_vect		*v_proj(t_vect *distance, t_vect *direction, double *ret_scale);
t_vect		*v_cross(t_vect *a, t_vect *b);
t_vect		*v_cross_normed(t_vect *a, t_vect *b);

double		v_x(t_vect *vect);
double		v_y(t_vect *vect);
double		v_z(t_vect *vect);
void		v_set(t_vect **a, t_vect *b);
void		v_set_x(t_vect *vect, double x);
void		v_set_y(t_vect *vect, double y);
void		v_set_z(t_vect *vect, double z);

#endif
