/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 13:18:14 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/01/30 13:18:15 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *))
{
	t_list	*result;
	t_list	*new;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	new = lst;
	if (!(result = ft_lstnew((*f)(new->content))))
		return (NULL);
	new = new->next;
	while (new)
	{
		tmp = ft_lstnew((*f)(new->content));
		ft_lstadd_back(&result, tmp);
		new = new->next;
	}
	return (result);
}
