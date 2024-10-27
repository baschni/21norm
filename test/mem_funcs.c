/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 05:37:27 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/27 06:48:23 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glib.h>
#include <string.h>
#include <stdio.h>

#include "libft.h"
#include "pairs.h"

void	bzero_test(void)
{
	int len[] = {strlen("qwerpzoxijas;ldkf") + 1, strlen("qwerpzoxijas;ldkf"), strlen("qwerpzoxijas;ldkf") - 5, 1, 0, 1, 0, 0, 1, 2};
	int comp_len[] = {strlen("qwerpzoxijas;ldkf") + 1, strlen("qwerpzoxijas;ldkf") + 1, strlen("qwerpzoxijas;ldkf") + 1, strlen("qwerpzoxijas;ldkf") + 1, strlen("qwerpzoxijas;ldkf") + 1, 1, 1, 2, 2, 2};

	t_pair *comp[] = { \
		spair("qwerpzoxijas;ldkf", "qwerpzoxijas;ldkf"), \
		spair("qwerpzoxijas;ldkf", "qwerpzoxijas;ldkf"), \
		spair("qwerpzoxijas;ldkf", "qwerpzoxijas;ldkf"), \
		spair("qwerpzoxijas;ldkf", "qwerpzoxijas;ldkf"), \
		spair("qwerpzoxijas;ldkf", "qwerpzoxijas;ldkf"), \
		spair("", ""), \
		spair("", ""), \
		spair("a", "a"), \
		spair("a", "a"), \
		spair("a", "a"), \
	NULL
	};

	int i = 0;
	while (comp[i])
	{
		ft_bzero(comp[i]->str.a, len[i]);
		bzero(comp[i]->str.b, len[i]);
		g_assert_cmpmem(comp[i]->str.a, len[i], comp[i]->str.b, len[i]);
		g_assert_cmpmem(comp[i]->str.a, comp_len[i], comp[i]->str.b, comp_len[i]);
		i++;
	}

	ft_bzero(NULL, 0);
	ft_bzero(NULL, 5);

}

void	memset_test(void)
{
	int len[] = {strlen("qwerpzoxijas;ldkf") + 1, strlen("qwerpzoxijas;ldkf"), strlen("qwerpzoxijas;ldkf") - 5, 1, 0, 1, 0, 0, 1, 2};
	int comp_len[] = {strlen("qwerpzoxijas;ldkf") + 1, strlen("qwerpzoxijas;ldkf") + 1, strlen("qwerpzoxijas;ldkf") + 1, strlen("qwerpzoxijas;ldkf") + 1, strlen("qwerpzoxijas;ldkf") + 1, 1, 1, 2, 2, 2};
	int c;
	t_pair *comp[] = { \
		spair("qwerpzoxijas;ldkf", "qwerpzoxijas;ldkf"), \
		spair("qwerpzoxijas;ldkf", "qwerpzoxijas;ldkf"), \
		spair("qwerpzoxijas;ldkf", "qwerpzoxijas;ldkf"), \
		spair("qwerpzoxijas;ldkf", "qwerpzoxijas;ldkf"), \
		spair("qwerpzoxijas;ldkf", "qwerpzoxijas;ldkf"), \
		spair("", ""), \
		spair("", ""), \
		spair("a", "a"), \
		spair("a", "a"), \
		spair("a", "a"), \
	NULL
	};

	int i = 0;
	while (comp[i])
	{
		c = g_test_rand_int_range (-128, 127);
		ft_memset((void *) comp[i]->str.a, c, len[i]);
		memset(comp[i]->str.b, c, len[i]);
		printf("%s vs %s\n", comp[i]->str.a, comp[i]->str.b);
		g_assert_cmpmem(comp[i]->str.a, len[i], comp[i]->str.b, len[i]);
		g_assert_cmpmem(comp[i]->str.a, comp_len[i], comp[i]->str.b, comp_len[i]);
		i++;
	}

	ft_memset(NULL, c, 0);
	ft_memset(NULL, c, 5);
	//memset(NULL, c, 0);

}

