#include "minishell.h"

int	pipe_commands(t_data *dtst)
{
	//dtst->arg = dtst->filedes[0];
	read(dtst->filedes[0], dtst->arg, 10000); //dirty padding...
	dtst->cmd = dtst->r_cmd;
	cmdfunc(dtst);
	return (0);	
}
