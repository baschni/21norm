/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:27:07 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/18 19:29:50 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

void	print_scene(t_scene *scene);
void	print_edges2d(t_list *edges);
void	print_edges3d(t_list *edges);
void	print_map(t_map *map);

#endif
