/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <cmcgahan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 14:39:47 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/10/12 15:02:32 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_parser(t_parser *p)
{
	p->i = 0;
	p->j = 0;
	p->cmd = 0;
	p->nb_cmd = 1;
	p->word = 0;
	p->token = 0;
	p->check_between = 0;
}

int	init(t_data *dtst)
{
	init_parser(&dtst->p);
	dtst->cmd = ft_calloc(1,1);
	dtst->arg = ft_calloc(1,1);
	dtst->r_arg = ft_calloc(1,1);
	dtst->r_cmd = ft_calloc(1,1);
	dtst->file = ft_calloc(1,1);
	dtst->dir = 0;
	dtst->pipe = -1;
	dtst->filedes[0] = -1;
	dtst->filedes[1] = -1;
	return (0);
}
