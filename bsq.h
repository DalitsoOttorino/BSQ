/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:43:30 by vtian             #+#    #+#             */
/*   Updated: 2025/04/09 18:29:37 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# define E_FAILURE -1
# define E_SUCCESS 1 
# define F_STDIN "/dev/stdin"
# define F_NULL "/dev/null"
# define BUFFER_SIZE 8
# define FILE_BUFFER_NAME "file_buffer"

typedef struct s_map
{
	char			emp;
	char			obs;
	char			ful;
	unsigned int	rows;
	unsigned int	cols;
}				t_map;

typedef struct s_pos
{
	int	row;
	int	col;
}				t_pos;

typedef struct s_soln
{
	int	size;
	int	row;
	int	col;
}				t_soln;

typedef struct s_boards
{
	char	*puzzle;
	char	*working;
}				t_boards;

int		ft_check_map(char *filename, t_map map);
t_map	ft_read_map(char *filename);
int		ft_check_map_helper(int fd, t_map map);
char	ft_get_grid(int row, int col, char *grid, t_map map);
void	ft_set_grid(t_pos pos, char *grid, t_map map, char c);
char	*ft_create_grid(char *filename, t_map map);
void	ft_print_grid(char *grid, t_map map);
void	ft_do_a_puzzle(t_boards b, t_map map);

#endif