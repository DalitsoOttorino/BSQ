/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:27:28 by vtian             #+#    #+#             */
/*   Updated: 2025/04/09 18:40:54 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

// Creates a buffer so that stdin output can be read multiple times
int	ft_create_buffer(char *filename)
{
	int			file;
	int			buffer;
	char		file_buffer[BUFFER_SIZE];
	__ssize_t	bytes_read;
	__ssize_t	bytes_written;


	file = open(filename, O_RDONLY);
	if (file == -1)
	{
		buffer = open(FILE_BUFFER_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		write(buffer, "\0", 1);
		return (E_FAILURE);
	}
	buffer = open(FILE_BUFFER_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (buffer == -1)
	{
		if (file != STDIN_FILENO)
			close(file);
		return (E_FAILURE);
	}
	bytes_read = read(file, file_buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		bytes_written = write(buffer, file_buffer, bytes_read);
		bytes_read = read(file, file_buffer, BUFFER_SIZE);
	}
	if (file != STDIN_FILENO)
		close(file);
	close(buffer);
	if (bytes_read == -1)
		return (E_FAILURE);
}

// no file passed in, read single file from standard input
// LIMITATIONS max square size is 255 because it is stored in a char
// LIMITATIONS used int and unsigned int inconsistently so
// 	it might be weird if size approaches 2^31
// remember to check valgrind before every commit
// remember to remove all printf and norminette before submission
// remember to remove the '0' used for solution printing
// 	in ft_solve_square
int	main(int argc, char *argv[])
{
	t_map		map;
	char		*filename;
	t_boards	b;
	int			i;

	i = 0;
	while (++i < argc || argc == 1)
	{
		if (argc == 1)
			filename = F_STDIN;
		else
			filename = argv[i];
		ft_create_buffer(filename);
		map = ft_read_map(FILE_BUFFER_NAME);
		if (ft_check_map(FILE_BUFFER_NAME, map) == E_FAILURE)
			return (1);
		ft_do_a_puzzle(b, map);
		if (argc == 1)
			return (0);
	}
	return (0);
}
