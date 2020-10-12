#include "minishell.h"

int	pipe_commands(t_data *dtst)
{
	printf("pipe it\n");
	//dtst->arg = dtst->filedes[0];
	read(dtst->filedes[0], dtst->arg, 10000); //dirty padding...
	dtst->cmd = dtst->r_cmd;
//	cmdfunc(dtst);
	return (0);	
}
