/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 16:17:03 by user42            #+#    #+#             */
/*   Updated: 2021/02/26 18:00:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_header(tools *tool, int fd)
{
	int	tmp;

	write(fd, "BM", 2);
	tmp = 14 + 40 + 4 * tool->res_x * tool->res_y;
	write(fd, &tmp, 4);
	tmp = 0;
	write(fd, &tmp, 2);
	write(fd, &tmp, 2);
	tmp = 54;
	write(fd, &tmp, 4);
	tmp = 40;
	write(fd, &tmp, 4);
	write(fd, &tool->res_x, 4);
	write(fd, &tool->res_y, 4);
	tmp = 1;
	write(fd, &tmp, 2);
	write(fd, &tool->bits_per_pixel, 2);
	tmp = 0;
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
}

void	save_screen(tools *tool, char *option)
{
	int fd;
	int x;
	int y;

	y = tool->res_y;
	if (ft_strcmp(option, "--save"))
		return ;
	if ((fd = open("capture.bmp", O_CREAT | O_RDWR)) == -1)
		return ;
	ft_header(tool, fd);
	while (--y >= 0)
	{
		x = -1;
		while (++x < tool->res_x)
			write(fd, tool->addr + (y * tool->line_length + x *
			(tool->bits_per_pixel / 8)), 4);
	}
	close(fd);
	system("chmod 777 capture.bmp");
	quit(tool);
}
