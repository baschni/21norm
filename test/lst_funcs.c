/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 05:43:31 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/27 05:43:31 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <glib.h>

void	lstnew_test(void)
{
	t_list	*a;
	char	b;

	b = 'a';
	a = ft_lstnew((void *) &b);

	g_assert_true(a->content == &b);
	g_assert_true(a->next == NULL);

}

void	lstadd_back_test(void)
{
	t_list	*start;
	t_list	*a;
	t_list	*b;
	t_list	*c;
	char	c_a;

	start = NULL;
	a = ft_lstnew((void *) &c_a);
	b = ft_lstnew((void *) &c_a);
	c = ft_lstnew((void *) &c_a);

	g_assert_true(start == NULL);
	ft_lstadd_back(&start, a);
	g_assert_true(start == a);
	ft_lstadd_back(&start, b);
	g_assert_true((start)->next == b);
	g_assert_true(a->next == b);
	ft_lstadd_back(&start, c);
	g_assert_true((start)->next == b);
	g_assert_true(a->next == b);
	g_assert_true((start)->next->next == c);
	g_assert_true(b->next == c);

}

void	lstsize_test(void)
{
	t_list	*start;
	t_list	*a;
	t_list	*b;
	t_list	*c;
	char	c_a;

	start = NULL;
	a = ft_lstnew((void *) &c_a);
	b = ft_lstnew((void *) &c_a);
	c = ft_lstnew((void *) &c_a);

	g_assert_cmpint(ft_lstsize(start), ==, 0);
	ft_lstadd_back(&start, a);
	g_assert_cmpint(ft_lstsize(start), ==, 1);
	ft_lstadd_back(&start, b);
	g_assert_cmpint(ft_lstsize(start), ==, 2);
	ft_lstadd_back(&start, c);
	g_assert_cmpint(ft_lstsize(start), ==, 3);
}
