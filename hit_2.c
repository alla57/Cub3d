/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboumed <alboumed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:56:11 by alboumed          #+#    #+#             */
/*   Updated: 2021/02/22 14:57:24 by alboumed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	hit_up(tools *tool)
{
	int i;

	i = 0;
	if (sin(tool->dir) > 0)
		i = hit_north(tool);
	else if (sin(tool->dir) < 0)
		i = hit_south(tool);
	if (cos(tool->dir) > 0)
		i = i | hit_east(tool);
	else if (cos(tool->dir) < 0)
		i = i | hit_west(tool);
	return (i);
}

int	hit_down(tools *tool)
{
	int i;

	i = 0;
	if (sin(tool->dir) < 0)
		i = hit_north(tool);
	else if (sin(tool->dir) > 0)
		i = hit_south(tool);
	if (cos(tool->dir) < 0)
		i = i | hit_east(tool);
	else if (cos(tool->dir) > 0)
		i = i | hit_west(tool);
	return (i);
}

int	hit_left(tools *tool)
{
	int i;

	i = 0;
	if (cos(tool->dir) > 0)
		i = hit_north(tool);
	else if (cos(tool->dir) < 0)
		i = hit_south(tool);
	if (sin(tool->dir) < 0)
		i = i | hit_east(tool);
	else if (sin(tool->dir) > 0)
		i = i | hit_west(tool);
	return (i);
}

int	hit_right(tools *tool)
{
	int i;

	i = 0;
	if (cos(tool->dir) < 0)
		i = hit_north(tool);
	else if (cos(tool->dir) > 0)
		i = hit_south(tool);
	if (sin(tool->dir) > 0)
		i = i | hit_east(tool);
	else if (sin(tool->dir) < 0)
		i = i | hit_west(tool);
	return (i);
}
