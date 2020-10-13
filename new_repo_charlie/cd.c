/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <cmcgahan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 13:39:49 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/10/13 13:42:59 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cdfunc(t_data *dtst)
{
	int	ret;
	char	*temp;
	char	*error_msg;

	temp = ft_strdup(dtst->arg);
	free(dtst->arg);
	dtst->arg = NULL;
	ret = 0;
	if (dtst->file)
		printcommand(dtst);
	dtst->arg = temp;
	if (dtst->pipe < 0)
		ret = chdir(dtst->arg);
	if (ret == -1)
	{
		error_msg = "No such file or directory.\n";
		error(dtst, error_msg, 3);
	}
	return (0);
}
