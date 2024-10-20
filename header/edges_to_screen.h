/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edges_to_screen.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:26:59 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/18 19:30:35 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDGES_TO_SCREEN_H
# define EDGES_TO_SCREEN_H

# include "libft.h"
# include "scene.h"

t_list	*project_edges_to_viewport(t_list *edges3d, t_scene *cam);

#endif
