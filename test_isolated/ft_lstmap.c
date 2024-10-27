/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:09:17 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/27 09:47:46 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	s_next(t_list *mapped, t_list **previous, t_list **start, t_list **lst)
{
	mapped->next = (NULL);
	if (*previous)
		(*previous)->next = mapped;
	*previous = mapped;
	*lst = (*lst)->next;
	if (!*start)
		*start = mapped;
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*mapped;
	t_list	*previous;
	t_list	*start;
	void	*content;

	start = (NULL);
	previous = (NULL);
	while (lst)
	{
		content = f(lst->content);
		if (!content)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		mapped = ft_lstnew(content);
		if (!mapped)
		{
			del(content);
			ft_lstclear(&start, del);
			return (NULL);
		}
		s_next(mapped, &previous, &start, &lst);
	}
	return (start);
}
