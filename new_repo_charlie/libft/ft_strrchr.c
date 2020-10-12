/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:56:11 by cmcgahan          #+#    #+#             */
/*   Updated: 2019/10/28 11:03:46 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	while (i >= 0)
	{
		if (*str == c)
			return (str);
		str--;
		i--;
	}
	return (NULL);
}
