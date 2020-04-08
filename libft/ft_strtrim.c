/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:20:18 by cmcgahan          #+#    #+#             */
/*   Updated: 2019/10/24 15:14:52 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			intheset(char const c, char const *set)
{
	int				i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char				*ft_strtrim(char const *s1, char const *set)
{
	char			*str;
	unsigned int	start;
	size_t			len;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (intheset(s1[start], set) == 1 && (s1[start] != '\0'))
		start++;
	len = ft_strlen(s1);
	while (intheset(s1[len - 1], set) == 1 && (s1[start] != '\0'))
		len--;
	if (!(str = ft_substr(s1, start, len - start)))
		return (NULL);
	return (str);
}
