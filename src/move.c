/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboumed <alboumed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 15:00:53 by alboumed          #+#    #+#             */
/*   Updated: 2021/02/22 15:03:31 by alboumed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_forward(tools *tool)
{
	tool->posy -= (sin(tool->dir) * tool->speed);
	tool->posx += (cos(tool->dir) * tool->speed);
	tool->pos_player[0] = (int)tool->posx;
	tool->pos_player[1] = (int)tool->posy;
}

void	move_backward(tools *tool)
{
	tool->posy += (sin(tool->dir) * tool->speed);
	tool->posx -= (cos(tool->dir) * tool->speed);
	tool->pos_player[0] = (int)tool->posx;
	tool->pos_player[1] = (int)tool->posy;
}

void	move_left(tools *tool)
{
	tool->posy -= (cos(tool->dir) * tool->speed);
	tool->posx -= (sin(tool->dir) * tool->speed);
	tool->pos_player[0] = (int)tool->posx;
	tool->pos_player[1] = (int)tool->posy;
}

void	move_right(tools *tool)
{
	tool->posy += (cos(tool->dir) * tool->speed);
	tool->posx += (sin(tool->dir) * tool->speed);
	tool->pos_player[0] = (int)tool->posx;
	tool->pos_player[1] = (int)tool->posy;
}
