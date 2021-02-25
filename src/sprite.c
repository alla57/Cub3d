/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboumed <alboumed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 16:19:39 by alboumed          #+#    #+#             */
/*   Updated: 2021/02/23 11:13:05 by alboumed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	hit_column_sprite_2(tools *tool, int i, int j, double *hit_y)
{
	if ((cos(tool->dir) < 0 && tool->map[j][i - 1] == '2') ||
	(cos(tool->dir) > 0 && tool->map[j][i] == '2'))
	{
		(cos(tool->dir) < 0 && tool->map[j][i - 1] == '2') ? --i : 1;
		tool->sprite_col = 1;
		hit_sprite(tool, i, j);
		*hit_y = tool->hit[2];
	}
}

double	hit_column_sprite(tools *tool, int column, double *hit_y)
{
	double	t;
	double	y;
	int		i;
	int		j;

	i = -5;
	tool->sprite_col = 0;
	cos(tool->dir) > 0 ? column : column++;
	while (i == -5 || !((cos(tool->dir) < 0 && (tool->map[j][i - 1] == '1' ||
	tool->map[j][i - 1] == ' ' || tool->map[j][i - 1] == '2')) ||
	(cos(tool->dir) > 0 && (tool->map[j][i] == '1' || tool->map[j][i] == ' ' ||
	tool->map[j][i] == '2'))))
	{
		cos(tool->dir) > 0 ? column++ : column--;
		t = (column - tool->posx) / cos(tool->dir);
		y = tool->posy - sin(tool->dir) * t;
		if (y > tool->max_y || y < 0)
			return (-1);
		i = column;
		j = (int)y;
	}
	hit_column_sprite_2(tool, i, j, hit_y);
	return (dist(tool, column, y));
}

void	hit_row_sprite_2(tools *tool, int i, int j, double *hit_x)
{
	if ((sin(tool->dir) > 0 && tool->map[j - 1][i] == '2') ||
	(sin(tool->dir) < 0 && tool->map[j][i] == '2'))
	{
		(sin(tool->dir) > 0 && tool->map[j - 1][i] == '2') ? --j : 1;
		tool->sprite_row = 1;
		hit_sprite(tool, i, j);
		*hit_x = tool->hit[2];
	}
}

double	hit_row_sprite(tools *tool, int row, double *hit_x)
{
	double	t;
	double	x;
	int		i;
	int		j;

	i = -5;
	tool->sprite_row = 0;
	sin(tool->dir) > 0 ? row++ : row;
	while (i == -5 || !((sin(tool->dir) > 0 && (tool->map[j - 1][i] == '1' ||
	tool->map[j - 1][i] == ' ' || tool->map[j - 1][i] == '2')) ||
	(sin(tool->dir) < 0 && (tool->map[j][i] == '1' || tool->map[j][i] == ' ' ||
	tool->map[j][i] == '2'))))
	{
		sin(tool->dir) > 0 ? row-- : row++;
		t = (row - tool->posy) / (-1 * sin(tool->dir));
		x = tool->posx + cos(tool->dir) * t;
		if (x > ft_strlen(tool->map[0]) || x < 0)
			return (-1);
		i = (int)x;
		j = row;
	}
	hit_row_sprite_2(tool, i, j, hit_x);
	return (dist(tool, x, row));
}

double	get_dist_sprite(tools *tool, double *hit_x, double hit_y)
{
	double dist;
	double dist_2;

	dist = -1;
	dist_2 = -1;
	if (ft_round(cos(tool->dir)) != 0)
		dist = hit_column_sprite(tool, (int)tool->posx, &hit_y);
	if (ft_round(sin(tool->dir)) != 0)
		dist_2 = hit_row_sprite(tool, (int)tool->posy, hit_x);
	if (dist != -1 && (dist < dist_2 || dist_2 == -1) && tool->sprite_col)
	{
		*hit_x = hit_y;
		get_texture(tool, 0, tool->sprite_col);
	}
	else if (dist_2 != -1 && (dist_2 < dist || dist == -1) && tool->sprite_row)
	{
		dist = dist_2;
		get_texture(tool, 1, tool->sprite_row);
	}
	else
		dist = -1;
	return (dist);
}
