#include "minishell.h"

int	echofunc(t_data *dtst)
{
	int fd;

	fd = 0;
	if (!dtst->flags[0])
		dtst->arg = ft_strjoin(dtst->arg, "\n");
	printcommand(dtst);
//	if (dtst->pipe)
//		pipe_commands(dtst);
	free(dtst->arg);
	dtst->arg = "";
	dtst->interrodollar = 0;
	return (0);
}
