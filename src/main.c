/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboumed <alboumed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:59:04 by alboumed          #+#    #+#             */
/*   Updated: 2021/02/23 12:06:28 by alboumed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void move_player(tools *tool)
{
	if (tool->keyup && !hit_up(tool))
		move_forward(tool);
	if (tool->keyleft && !hit_left(tool))
		move_left(tool);
	if (tool->keydown && !hit_down(tool))
		move_backward(tool);
	if (tool->keyright && !hit_right(tool))
		move_right(tool);
	if (tool->rotate_left)
		rotate_left(tool);
	if (tool->rotate_right)
		rotate_right(tool);
	if (tool->keyup || tool->keydown || tool->keyleft || tool->keyright || tool->rotate_left || tool->rotate_right)
	{
		raycasting(tool, 0);
		check_sprite(tool);
		mlx_put_image_to_window(tool->mlx_ptr, tool->win_ptr, tool->img_ptrnew, 0, 0);
	}
}

int 	press(int keycode, tools *tool) //old
{
	if (keycode == 13) //13 122
		tool->keyup = 1;
	if (keycode == 0) //0 113
		tool->keyleft = 1;
	if (keycode == 1) //1 115
		tool->keydown = 1;
	if (keycode == 2) //2 100
		tool->keyright = 1;
	if (keycode == 123) //123 65361
		tool->rotate_left = 1;
	if (keycode == 124) //124 65363
		tool->rotate_right = 1;
	move_player(tool);
	return 1;
}

int		release(int keycode, tools *tool) //old
{
	if (keycode == 13) //13 122
		tool->keyup = 0;
	if (keycode == 0) //0 113
		tool->keyleft = 0;
	if (keycode == 1) //1 115
		tool->keydown = 0;
	if (keycode == 2) //2 100
		tool->keyright = 0;
	if (keycode == 123) //123 65361
		tool->rotate_left = 0;
	if (keycode == 124) //124 65363
		tool->rotate_right = 0;
	printf("keyrelease\n");
	return 1;
}

int main(int ac, char *av[])
{
	tools tool;

	(void)(ac);
	if (get_map_param(av[1], &tool))
	{
		printf("tous les parametres sont bons\n");
	}
	else
	{
		printf("error\n");
		return (0);
	}

	init_param(&tool);
	init_window(&tool);
	create_img_addr(&tool);
	init_player_pos(&tool);
	mlx_put_image_to_window(tool.mlx_ptr, tool.win_ptr, tool.img_ptrnew, 0, 0);
	mlx_hook(tool.win_ptr, 2, 1L<<0, press, &tool);
	mlx_hook(tool.win_ptr, 3, 1L<<1, release, &tool);
	mlx_loop(tool.mlx_ptr);
	return 0;
}