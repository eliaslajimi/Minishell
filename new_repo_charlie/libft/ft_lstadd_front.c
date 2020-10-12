/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 13:17:30 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/01/30 13:17:32 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstadd_front(t_list **alst, t_list *new)
{
	t_list	*tmp;

	if (alst && new && (*alst != new))
	{
		tmp = *alst;
		if (*alst == NULL)
			*alst = new;
		else
		{
			*alst = new;
			new->next = tmp;
		}
	}
}
