/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr.c                                           :+:      :+:    :+:   */
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
#include <stdlib.h>

#include "libft.h"
#include "read_file_to_str.h"
#include "config.h"

char	*itoa(int i)
{
	char	*s;

	s = malloc(500);
	sprintf(s, "%i", i);
	return (s);
}

void	putnbr_test1(void)
{
	if (g_test_subprocess())
	{
		write(STDIN_FILENO, "function output: \n", 18);
		ft_putnbr_fd(-12345, STDOUT_FILENO);
		write(STDIN_FILENO, "\n", 1);
	}
	g_test_trap_subprocess("/put_fd/putnbr/test1_stdout", 20000, 0);
	g_test_trap_assert_stdout(itoa(-12345));
}

void	putnbr_test2(void)
{
	if (g_test_subprocess())
	{
		write(STDIN_FILENO, "function output: \n", 18);
		ft_putnbr_fd(12345, STDERR_FILENO);
		write(STDIN_FILENO, "\n", 1);
	}
	g_test_trap_subprocess("/put_fd/putnbr/test2_stderr", 20000, 0);
	g_test_trap_assert_stderr(itoa(12345));
}

void	putnbr_test3(void)
{
	char	*path;
	int		fd;

	if (g_test_subprocess())
	{
		path = concat(TEMP_FOLDER, "putnbr_test3.out");
		unlink(path);
		fd = open(path, O_CREAT | O_WRONLY, S_IRUSR);
		ft_putnbr_fd(52376, fd);
		close(fd);
		g_assert_cmpstr(itoa(52376), ==, read_file_to_str(path));
	}
	g_test_trap_subprocess("/put_fd/putnbr/test3_file", 20000, 0);
	g_test_trap_assert_stdout("");
	g_test_trap_assert_stderr("");
}

void	putnbr_test4(void)
{
	if (g_test_subprocess())
	{
		write(STDIN_FILENO, "function output: \n", 18);
		ft_putnbr_fd(0, STDOUT_FILENO);
		write(STDIN_FILENO, "\n", 1);
	}
	g_test_trap_subprocess("/put_fd/putnbr/test4_0", 20000, 0);
	g_test_trap_assert_stdout(itoa(0));
}

void	putnbr_test5(void)
{
	if (g_test_subprocess())
	{
		write(STDIN_FILENO, "function output: \n", 18);
		ft_putnbr_fd(INT_MIN, STDOUT_FILENO);
		write(STDIN_FILENO, "\n", 1);
	}
	g_test_trap_subprocess("/put_fd/putnbr/test5_INT_MIN", 20000, 0);
	g_test_trap_assert_stdout(itoa(INT_MIN));
}

void	putnbr_test6(void)
{
	if (g_test_subprocess())
	{
		write(STDIN_FILENO, "function output: \n", 18);
		ft_putnbr_fd(INT_MAX, STDOUT_FILENO);
		write(STDIN_FILENO, "\n", 1);
	}
	g_test_trap_subprocess("/put_fd/putnbr/test6_INT_MAX", 20000, 0);
	g_test_trap_assert_stdout(itoa(INT_MAX));
}
