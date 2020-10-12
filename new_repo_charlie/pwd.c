/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <cmcgahan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:15:49 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/10/12 16:15:52 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwdfunc(t_data *dtst)
{
	char	*buf;
	char	*currentdir;
	int	size;
	
	buf = NULL;
	size = 1000;
	currentdir = getcwd(buf, size);
	dtst->arg = currentdir;
	dtst->arg = ft_strjoin(dtst->arg, "\n");
	printcommand(dtst);
	free(dtst->arg);
	dtst->arg = "";
	return (0);
}
