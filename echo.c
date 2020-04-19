#include "minishell.h"

int	echofunc(t_data *dtst)
{
	dtst->arg = ft_strtrim(dtst->arg,"\"");
	write(1, dtst->arg, ft_strlen(dtst->arg));	
	write(1, "\n", 1);
	return (0);
}
