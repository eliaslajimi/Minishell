#include "minishell.h"

int	pwdfunc(t_data *dtst)
{
	char	*buf;
	char	*currentdir;
	int	size;
	
	(void)dtst;
	buf = NULL;
	size = 1000;
	currentdir = getcwd(buf, size);
	write(1, currentdir, ft_strlen(currentdir));
	write(1, "\n", 1);
	return (0);
}
