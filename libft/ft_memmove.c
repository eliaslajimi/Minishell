/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:47:17 by cmcgahan          #+#    #+#             */
/*   Updated: 2019/10/28 10:56:13 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*source;

	if (!(dst || src))
		return (0);
	if (dst == src)
		return (dst);
	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	i = 0;
	if (source > dest)
		while (i < len)
		{
			dest[i] = source[i];
			i++;
		}
	else
		while (len-- > 0)
			dest[len] = source[len];
	return (dst);
}
