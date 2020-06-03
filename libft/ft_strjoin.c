/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 13:39:08 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/01/30 13:39:24 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin_space(char *s1, char *s2, int space)
{
	char	*new;
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!(new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + space + 1))))
		return (NULL);
	while (s1 && *s1)
		new[i++] = *s1++;
	while (s2 && *s2)
		new[i++] = *s2++;
	if (space != 0)
		new[i++] = ' ';
	new[i] = '\0';
	return (new);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!(new = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char))))
		return (NULL);
	while (s1 && *s1)
		new[i++] = *s1++;
	while (s2 && *s2)
		new[i++] = *s2++;
	new[i] = '\0';
	return (new);
}
