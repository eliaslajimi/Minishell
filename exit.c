#include "minishell.h"

int	exitfunc(t_data *dtst)
{
	int	status;

	status = 0;
	if (dtst->arg != NULL)
		status = ft_atoi(dtst->arg);
	//free tout ce qu'il faut
	//exit(status);
	return (status);
}
