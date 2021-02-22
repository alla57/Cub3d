/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboumed <alboumed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 15:03:52 by alboumed          #+#    #+#             */
/*   Updated: 2021/02/22 15:39:51 by alboumed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	rotate_left(tools *tool)
{
	tool->dir += tool->speed;
}

void	rotate_right(tools *tool)
{
	tool->dir -= tool->speed;
}
