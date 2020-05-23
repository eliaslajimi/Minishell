#include "minishell.h"

int	cdfunc(t_data *dtst)
{
	int	ret;
	char	*temp;
	char	*error_msg;

	temp = ft_strdup(dtst->arg);
	free(dtst->arg);
	dtst->arg = NULL;
	if (dtst->file)
		printcommand(dtst);
	dtst->arg = temp;
	ret = chdir(dtst->arg);
	if (ret == -1)
	{
		error_msg = "No such file or directory";
		error(dtst, error_msg, 3);
	}
	return (0);
}
