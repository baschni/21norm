/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_free_fdf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:20:17 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/21 07:49:48 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "auto_free_fdf.h"
#include "mlx.h"
#include "libft.h"

void	free_mlx_window(void *mlx_win, t_list **mallocs_history)
{
	t_typed_ptr	*tp;
	t_list		*list_item;

	list_item = *mallocs_history;
	while (list_item)
	{
		tp = (t_typed_ptr *) list_item->content;
		if (tp->type == T_MLX && tp->ptr_malloc)
			break ;
		list_item = list_item->next;
	}
	if (!list_item)
	{
		ft_putendl_fd("Error: could not destroy mlx window", STDOUT_FILENO);
		return ;
	}
	mlx_destroy_window(tp->ptr_malloc, mlx_win);
}

void	auto_free_type(int type, void *ptr, t_list **mallocs_history)
{
	if (type == T_MAP)
		m_free(ptr);
	else if (type == T_VECT)
		v_free(ptr);
	else if (type == T_EDGE)
		e_free(ptr);
	else if (type == T_SCENE)
		s_free(ptr);
	else if (type == T_MLX)
		free(ptr);
	else if (type == T_WINDOW)
		free_mlx_window(ptr, mallocs_history);
	else if (type == T_LIST_ITEM)
		free(ptr);
	else if (type == T_EDGE_LIST)
		ft_lstclear((t_list **) &ptr, e_free);
}
