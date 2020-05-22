#include "minishell.h"

int	pwdfunc(t_data *dtst)
{
	char	*buf;
	char	*currentdir;
	int	size;
	
	
	buf = NULL;
	size = 1000;
	free(dtst->arg);
	currentdir = getcwd(buf, size);
	dtst->arg = currentdir;
	printcommand(dtst);
	return (0);
}
