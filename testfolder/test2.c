/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 00:29:43 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/19 02:37:10 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "dim.h"

int	max_left(int table[DIM][DIM], int row);
int		max_right(int table[DIM][DIM], int row);
int	max_down(int table[DIM][DIM], int col);
int	max_up(int table[DIM][DIM], int col);
