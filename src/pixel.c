/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboumed <alboumed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 15:52:52 by alboumed          #+#    #+#             */
/*   Updated: 2021/02/23 11:47:25 by alboumed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void			my_mlx_pixel_put(tools *tool, int x, int y, int color)
{
	char *dst;

	dst = tool->addr + (y * tool->line_length + x * (tool->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

unsigned int	get_pixel(tools *tool, int x, int y)
{
	char *dst;

	tool->addr_texture = mlx_get_data_addr(tool->texture,
	&tool->bits_per_pixel_2, &tool->line_length_2, &tool->endian_2);
	dst = tool->addr_texture + (y * tool->line_length_2 + x *
	(tool->bits_per_pixel_2 / 8));
	return (*(unsigned int*)dst);
}

void			get_img(tools *tool, int x, int *y, double height)
{
	calcul c;

	c.width = height;
	c.fx = tool->width / (double)height;
	c.fy = tool->height / (double)height;
	c.a = (int)tool->hit[2];
	c.y_dest = 0;
	c.x_dest = (tool->hit[2] - (double)c.a) * (float)c.width;
	c.x_src = c.x_dest * c.fx;
	if (height > tool->res_y)
		c.y_dest = (height - tool->res_y) / 2;
	while (c.y_dest < height && *y < tool->res_y)
	{
		c.y_src = c.y_dest * c.fy;
		c.color = get_pixel(tool, c.x_src, c.y_src);
		if (!(tool->texture == tool->img_ptr_sp && c.color == 0x00000000))
			my_mlx_pixel_put(tool, x, *y, c.color);
		++c.y_dest;
		++*y;
	}
	++c.x_dest;
}

void			draw_column(double height, int col, double hit_x, tools *tool)
{
	int x;
	int y;
	int i;

	i = -1;
	x = col;
	y = 0;
	tool->hit[2] = hit_x;
	while (++i < (tool->res_y - height) / 2)
	{
		my_mlx_pixel_put(tool, x, y++, tool->c_color);
	}
	get_img(tool, x, &y, height);
	while (y < tool->res_y)
	{
		my_mlx_pixel_put(tool, x, y++, tool->f_color);
	}
}

void			get_texture(tools *tool, int hit, int sprite)
{
	int column;
	int row;

	column = 0;
	row = 1;
	if (hit == column && !sprite)
	{
		if (cos(tool->dir) > 0)
			tool->texture = tool->img_ptr_ea;
		else
			tool->texture = tool->img_ptr_we;
	}
	else if (hit == row && !sprite)
	{
		if (sin(tool->dir) > 0)
			tool->texture = tool->img_ptr_no;
		else
			tool->texture = tool->img_ptr_so;
	}
	else if (sprite)
		tool->texture = tool->img_ptr_sp;
}
