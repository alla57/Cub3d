/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboumed <alboumed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 16:24:33 by alboumed          #+#    #+#             */
/*   Updated: 2021/02/23 11:15:36 by alboumed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	hit_column(tools *tool, int column, double *hit_y)
{
	double	t;
	double	y;
	int		i;
	int		j;

	i = -5;
	tool->sprite_col = 0;
	cos(tool->dir) > 0 ? column : column++;
	while (i == -5 || !((cos(tool->dir) < 0 && (tool->map[j][i - 1] == '1' ||
	tool->map[j][i - 1] == ' ')) || (cos(tool->dir) > 0 &&
	(tool->map[j][i] == '1' || tool->map[j][i] == ' '))))
	{
		cos(tool->dir) > 0 ? column++ : column--;
		t = (column - tool->posx) / cos(tool->dir);
		y = tool->posy - sin(tool->dir) * t;
		if (y > tool->max_y || y < 0)
			return (-1);
		i = column;
		j = (int)y;
	}
	*hit_y = y;
	return (dist(tool, column, y));
}

double	hit_row(tools *tool, int row, double *hit_x)
{
	double	t;
	double	x;
	int		i;
	int		j;

	i = -5;
	tool->sprite_row = 0;
	sin(tool->dir) > 0 ? row++ : row;
	while (i == -5 || !((sin(tool->dir) > 0 && (tool->map[j - 1][i] == '1' ||
	tool->map[j - 1][i] == ' ')) || (sin(tool->dir) < 0 &&
	(tool->map[j][i] == '1' || tool->map[j][i] == ' '))))
	{
		sin(tool->dir) > 0 ? row-- : row++;
		t = (row - tool->posy) / (-1 * sin(tool->dir));
		x = tool->posx + cos(tool->dir) * t;
		if (x > ft_strlen(tool->map[0]) || x < 0)
			return (-1);
		i = (int)x;
		j = row;
	}
	*hit_x = x;
	return (dist(tool, x, row));
}

void	new_calcul(tools *tool, int col, int sprite)
{
	double dist;
	double height;
	double hit_x;
	double hit_y;

	hit_y = 0;
	if (!sprite)
	{
		dist = get_dist(tool, &hit_x, hit_y);
		dist = dist * cos(fabs(tool->ray_dir));
	}
	else
	{
		dist = get_dist_sprite(tool, &hit_x, hit_y);
	}
	if (dist == -1)
		return ;
	height = (tool->res_y * (tool->res_x / tool->res_y)) / dist;
	draw_column(height, col, hit_x, tool);
}

void	raycasting(tools *tool, int sprite)
{
	double	one_ray;
	double	temp;
	int		column;

	column = 0;
	temp = tool->dir;
	tool->dir += 0.5;
	one_ray = 1.0 / tool->res_x;
	tool->ray_dir = 0.5;
	while (column < tool->res_x)
	{
		new_calcul(tool, column, sprite);
		tool->dir -= one_ray;
		tool->ray_dir -= one_ray;
		++column;
	}
	tool->dir = temp;
}

void	check_sprite(tools *tool)
{
	int sprite;

	sprite = 1;
	raycasting(tool, sprite);
}
