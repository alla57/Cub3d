/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboumed <alboumed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 13:12:28 by alboumed          #+#    #+#             */
/*   Updated: 2021/02/25 13:25:47 by alboumed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*ft_strcpy_vtwo(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = src[i];
	return (dest);
}

char	*realloc_extended_map(char **str, int max)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*str)[i])
		++i;
	temp = *str;
	if (!((*str) = malloc(sizeof(char) * (max + 1))))
		return (NULL);
	ft_strcpy_vtwo(*str, temp);
	while (i < max)
		(*str)[i++] = ' ';
	(*str)[i] = '\0';
	free(temp);
	return (*str);
}

int		realloc_map(tools *tool)
{
	static int	n = 1;
	char		**temp;
	char		**new_map;
	int			i;

	i = -1;
	temp = tool->map;
	if (!(new_map = malloc(sizeof(char*) * n)))
		return (0);
	tool->map = new_map;
	while (++i < n - 1 && n > 1)
	{
		new_map[i] = ft_strdup(temp[i]);
		free(temp[i]);
	}
	if (n > 1)
		free(temp);
	++n;
	return (1);
}

int		check_player(tools *tool, int max_y)
{
	int	x;
	int	y;
	int	p;

	y = 0;
	p = 0;
	while (y <= max_y)
	{
		x = 0;
		while (tool->map[y][x])
		{
			if (is_player(tool->map[y][x], tool))
			{
				tool->pos_player[0] = (double)y;
				tool->pos_player[1] = (double)x;
				++p;
			}
			++x;
		}
		++y;
	}
	if (p != 1)
		return (0);
	return (1);
}

int		map_master_two(int j, int max_x, tools *tool)
{
	int	max_y;

	max_y = --j;
	while (j >= 0 && is_line(tool->map[j], tool))
	{
		tool->map[j] = realloc_extended_map(&tool->map[j], max_x);
		--j;
	}
	if (j != -1)
		return (0);
	while (++j < (int)max_x)
	{
		if (!is_column(tool->map, max_y, tool))
			return (0);
	}
	tool->max_y = max_y;
	return (check_player(tool, max_y));
}
