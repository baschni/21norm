/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 05:37:25 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/27 06:54:14 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <glib.h>
#include "pairs.h"
#include "limits.h"

void	atoi_test(void)
{
	//g_assert_cmpint(ft_atoi("1"), ==, atoi("0"));
	t_pair *comp[] = { \
		spair("", ""), \
		spair("-1", "-1"), \
		spair("1", "1"), \
		spair("0", "0"), \
		spair("2345", "2345"), \
		spair("-2345", "-2345"), \
		spair("-2147483648", "-2147483648"), \
		spair("2147483647", "2147483647"), \
		spair(" 2147483647", " 2147483647"), \
		spair(" 2147483647", " 2147483647"), \
		spair(" +2147483647", " +2147483647"), \
		spair(" -2147483647", " -2147483647"), \
		spair(" + 2147483647", " + 2147483647"), \
		spair(" - 2147483647", " - 2147483647"), \
		NULL \
	};

	int i = 0;
	while (comp[i])
	{
		g_assert_cmpint(ft_atoi(comp[i]->str.a), ==, atoi(comp[i]->str.b));
		i++;
	}

	g_assert_cmpint(ft_atoi(NULL), ==, 0);
}
void	itoa_test(void)
{
	int test_i[] = {0, -1, 1, 234, -2345, -2147483648, 2147483647, 1234267, 98780923};
	char *test_s[] = {"0", "-1", "1", "234", "-2345", "-2147483648", "2147483647", "1234267", "98780923", NULL};
	int i;
	char **j;

	ft_itoa(234);

	i = 0;
	j = test_s;
	while (*j)
	{
		g_assert_cmpstr(ft_itoa(test_i[i]), ==, *j);
		j++;
		i++;
	}
}
