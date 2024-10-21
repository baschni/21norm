/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map2.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:26:50 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/18 19:29:03 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_MAP2_H
# define READ_MAP2_H

void	*free_line_map_fd(char *line, t_map *map, int fd, char *error_msg);
void	*free_splits_and_map(t_list **splits, t_map *map, char *error_msg);
t_list	*list_item_from_split(char *line, char sep, t_map *map, int fd);
t_list	*list_item_from_split_inner(char **split, t_map *map, int fd);
void	m_free(t_map *map);

#endif
