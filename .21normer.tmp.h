/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .21normer.tmp.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:27:07 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/22 01:30:40 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _21NORMER_TMP_H
# define _21NORMER_TMP_H

# include "libft.h"
# include "scene.h"
# include "map.h"

void	print_scene(t_scene *scene);
void	print_edges2d(t_list *edges);
void	print_edges3d(t_list *edges);
void	print_map(t_map *map);

typedef t_list	t_elist;

#endif