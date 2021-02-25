/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboumed <alboumed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 12:56:41 by alboumed          #+#    #+#             */
/*   Updated: 2021/02/25 13:00:37 by alboumed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_north_texture(char **no_texture, tools *tool)
{
	int	i;

	i = 0;
	while (no_texture[i])
		++i;
	if (i < 2)
		return (0);
	i = 0;
	if (ft_strcmp(no_texture[0], "NO"))
		return (0);
	if (check_path_format(no_texture[1]) == 1)
		tool->no_path = ft_strdup(no_texture[1]);
	else
		return (0);
	return (1);
}

int	get_south_texture(char **so_texture, tools *tool)
{
	int	i;

	i = 0;
	while (so_texture[i])
		++i;
	if (i < 2)
		return (0);
	i = 0;
	if (ft_strcmp(so_texture[0], "SO"))
		return (0);
	if (check_path_format(so_texture[1]) == 1)
		tool->so_path = ft_strdup(so_texture[1]);
	else
		return (0);
	return (1);
}

int	get_east_texture(char **ea_texture, tools *tool)
{
	int	i;

	i = 0;
	while (ea_texture[i])
		++i;
	if (i < 2)
		return (0);
	i = 0;
	if (ft_strcmp(ea_texture[0], "EA"))
		return (0);
	if (check_path_format(ea_texture[1]) == 1)
		tool->ea_path = ft_strdup(ea_texture[1]);
	else
		return (0);
	return (1);
}

int	get_west_texture(char **we_texture, tools *tool)
{
	int	i;

	i = 0;
	while (we_texture[i])
		++i;
	if (i < 2)
		return (0);
	i = 0;
	if (ft_strcmp(we_texture[0], "WE"))
		return (0);
	if (check_path_format(we_texture[1]) == 1)
		tool->we_path = ft_strdup(we_texture[1]);
	else
		return (0);
	return (1);
}

int	get_sprite(char **sprite, tools *tool)
{
	int	i;

	i = 0;
	while (sprite[i])
		++i;
	if (i < 2)
		return (0);
	i = 0;
	if (ft_strcmp(sprite[0], "S"))
		return (0);
	if (check_path_format(sprite[1]) == 1)
		tool->sprite_path = ft_strdup(sprite[1]);
	else
		return (0);
	return (1);
}
