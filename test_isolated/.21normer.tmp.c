/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .21normer.tmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 06:46:28 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/27 06:46:28 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glib.h>
#include "libft.h"
#include <string.h>
#include <stdio.h>
#include "pairs.h"

void	strlen_test(void)
{
	g_assert(ft_strlen("") == strlen(""));
	//g_assert(ft_strlen(NULL) == strlen(NULL));
	// g_assert(ft_strlen(NULL) == 0);
	g_assert(ft_strlen("asdf") == strlen("asdf"));
	g_assert(ft_strlen("a") == strlen("a"));
	g_assert(ft_strlen("asdf") != strlen("asdfa"));
}

void	substr_test(void)
{
	t_pair *start_end[] = { \
		ipair(7, 4), \
		ipair(0, 1), \

		ipair(0, 5), \
		ipair(0, 1), \

		ipair(0, 0), \
		ipair(0, 1), \
		ipair(0, 2), \

		ipair(0, 12), \
		ipair(0, 24), \
		ipair(3, 11), \
		ipair(3, 24), \
		ipair(0, 11), \
		NULL
	};
	t_pair *str_substr[] = { \
		spair("I like boat.", "boat"), \
		spair("I like boat.", "I"), \

		spair("", ""), \
		spair("", ""), \

		spair("a", ""), \
		spair("a", "a"), \
		spair("a", "a"), \

		spair("qwerqwerqwer", "qwerqwerqwer"), \
		spair("qwerqwerqwer", "qwerqwerqwer"), \
		spair("qwerqwerqwer", "rqwerqwer"), \
		spair("qwerqwerqwer", "rqwerqwer"), \
		spair("qwerqwerqwer", "qwerqwerqwe"), \
		NULL
	};
	int i = 0;

	while (str_substr[i])
	{
		g_assert_cmpstr(ft_substr(str_substr[i]->str.a, start_end[i]->i.a, start_end[i]->i.b), ==, str_substr[i]->str.b);
		i++;
	}
}

void	strchr_test(void)
{
	char *asdf = "asdf";
	char *asdfdqwer = "asdfdqwer";
	char *a = "a";
	char *empty = "";

	g_assert(ft_strchr(asdf, 'd') == strchr(asdf, 'd'));
	g_assert(ft_strchr(empty, 'c') == strchr(empty, 'c'));

	//g_assert(ft_strchr(NULL,'a') == strchr(NULL,'a'));

	// g_assert(ft_strchr(NULL,'a') == NULL);
	g_assert(ft_strchr(a, 'a') == strchr(a, 'a'));
	g_assert(ft_strchr(a, 'b') == strchr(a, 'b'));
	g_assert(ft_strchr(asdf, 'y') == strchr(asdf, 'y'));
	g_assert(ft_strchr(empty, 0) == strchr(empty, 0));
	g_assert(ft_strchr(asdf, 0) == strchr(asdf, 0));
	g_assert(ft_strchr(asdfdqwer, 'd') == strchr(asdfdqwer, 'd'));
	g_assert(ft_strchr(asdfdqwer, 'd') != strrchr(asdfdqwer, 'd'));
	g_assert(ft_strchr("asdf", 'd') != strchr("asdf", 'f'));
}

void	strrchr_test(void)
{
	char *asdf = "asdf";
	char *asdfdqwer = "asdfdqwer";
	char *a = "a";
	char *empty = "";

	g_assert(ft_strrchr(asdf, 'd') == strrchr(asdf, 'd'));
	g_assert(ft_strrchr(empty, 'c') == strrchr(empty, 'c'));
	//g_assert(ft_strrchr(NULL,'a') == strrchr(NULL,'a'));
	// g_assert(ft_strrchr(NULL,'a') == NULL);
	g_assert(ft_strrchr(a, 'a') == strrchr(a, 'a'));
	g_assert(ft_strrchr(a, 'b') == strrchr(a, 'b'));
	g_assert(ft_strrchr(asdf, 'y') == strrchr(asdf, 'y'));
	g_assert(ft_strrchr(empty, 0) == strrchr(empty, 0));
	g_assert(ft_strrchr(asdf, 0) == strrchr(asdf, 0));
	g_assert(ft_strrchr(asdfdqwer, 'd') == strrchr(asdfdqwer, 'd'));
	g_assert(ft_strrchr(asdfdqwer, 'd') != strchr(asdfdqwer, 'd'));
	g_assert(ft_strrchr("asdf", 'd') != strrchr("asdf", 'f'));

}

