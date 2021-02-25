/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboumed <alboumed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 13:02:05 by alboumed          #+#    #+#             */
/*   Updated: 2021/02/25 13:03:45 by alboumed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_rgb(char *colors)
{
	char	**temp;
	int		rgb[3];
	int		i;

	i = 0;
	temp = ft_split(colors, ',');
	while (temp[i])
		i++;
	if (i != 3)
		return (-1);
	i = -1;
	while (++i < 3)
	{
		rgb[i] = ft_atoi(temp[i]);
		if (!(rgb[i] >= 0 && rgb[i] <= 255))
			return (-1);
	}
	rgb[0] <<= 16;
	rgb[1] <<= 8;
	i = -1;
	while (temp[++i])
		free(temp[i]);
	free(temp);
	return (rgb[0] | rgb[1] | rgb[2]);
}

int	get_ground_color(char **ground, tools *tool)
{
	int	i;

	i = 0;
	while (ground[i])
		++i;
	if (i != 2)
		return (0);
	i = 0;
	if (ft_strcmp(ground[0], "F"))
		return (0);
	if ((tool->f_color = get_rgb(ground[1])) == -1)
		return (0);
	return (1);
}

int	get_top_color(char **top, tools *tool)
{
	int	i;

	i = 0;
	while (top[i])
		++i;
	if (i != 2)
		return (0);
	i = 0;
	if (ft_strcmp(top[0], "C"))
		return (0);
	if ((tool->c_color = get_rgb(top[1])) == -1)
		return (0);
	return (1);
}

int	get_res(char **res, tools *tool)
{
	int	i;

	i = 0;
	while (res[i])
		++i;
	if (i < 3)
		return (0);
	i = 0;
	if (ft_strcmp(res[0], "R"))
		return (0);
	while (ft_isdigit(res[1][i]) && res[1][0] > '0')
		++i;
	if (res[1][i] == '\0')
		tool->res_x = ft_atoi(res[1]);
	else
		return (0);
	i = 0;
	while (ft_isdigit(res[2][i]) && res[2][0] > '0')
		++i;
	if (res[2][i] == '\0')
		tool->res_y = ft_atoi(res[2]);
	else
		return (0);
	return (1);
}
