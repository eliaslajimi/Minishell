#include "minishell.h"

int	echofunc(t_data *dtst)//Should we Impliment Quote and variable management?
{
	dtst->arg = ft_strtrim(dtst->arg,"\"");//allocation ?
	write(1, dtst->arg, ft_strlen(dtst->arg));	
	!dtst->flags[0] ? write(1, "\n", 1) : (void)dtst;
	return (0);
}
