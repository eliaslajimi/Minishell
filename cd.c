#include "minishell.h"

int	cdfunc(t_data *dtst)
{
	int ret;

	ret = chdir(dtst->arg);
	ret == -1 ? error(dtst) : (void)dtst;
	return (0);
}
