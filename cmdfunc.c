#include "minishell.h"

int	cmdfunc(t_data *dtst)
{
	if (!ft_strcmp(dtst->cmd,"echo"))
		dtst->interrodollar = echofunc(dtst);
	else if (!ft_strcmp(dtst->cmd,"cd"))
		dtst->interrodollar = cdfunc(dtst);
	else if (!ft_strcmp(dtst->cmd,"pwd"))
		dtst->interrodollar = pwdfunc(dtst);
	else if (!ft_strcmp(dtst->cmd,"export"))
		dtst->interrodollar = exportfunc(dtst);
	else if (!ft_strcmp(dtst->cmd,"unset"))
		dtst->interrodollar = unsetfunc(dtst, "void");
	else if (!ft_strcmp(dtst->cmd, "env"))
		dtst->interrodollar = envfunc(dtst, 1);
	else if (!ft_strcmp(dtst->cmd,"exit"))
		exit(exitfunc(dtst));
	else
	{
		absolute_path(dtst, dtst->cmd);
		fork_cmd(dtst);
	}
	return (0);
}
