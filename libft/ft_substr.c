/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 13:40:12 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/01/30 13:40:27 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new_s;
	size_t			i;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		len = 0;
	else if (ft_strlen(s) < start + len)
		len = ft_strlen(s) - start;
	if (!(new_s = (char*)malloc((len + 1) * sizeof(char))))
		return (NULL);
	while (i < len && (new_s[i] = s[start++]))
		i++;
	new_s[i] = '\0';
	return (new_s);
}
