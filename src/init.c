/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboumed <alboumed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 15:45:52 by alboumed          #+#    #+#             */
/*   Updated: 2021/02/22 15:51:46 by alboumed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_param(tools *tool)
{
	tool->sprite_col = 0;
	tool->sprite_row = 0;
	tool->keyup = 0;
	tool->keyleft = 0;
	tool->keydown = 0;
	tool->keyright = 0;
	tool->rotate_right = 0;
	tool->rotate_left = 0;
	tool->speed = 0.1;
}

void	init_window(tools *tool)
{
	tool->title = "Cub3d";
	tool->mlx_ptr = mlx_init();
	tool->win_ptr = mlx_new_window(tool->mlx_ptr, tool->res_x,
	tool->res_y, tool->title);
}

void	create_img_addr(tools *tool)
{
	tool->img_ptrnew = mlx_new_image(tool->mlx_ptr, tool->res_x, tool->res_y);
	tool->addr = mlx_get_data_addr(tool->img_ptrnew, &tool->bits_per_pixel,
	&tool->line_length, &tool->endian);
	tool->img_ptr_no = mlx_xpm_file_to_image(tool->mlx_ptr, tool->no_path,
	&tool->width, &tool->height);
	tool->img_ptr_so = mlx_xpm_file_to_image(tool->mlx_ptr, tool->so_path,
	&tool->width, &tool->height);
	tool->img_ptr_ea = mlx_xpm_file_to_image(tool->mlx_ptr, tool->ea_path,
	&tool->width, &tool->height);
	tool->img_ptr_we = mlx_xpm_file_to_image(tool->mlx_ptr, tool->we_path,
	&tool->width, &tool->height);
	tool->img_ptr_sp = mlx_xpm_file_to_image(tool->mlx_ptr, tool->sprite_path,
	&tool->width, &tool->height);
}

void	init_player_pos(tools *tool)
{
	tool->posy = tool->pos_player[0] + 0.5;
	tool->posx = tool->pos_player[1] + 0.5;
}
