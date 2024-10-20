/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_free_fdf.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:27:16 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/18 19:29:58 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTO_FREE_FDF_H
# define AUTO_FREE_FDF_H

# include "auto_free.h"
# include "map.h"
# include "vector.h"
# include "edge.h"
# include "scene.h"

enum e_types
{
	T_MAP,
	T_VECT,
	T_EDGE,
	T_SCENE,
	T_MLX,
	T_WINDOW,
	T_LIST_ITEM,
	T_EDGE_LIST
};

#endif