void	strncmp_test(void)
{
	char *s1 = "asdf";
	char *s2 = "asdfdqwer";
	char *a = "a";
	char *empty = "";

	printf("%i %i\n", ft_strncmp(s1, s2, 4), strncmp(s1, s2, 4));

	g_assert(ft_strncmp(s1, s2, 6) == strncmp(s1, s2, 6));
	g_assert(ft_strncmp(s1, s2, 5) == strncmp(s1, s2, 5));
	g_assert(ft_strncmp(s1, s2, 4) == strncmp(s1, s2, 4));
	g_assert(ft_strncmp(s1, s2, 1) == strncmp(s1, s2, 1));
	g_assert(ft_strncmp(s1, s2, 0) == strncmp(s1, s2, 0));
	g_assert(ft_strncmp(s2, s1, 6) == strncmp(s2, s1, 6));
	g_assert(ft_strncmp(s2, s1, 5) == strncmp(s2, s1, 5));
	g_assert(ft_strncmp(s2, s1, 4) == strncmp(s2, s1, 4));
	g_assert(ft_strncmp(s2, s1, 1) == strncmp(s2, s1, 1));
	g_assert(ft_strncmp(s2, s1, 0) == strncmp(s2, s1, 0));

	g_assert(ft_strncmp(s1, s1, 5) == strncmp(s1, s1, 5));
	g_assert(ft_strncmp(s1, s1, 4) == strncmp(s1, s1, 4));
	g_assert(ft_strncmp(s1, s1, 1) == strncmp(s1, s1, 1));
	g_assert(ft_strncmp(s1, s1, 0) == strncmp(s1, s1, 0));

	g_assert(ft_strncmp(a, s1, 4) == strncmp(a, s1, 4));
	g_assert(ft_strncmp(a, s1, 2) == strncmp(a, s1, 2));
	g_assert(ft_strncmp(a, s1, 1) == strncmp(a, s1, 1));
	g_assert(ft_strncmp(a, s1, 0) == strncmp(a, s1, 0));
	g_assert(ft_strncmp(s1, a, 2) == strncmp(s1, a, 2));
	g_assert(ft_strncmp(s1, a, 1) == strncmp(s1, a, 1));
	g_assert(ft_strncmp(s1, a, 0) == strncmp(s1, a, 0));
	g_assert(ft_strncmp(a, a, 2) == strncmp(a, a, 2));
	g_assert(ft_strncmp(a, a, 1) == strncmp(a, a, 1));
	g_assert(ft_strncmp(a, a, 0) == strncmp(a, a, 0));

	g_assert(ft_strncmp(empty, empty, 1) == strncmp(empty, empty, 1));
	g_assert(ft_strncmp(empty, empty, 0) == strncmp(empty, empty, 0));

	g_assert(ft_strncmp(s1, empty, 1) == strncmp(s1, empty, 1));
	g_assert(ft_strncmp(s1, empty, 0) == strncmp(s1, empty, 0));

	g_assert(ft_strncmp(empty, s1, 1) == strncmp(empty, s1, 1));
	g_assert(ft_strncmp(empty, s1, 0) == strncmp(empty, s1, 0));

	// g_assert(ft_strncmp(NULL,NULL,5) == 0);
	// g_assert(ft_strncmp(NULL,NULL,0) == 0);
	// g_assert(ft_strncmp(NULL,s1,5) == -1);
	// g_assert(ft_strncmp(s2,NULL,5) == 1);
	// g_assert(ft_strncmp(NULL,s1,0) == 0);
	// g_assert(ft_strncmp(s2,NULL,0) == 0);

}
