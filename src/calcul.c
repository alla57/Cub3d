/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboumed <alboumed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 16:14:27 by alboumed          #+#    #+#             */
/*   Updated: 2021/02/22 16:26:12 by alboumed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		ft_pair(double n)
{
	if (((int)n % 2) == 0)
		return (1);
	return (0);
}

double	ft_round(double n)
{
	n = round(n * 1000);
	n = n / 1000;
	return (n);
}

double	dist(tools *tool, double x, double y)
{
	int a;
	int b;

	a = (int)x;
	b = (int)y;
	if ((tool->sprite_col && (double)a == x) ||
	(tool->sprite_row && (double)b == y))
	{
		x = tool->hit[0];
		y = tool->hit[1];
	}
	x -= tool->posx;
	y -= tool->posy;
	x = x * x;
	y = y * y;
	return (sqrt(x + y));
}

double	get_dist(tools *tool, double *hit_x, double hit_y)
{
	double dist;
	double dist_2;

	dist = -1;
	dist_2 = -1;
	if (ft_round(cos(tool->dir)) != 0)
		dist = hit_column(tool, (int)tool->posx, &hit_y);
	if (ft_round(sin(tool->dir)) != 0)
		dist_2 = hit_row(tool, (int)tool->posy, hit_x);
	if ((dist < dist_2 && dist != -1) || dist_2 == -1)
	{
		*hit_x = hit_y;
		get_texture(tool, 0, 0);
	}
	else
	{
		dist = dist_2;
		get_texture(tool, 1, 0);
	}
	return (dist);
}
