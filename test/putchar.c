/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putchar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 05:25:21 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/27 05:25:21 by baschnit         ###   ########.fr       */
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

void	putchar_test1(void)
{
	if (g_test_subprocess())
	{
		write(STDIN_FILENO, "function output: \n", 18);
		ft_putchar_fd('o', STDOUT_FILENO);
		write(STDIN_FILENO, "\n", 1);
	}
	g_test_trap_subprocess("/put_fd/putchar/test1_stdout", 20000, 0);
	g_test_trap_assert_stdout("o");
}

void	putchar_test2(void)
{
	if (g_test_subprocess())
	{
		write(STDIN_FILENO, "function output: \n", 18);
		ft_putchar_fd('[', STDERR_FILENO);
		write(STDIN_FILENO, "\n", 1);
	}
	g_test_trap_subprocess("/put_fd/putchar/test2_stderr", 20000, 0);
	g_test_trap_assert_stderr("[");
}

void	putchar_test3(void)
{
	char	*path;
	int		fd;

	if (g_test_subprocess())
	{
		path = concat(TEMP_FOLDER, "putchar_test3.out");
		unlink(path);
		fd = open(path, O_CREAT | O_WRONLY, S_IRUSR);
		ft_putchar_fd('^', fd);
		close(fd);
		g_assert_cmpstr("^", ==, read_file_to_str(path));
	}
	g_test_trap_subprocess("/put_fd/putchar/test3_file", 20000, 0);
	g_test_trap_assert_stdout("");
	g_test_trap_assert_stderr("");
}

void	putchar_test4(void)
{
	if (g_test_subprocess())
	{
		write(STDIN_FILENO, "function output: \n", 18);
		ft_putchar_fd(0, STDOUT_FILENO);
		write(STDIN_FILENO, "\n", 1);
	}
	g_test_trap_subprocess("/put_fd/putchar/test4_0char", 20000, 0);
	g_test_trap_assert_stdout("");
}

void	putchar_test5(void)
{
	if (g_test_subprocess())
	{
		write(STDIN_FILENO, "function output: \n", 18);
		ft_putchar_fd(128, STDOUT_FILENO);
		write(STDIN_FILENO, "\n", 1);
	}
	g_test_trap_subprocess("/put_fd/putchar/test5_overflow_char", 20000, 0);
	g_test_trap_assert_stdout(char_to_str(-128));
}

// void putchar_test6(void)
// {
// 	write(STDIN_FILENO, "function output: \n", 18);
// 	ft_putchar_fd(-129, STDOUT_FILENO);
// 	write(STDIN_FILENO, "\n", 1);
// 	g_test_trap_subprocess("/put_fd/putchar/test1_stdout", 20, 0);
// 	g_test_trap_assert_stdout(char_to_str(127));
// }