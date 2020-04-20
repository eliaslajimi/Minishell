#include "minishell.h"

int	echofunc(t_data *dtst)
{
	dtst->arg = ft_strtrim(dtst->arg,"\"");//allocation ?
	write(1, dtst->arg, ft_strlen(dtst->arg));	
	!dtst->flags[0] ? write(1, "\n", 1) : (void)dtst;
	return (0);
}
