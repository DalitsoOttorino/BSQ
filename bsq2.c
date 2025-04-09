/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:25:08 by vtian             #+#    #+#             */
/*   Updated: 2025/04/09 18:29:47 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include <stdlib.h>

// 1-Indexed Grid
// Returns the largest square which can be created
// with its upper left corner at the current position
// while empty tiles in row, set size based on width,
// if first tile checked in row is obs, set size to height
int	ft_calculate_square(int row, int col, char *puzzle, t_map map)
{
	int	max;
	int	tmp;
	int	i_row;
	int	j_col;

	i_row = 0;
	j_col = 0;
	max = 0;
	while ((ft_get_grid(row + i_row, col + j_col, puzzle, map) == map.emp)
		&& (i_row < max || max == 0))
	{
		while ((ft_get_grid(row + i_row, col + j_col, puzzle, map) == map.emp)
			&& ((j_col < max) || (max == 0)))
			j_col++;
		max = j_col;
		if (i_row > max)
			max = i_row;
		i_row++;
		j_col = 0;
	}
	if (i_row < max)
		max = i_row;
	return (max);
}

// Populates the working grid according to largest possible squares
// Returns solution row, col, size
// For debugging, add '0' to grid values so they can be printed
t_soln	ft_solve_square(char *working, char *puzzle, t_map map)
{
	t_soln	soln;
	t_pos	pos;

	pos.row = 0;
	soln.size = 0;
	while (pos.row++ < map.rows)
	{
		pos.col = 0;
		while (pos.col++ < map.cols)
		{
			ft_set_grid(pos, working, map,
				(ft_calculate_square(pos.row, pos.col, puzzle, map)));
			if (ft_get_grid(pos.row, pos.col, working, map) > soln.size)
			{
				soln.col = pos.col;
				soln.row = pos.row;
				soln.size = ft_get_grid(pos.row, pos.col, working, map);
			}
		}
	}
	return (soln);
}

// Inserts the largest square at the given position
void	ft_set_square(t_soln soln, char *puzzle, t_map map)
{
	t_pos	pos;
	int		row;
	int		col;

	row = -1;
	while (row++ + 1 < soln.size)
	{
		col = -1;
		while (col++ + 1 < soln.size)
		{
			pos.row = soln.row + row;
			pos.col = soln.col + col;
			ft_set_grid(pos, puzzle, map, map.ful);
		}
	}
}

void	ft_do_a_puzzle(t_boards b, t_map map)
{
	t_soln		soln;

	b.puzzle = ft_create_grid(FILE_BUFFER_NAME, map);
	b.working = ft_create_grid(F_NULL, map);
	soln = ft_solve_square(b.working, b.puzzle, map);
	ft_set_square(soln, b.puzzle, map);
	ft_print_grid(b.puzzle, map);
	free(b.puzzle);
	free(b.working);
}
