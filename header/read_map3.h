/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map3.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:26:46 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/18 19:28:47 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_MAP3_H
# define READ_MAP3_H

void	cancel_newline_at_end(char *line);
long	ft_atol(const char *nptr);
void	ft_free_split(void *vtable);
size_t	ft_split_size(char **split);
int		is_number_str(char *s);

#endif
