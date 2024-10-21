/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:13:49 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/21 07:49:48 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "auto_free.h"

/**
 * @brief set a target ptr to a newly allocated memory ptr while registering both in a list
 * 
 * This is the central function of the auto free module. It receives a newly
 * allocated memory range together with a **ptr to store the address of the newly
 * allocated memory. It will store both addresses to a list passed as parameter
 * (mallocs_history) as long as the type. This list will later be used, when one
 * of the auto free functions is used, to free all the allocated memory addresses
 * and set the according parent pointers to NULL.
 * 
 * @param mallocs_history	list of structure typed_ptr containing type and two pointers
 * @param type 				integer variable holding a value of e_types which is to be
 * 							defined individually for each application
 * @param target 			parent pointer to be set to the memory address on
 * 							allocation and to be set to NULL in auto free function
 * @param void_new 			address returned by malloc upon allocating new memory
 * @return void* 			returns NULL if malloc failed or the address to the
 * 							allocated memory
*/
void	*new(t_list **mallocs_history, int type, void *vtarget, void *void_new)
{
	t_typed_ptr	*tp_new;
	t_list		*l_new;
	void		**target;

	// printf("allocated %p of type %i\n", void_new, type);
	target = (void **) vtarget;
	*target = NULL;
	tp_new = malloc(sizeof(t_typed_ptr));
	if (!tp_new)
		return (auto_free(mallocs_history));
	tp_new->ptr_storage = target;
	tp_new->ptr_malloc = void_new;
	tp_new->type = type;
	l_new = ft_lstnew(tp_new);
	if (!l_new)
	{
		free(tp_new);
		return (auto_free(mallocs_history));
	}
	ft_lstadd_back(mallocs_history, l_new);
	*target = void_new;
	return (void_new);
}

void	*fnew(t_list **mallocs_history, int type, void *vtarget, void *void_new)
{
	*mallocs_history = NULL;
	return (new(mallocs_history, type, vtarget, void_new));
}

void	*auto_free(t_list **mallocs_history)
{
	t_typed_ptr	*tp;
	t_list		*list_item;
	t_list		*list_item_previous;

	list_item = ft_lstlast(*mallocs_history);
	while (list_item)
	{
		tp = (t_typed_ptr *) list_item->content;
		if (tp->ptr_malloc)
			auto_free_type(tp->type, tp->ptr_malloc, mallocs_history);
		tp->ptr_malloc = NULL;
		*(tp->ptr_storage) = NULL;
		list_item_previous = list_item;
		list_item = list_item->next;
		free(list_item_previous->content);
		free(list_item_previous);
	}
	*mallocs_history = NULL;
	return (NULL);
}

void	*auto_free_but_one(t_list **mallocs_history, void *ptr_to_spare)
{
	t_typed_ptr	*tp;
	t_list		*list_item;
	t_list		*list_item_previous;

	list_item = ft_lstlast(*mallocs_history);
	while (list_item)
	{
		tp = (t_typed_ptr *) list_item->content;
		if (tp->ptr_malloc != ptr_to_spare)
		{
			if (tp->ptr_malloc)
				auto_free_type(tp->type, tp->ptr_malloc, mallocs_history);
			tp->ptr_malloc = NULL;
			*(tp->ptr_storage) = NULL;
		}
		list_item_previous = list_item;
		list_item = list_item->next;
		free(list_item_previous->content);
		free(list_item_previous);
	}
	*mallocs_history = NULL;
	return (ptr_to_spare);
}

void	*auto_free_but_two(t_list **hist, void *ptr_to_ret, void *ptr_to_spare)
{
	t_typed_ptr	*tp;
	t_list		*list_item;
	t_list		*list_item_previous;

	list_item = ft_lstlast(*hist);
	while (list_item)
	{
		tp = (t_typed_ptr *) list_item->content;
		// printf("checking to free content of type %i\n", tp->type);
		// printf("checking to free content of type %i with pointer %p and ptrs to spare (%p and %p)\n", tp->type, tp->ptr_malloc, ptr_to_spare, ptr_to_spare2);
		if (tp->ptr_malloc != ptr_to_ret && tp->ptr_malloc != ptr_to_spare)
		{
			if (tp->ptr_malloc)
				auto_free_type(tp->type, tp->ptr_malloc, hist);
			tp->ptr_malloc = NULL;
			*(tp->ptr_storage) = NULL;
		}
		list_item_previous = list_item;
		list_item = list_item->next;
		free(list_item_previous->content);
		free(list_item_previous);
	}
	*hist = NULL;
	// printf("auto free 2 ended \n");
	return (ptr_to_ret);
}

void	*free_list_leave_contents(t_list **mallocs_history)
{
	t_list	*iterator;
	t_list	*iterator_previous;

	iterator = *mallocs_history;
	while (iterator)
	{
		iterator_previous = iterator;
		iterator = iterator->next;
		free(iterator_previous);
	}
	*mallocs_history = NULL;
	return (NULL);
}

int	int_error(void *ptr)
{
	if (!ptr)
		return (-1);
	else
		return (0);
}
