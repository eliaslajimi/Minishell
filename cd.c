#include "minishell.h"

int	cdfunc(t_data *dtst)
{
	int	ret;
	char	*error_msg;

	ret = chdir(dtst->arg);
	if (ret == -1)
	{
		error_msg = "No such file or directory";
		error(dtst, error_msg, 3);
	}
	return (0);
}
