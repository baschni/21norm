/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/25/19 17:25:56 by baschnit          #+#    #+#             */
/*   Updated: 2024/25/19 17:25:56 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "dim.h"

int max_left(int table[DIM][DIM], int row);
int max_right(int table[DIM][DIM], int row);
int max_down(int table[DIM][DIM], int col);
int max_up(int table[DIM][DIM], int col);
