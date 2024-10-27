/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 05:25:22 by baschnit          #+#    #+#             */
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

void	putstr_test1(void)
{
	if (g_test_subprocess())
	{
		write(STDIN_FILENO, "function output: \n", 18);
		ft_putstr_fd("asdf", STDOUT_FILENO);
		write(STDIN_FILENO, "\n", 1);
	}
	g_test_trap_subprocess("/put_fd/putstr/test1_stdout", 20000, 0);
	g_test_trap_assert_stdout("asdf");
}

void	putstr_test2(void)
{
	if (g_test_subprocess())
	{
		write(STDIN_FILENO, "function output: \n", 18);
		ft_putstr_fd("bsdf", STDERR_FILENO);
		write(STDIN_FILENO, "\n", 1);
	}
	g_test_trap_subprocess("/put_fd/putstr/test2_stderr", 20000, 0);
	g_test_trap_assert_stderr("bsdf");
}

void	putstr_test3(void)
{
	char	*path;
	int		fd;

	if (g_test_subprocess())
	{
		path = concat(TEMP_FOLDER, "putstr_test3.out");
		unlink(path);
		fd = open(path, O_CREAT | O_WRONLY, S_IRUSR);
		ft_putstr_fd("a[ff-q9203ru]", fd);
		close(fd);
		g_assert_cmpstr("a[ff-q9203ru]", ==, read_file_to_str(path));
	}
	g_test_trap_subprocess("/put_fd/putstr/test3_file", 20000, 0);
	g_test_trap_assert_stdout("");
	g_test_trap_assert_stderr("");
}

void	putstr_test4(void)
{
	if (g_test_subprocess())
	{
		write(STDIN_FILENO, "function output: \n", 18);
		ft_putstr_fd("", STDOUT_FILENO);
		write(STDIN_FILENO, "\n", 1);
	}
	g_test_trap_subprocess("/put_fd/putstr/test4_empty_str", 20000, 0);
	g_test_trap_assert_stdout("");
}

void	putstr_test5(void)
{
	if (g_test_subprocess())
	{
		write(STDIN_FILENO, "function output: \n", 18);
		ft_putstr_fd(NULL, STDOUT_FILENO);
		write(STDIN_FILENO, "\n", 1);
	}
	g_test_trap_subprocess("/put_fd/putstr/test5_null_str", 20000, 0);
	g_test_trap_assert_stdout("");
}
