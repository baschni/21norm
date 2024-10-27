/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putendl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:31:23 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/27 05:25:22 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <glib.h>
#include <fcntl.h>
#include <string.h>
#include "libft.h"
#include "read_file_to_str.h"
#include "config.h"

void	putendl_test1(void)
{
	if (g_test_subprocess())
	{
		write(STDIN_FILENO, "function output: \n", 18);
		ft_putendl_fd("asdf", STDOUT_FILENO);
		write(STDIN_FILENO, "\n", 1);
	}
	g_test_trap_subprocess("/put_fd/putendl/test1_stdout", 20000, 0);
	g_test_trap_assert_stdout("asdf\n");
}

void	putendl_test2(void)
{
	if (g_test_subprocess())
	{
		write(STDIN_FILENO, "function output: \n", 18);
		ft_putendl_fd("bsdf", STDERR_FILENO);
		write(STDIN_FILENO, "\n", 1);
	}
	g_test_trap_subprocess("/put_fd/putendl/test2_stderr", 20000, 0);
	g_test_trap_assert_stderr("bsdf\n");
}

void	putendl_test3(void)
{
	char	*path;
	int		fd;

	if (g_test_subprocess())
	{
		path = concat(TEMP_FOLDER, "putendl_test3.out");
		unlink(path);
		fd = open(path, O_CREAT | O_WRONLY, S_IRUSR);
		ft_putendl_fd("a[ff-q9203ru]", fd);
		close(fd);
		g_assert_cmpstr("a[ff-q9203ru]\n", ==, read_file_to_str(path));
	}
	g_test_trap_subprocess("/put_fd/putendl/test3_file", 20000, 0);
	g_test_trap_assert_stdout("");
	g_test_trap_assert_stderr("");
}

void	putendl_test4(void)
{
	if (g_test_subprocess())
	{
		write(STDIN_FILENO, "function output: \n", 18);
		ft_putendl_fd("", STDOUT_FILENO);
		write(STDIN_FILENO, "\n", 1);
	}
	g_test_trap_subprocess("/put_fd/putendl/test4_empty_str", 20000, 0);
	g_test_trap_assert_stdout("\n");
}

void	putendl_test5(void)
{
	if (g_test_subprocess())
	{
		write(STDIN_FILENO, "function output: \n", 18);
		ft_putendl_fd(NULL, STDOUT_FILENO);
		write(STDIN_FILENO, "\n", 1);
	}
	g_test_trap_subprocess("/put_fd/putendl/test5_null_str", 20000, 0);
	g_test_trap_assert_stdout("\n");
}
