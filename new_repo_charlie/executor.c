/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <cmcgahan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:01:50 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/10/13 13:06:42 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_cmd(t_data *d, char *cmd)
{
	if (!ft_strcmp(cmd,"echo"))
		d->interrodollar = echofunc(d);
	else if (!ft_strcmp(cmd,"cd"))
		d->interrodollar = cdfunc(d);
	else if (!ft_strcmp(cmd,"pwd"))
	{
		d->interrodollar = pwdfunc(d);
	}
	else if (!ft_strcmp(cmd,"export"))
		d->interrodollar = exportfunc(d);
	else if (!ft_strcmp(cmd,"unset"))
		d->interrodollar = unsetfunc(d, "void");
	else if (!ft_strcmp(cmd, "env"))
		d->interrodollar = envfunc(d, 1);
	else if (!ft_strcmp(cmd,"exit"))
		exit(exitfunc(d));
	else
	{
		absolute_path(d, cmd);
		fork_cmd(d);
	}
	return (0);
}

int		executor(t_data *d)
{
	while (d->p.cmd_grid[d->p.i] != NULL)
	{
		d->p.j = 0;
		while (d->p.cmd_grid[d->p.i][d->p.j] != NULL)
		{
			exec_cmd(d, d->p.cmd_grid[d->p.i][d->p.j]);
			d->p.j++;
		}
		d->p.i++;
	}
	return (0);
}