void	memchr_test(void)
{
	char *asdf = "asdf";
	char *asdfdqwer = "asdfdqwer";
	char *a = "a";
	char *empty = "";

	g_assert(ft_memchr(asdf, 'd', 0) == memchr(asdf, 'd', 0));
	g_assert(ft_memchr(asdf, 'd', 3) == memchr(asdf, 'd', 3));
	g_assert(ft_memchr(asdf, 'd', 4) == memchr(asdf, 'd', 4));
	g_assert(ft_memchr(asdf, 'd', 5) == memchr(asdf, 'd', 5));
	g_assert(ft_memchr(empty, 'c', 0) == memchr(empty, 'c', 0));
	g_assert(ft_memchr(NULL, 'a', 0) == NULL);
	g_assert(ft_memchr(NULL, 'a', 5) == NULL);
	g_assert(ft_memchr(a, 'a', 1) == memchr(a, 'a', 1));
	g_assert(ft_memchr(a, 'b', 1) == memchr(a, 'b', 1));
	g_assert(ft_memchr(asdf, 'y', 5) == memchr(asdf, 'y', 5));
	g_assert(ft_memchr(empty, 0, 1) == memchr(empty, 0, 1));
	g_assert(ft_memchr(asdf, 0, 5) == memchr(asdf, 0, 5));
	g_assert(ft_memchr(asdfdqwer, 'd', 8) == memchr(asdfdqwer, 'd', 8));
	//g_assert(ft_memchr(asdfdqwer,'d') != memrchr(asdfdqwer,'d'));
	g_assert(ft_memchr("asdf", 'd', 5) != memchr("asdf", 'f', 5));
}

void	memcmp_test(void)
{
	char *s1 = "asdf";
	char *s2 = "asdfdqwer";
	char *a = "a";
	char *empty = "";

	printf("%i %i\n", ft_memcmp(s1, s2, 4), memcmp(s1, s2, 4));

	g_assert(ft_memcmp(s1, s2, 6) == memcmp(s1, s2, 6));
	g_assert(ft_memcmp(s1, s2, 5) == memcmp(s1, s2, 5));
	g_assert(ft_memcmp(s1, s2, 4) == memcmp(s1, s2, 4));
	g_assert(ft_memcmp(s1, s2, 1) == memcmp(s1, s2, 1));
	g_assert(ft_memcmp(s1, s2, 0) == memcmp(s1, s2, 0));
	g_assert(ft_memcmp(s2, s1, 6) == memcmp(s2, s1, 6));
	g_assert(ft_memcmp(s2, s1, 5) == memcmp(s2, s1, 5));
	g_assert(ft_memcmp(s2, s1, 4) == memcmp(s2, s1, 4));
	g_assert(ft_memcmp(s2, s1, 1) == memcmp(s2, s1, 1));
	g_assert(ft_memcmp(s2, s1, 0) == memcmp(s2, s1, 0));

	g_assert(ft_memcmp(s1, s1, 5) == memcmp(s1, s1, 5));
	g_assert(ft_memcmp(s1, s1, 1) == memcmp(s1, s1, 1));
	g_assert(ft_memcmp(s1, s1, 0) == memcmp(s1, s1, 0));

	g_assert(ft_memcmp(a, s1, 2) == memcmp(a, s1, 2));
	g_assert(ft_memcmp(a, s1, 1) == memcmp(a, s1, 1));
	g_assert(ft_memcmp(a, s1, 0) == memcmp(a, s1, 0));

	g_assert(ft_memcmp(s1, a, 3) == memcmp(s1, a, 3));
	g_assert(ft_memcmp(s1, a, 2) == memcmp(s1, a, 2));
	g_assert(ft_memcmp(s1, a, 1) == memcmp(s1, a, 1));
	g_assert(ft_memcmp(s1, a, 0) == memcmp(s1, a, 0));
	g_assert(ft_memcmp(a, a, 2) == memcmp(a, a, 2));
	g_assert(ft_memcmp(a, a, 1) == memcmp(a, a, 1));
	g_assert(ft_memcmp(a, a, 0) == memcmp(a, a, 0));

	g_assert(ft_memcmp(empty, empty, 1) == memcmp(empty, empty, 1));
	g_assert(ft_memcmp(empty, empty, 0) == memcmp(empty, empty, 0));

	g_assert(ft_memcmp(s1, empty, 1) == memcmp(s1, empty, 1));
	g_assert(ft_memcmp(s1, empty, 0) == memcmp(s1, empty, 0));

	g_assert(ft_memcmp(empty, s1, 1) == memcmp(empty, s1, 1));
	g_assert(ft_memcmp(empty, s1, 0) == memcmp(empty, s1, 0));

	// g_assert(ft_memcmp(NULL,NULL,5) == 0);
	// g_assert(ft_memcmp(NULL,NULL,0) == 0);
	// g_assert(ft_memcmp(NULL,s1,5) == -1);
	// g_assert(ft_memcmp(s2,NULL,5) == 1);
	// g_assert(ft_memcmp(NULL,s1,0) == 0);
	// g_assert(ft_memcmp(s2,NULL,0) == 0);

}
