/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/36/19 01:36:01 by baschnit          #+#    #+#             */
/*   Updated: 2024/36/19 01:36:01 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "dim.h"

int	max_left(int table[DIM][DIM], int row);
int	max_right(int table[DIM][DIM], int row);
int	max_down(int table[DIM][DIM], int col);
int	max_up(int table[DIM][DIM], int col);

int	check_argument(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (i % 2 == 0 && !(*str >= '0' && *str <= '9'))
			return (-1);
		if (i % 2 == 1 && *str != ' ')
			return (-1);
		i++;
		str++;
	}
	if (i != (4 * DIM * 2 - 1))
	{
		return (-1);
	}
	return (0);
}

int	read_input(int argc, char **argv, int vue[DIM][DIM])
{
	int	i;

	if (argc != 2 || argv[1][4 * DIM * 2 - 1] != '\0')
	{
		return (-1);
	}
	if (check_argument(argv[1]) == (-1))
		return (-1);
	i = 0;
	while (i < DIM)
	{
		vue[0][i] = argv[1][i * 2] - '0';
		vue[1][i] = argv[1][2 * DIM + i * 2] - '0';
		vue[2][i] = argv[1][4 * DIM + i * 2] - '0';
		vue[3][i] = argv[1][6 * DIM + i * 2] - '0';
		i++;
	}
	return (0);
}

int	check_size(int table[DIM][DIM], int row, int col, int size)
{
	int	i;

	i = 0;
	while (i < col)
	{
		if (table[row][i] == size)
			return (0);
		i++;
	}
	i = 0;
	while (i < row)
	{
		if (table[i][col] == size)
			return (0);
		i++;
	}
	return (1);
}

int	check_vue_row(int table[DIM][DIM], int vue[DIM][DIM], int row)
{
	int	count_left;
	int	count_right;

	count_left = max_left(table, row);
	count_right = max_right(table, row);
	if (count_left != vue[2][row] || count_right != vue[3][row])
		return (0);
	return (1);
}

int	check_vue_col(int table[DIM][DIM], int vue[DIM][DIM], int col)
{
	int	count_top;
	int	count_bottom;

	count_top = max_down(table, col);
	count_bottom = max_up(table, col);
	if (count_top != vue[0][col] || count_bottom != vue[1][col])
		return (0);
	return (1);
}
