/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jia-lim <jia-lim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:43:04 by jia-lim           #+#    #+#             */
/*   Updated: 2025/04/09 17:06:53 by jia-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "bsq.h"

//checks if any key in the map contains invalid key
int	ft_check_map_helper(int fd, t_map map)
{
	unsigned int	cols;
	char			c;

	cols = 0;
	while (read(fd, &c, 1) > 0)
	{
		if ((c != map.emp && c != map.obs && c
				&& c != '\n') || ((c == '\n') && cols++ != map.cols))
		{
			close(fd);
			return (E_FAILURE);
		}
		cols++;
		if (c == '\n')
			cols = 0;
	}
	return (E_SUCCESS);
}
