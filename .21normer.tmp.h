/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .21normer.tmp.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 17:28:30 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/19 17:32:14 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTO_FREE_H
# define AUTO_FREE_H

# include "libft.h"

typedef struct s_typed_ptr
{
	int type;
	void	**ptr_storage;
	void	*ptr_malloc;
}	t_typed_ptr;

void *neaw(t_list **mallocs_history, int type, void *target, void *void_new);
void	*fnew(t_list **mallocs_history, int type, void *target, void *void_new);
void	*auto_free(t_list **mallocs_history);
void	*auto_free_but_one(t_list **mallocs_history, void *ptr_to_spare);
void	*auto_free_but_two(t_list **hist, void *ptr_to_ret, void *ptr_to_spare);
void	*free_list_leave_contents(t_list **mallocs_history);
int		int_error(void *ptr);

void	auto_free_type(int type, void *ptr, t_list **mallocs_history);

#endif