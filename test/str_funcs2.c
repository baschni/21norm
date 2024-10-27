/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_funcs2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 06:48:25 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/27 06:48:25 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pairs.h"
#include <glib.h>
#include <stdio.h>

void	assert_split(char **split, char **sol)
{
	while (*split && *sol)
	{
		printf("%s %s\n", *split, *sol);
		g_assert_cmpstr(*split, ==, *sol);
		split++;
		sol++;
	}
	if ((!*split && *sol) || (*split && !*sol))
		g_assert(0);
}

void	split_test(void)
{
	char *str1 = "asdf ewrqwer xcvzxcv";
	char sep1 = ' ';
	char *sol1[] = {"asdf", "ewrqwer", "xcvzxcv", NULL};

	char *str2 = "asdf ewrqwer xcvzxcv";
	char sep2 = '\0';
	char *sol2[] = {"asdf ewrqwer xcvzxcv", NULL};

	char *str3 = "||as df||||ewrqwer |xcv z|xcv";
	char sep3 = '|';
	char *sol3[] = {"as df", "ewrqwer ", "xcv z", "xcv", NULL};

	char *str4 = "";
	char sep4 = '|';
	char *sol4[] = {NULL};

	char *str5 = "\0\0\0";
	char sep5 = '\0';
	char *sol5[] = {NULL};

	char *str6 = "||";
	char sep6 = '|';
	char *sol6[] = {NULL};

	char *str7 = "|";
	char sep7 = '|';
	char *sol7[] = {NULL};

	char *str8 = "";
	char sep8 = '\0';
	char *sol8[] = {NULL};

	assert_split(ft_split(str1, sep1), sol1);
	assert_split(ft_split(str2, sep2), sol2);
	assert_split(ft_split(str3, sep3), sol3);
	assert_split(ft_split(str4, sep4), sol4);
	assert_split(ft_split(str5, sep5), sol5);
	assert_split(ft_split(str6, sep6), sol6);
	assert_split(ft_split(str7, sep7), sol7);
	assert_split(ft_split(str8, sep8), sol8);

}

void	strtrim_test(void)
{
	char *sol[] = { \
		"qwerp;;zoxijas;ldkf", \
		"", \
		"The array of new strings resulting from the split. NULL if the allocation fails.", \
		"", \
		"", \
		"", \
		"asdf", \
		"asdf+", \
		"Allocates (with malloc(3)) and returns a string representing the integer received as an argument. Negative numbers must be handled.", \
		"Allocates (with malloc(3)) and returns a string representing the integer received as an argument. Negative numbers must be handled.", \

	};
	t_pair *comp[] = { \
		spair(";qwerp;;zoxijas;ldkf;;;;", ";"), \
		spair("", ""), \
		spair(" \t\t \t\t\t\tThe array of new strings resulting from the split. NULL if the allocation fails.\t \t", " \t"), \
		spair("", ";+-=!'/"), \
		spair("+++;;;-", "+;-"), \
		spair("+++;;;", "+;"), \
		spair(";asdf+;", ";;+"), \
		spair(";asdf+;", ";;;"), \
		spair("Allocates (with malloc(3)) and returns a string representing the integer received as an argument. Negative numbers must be handled.", " \t"), \
		spair("Allocates (with malloc(3)) and returns a string representing the integer received as an argument. Negative numbers must be handled.", ""), \
	NULL
	};
	int i = 0;

	while (comp[i])
	{
		g_assert_cmpstr(ft_strtrim(comp[i]->str.a, comp[i]->str.b), ==, sol[i]);
		i++;
	}
}
