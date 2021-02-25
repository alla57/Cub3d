/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboumed <alboumed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 13:06:33 by alboumed          #+#    #+#             */
/*   Updated: 2021/02/25 13:24:45 by alboumed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_player(char c, tools *tool)
{
	if (c == 'N')
		tool->dir = M_PI_2;
	else if (c == 'S')
		tool->dir = 3 * M_PI_4;
	else if (c == 'E')
		tool->dir = 0;
	else if (c == 'W')
		tool->dir = M_PI;
	else
		return (0);
	return (1);
}

int	is_column(char **map, int max, tools *tool)
{
	static int	j = 0;
	int			i;
	int			a;

	i = 0;
	while (i <= max)
	{
		a = i;
		while (i <= max && map[i][j] == ' ')
			++i;
		while (i <= max && map[i][j] == '1')
		{
			++i;
			while (i <= max && (map[i][j] == '0' || map[i][j] == '2' ||
			is_player(map[i][j], tool)))
			{
				if (i == max || map[++i][j] == ' ')
					return (0);
			}
		}
		if (i == a)
			return (0);
	}
	return (++j);
}

int	is_line(char *str, tools *tool)
{
	int	i;
	int	a;

	i = 0;
	while (str[i])
	{
		a = i;
		while (str[i] == ' ')
			++i;
		while (str[i] == '1')
		{
			++i;
			while (str[i] == '0' || str[i] == '2' || is_player(str[i], tool))
			{
				++i;
				if (str[i] == '\0' || str[i] == ' ')
					return (0);
			}
		}
		if (i == a)
			return (0);
	}
	return (1);
}

int	map_check_line(char *str, tools *tool)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '0' && str[i] != '1'
		&& str[i] != '2' && !is_player(str[i], tool))
			return (0);
		++i;
	}
	return (1);
}

int	empty_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			++i;
		else
			return (0);
	}
	return (1);
}
