/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboumed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:30:13 by alboumed          #+#    #+#             */
/*   Updated: 2019/11/17 15:45:56 by alboumed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((char*)dest)[i] = ((unsigned char*)src)[i];
		i++;
	}
	return (dest);
}
