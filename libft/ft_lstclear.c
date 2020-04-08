/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 13:17:40 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/01/30 13:17:42 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*list;

	if (lst && del)
	{
		list = *lst;
		while (list)
		{
			ft_lstdelone(list, del);
			list = list->next;
		}
		*lst = NULL;
	}
}
