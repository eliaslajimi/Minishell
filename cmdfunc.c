#include "minishell.h"

int	cmdfunc(t_data *dtst)
{
	if (!ft_strcmp(dtst->cmd,"echo"))
		echofunc(dtst);
	else if (!ft_strcmp(dtst->cmd,"cd"))
		cdfunc(dtst);
	else if (!ft_strcmp(dtst->cmd,"pwd"))
		pwdfunc(dtst);
	else if (!ft_strcmp(dtst->cmd,"export"))
		dtst->interrodollar = exportfunc(dtst);
	else if (!ft_strcmp(dtst->cmd,"unset"))
		unsetfunc(dtst, "void");
	else if (!ft_strcmp(dtst->cmd, "env"))
		dtst->interrodollar = envfunc(dtst, 1);
	else if (!ft_strcmp(dtst->cmd,"exit"))
		exitfunc(dtst);
	else
	{
		absolute_path(dtst, dtst->cmd);
		fork_cmd(dtst);
	}
	return (0);
}
