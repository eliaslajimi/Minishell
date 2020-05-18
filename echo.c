#include "minishell.h"

int	echofunc(t_data *dtst)//Should we Impliment Quote and variable management?
{
	int fd;

	fd = 0;
	printf("\nthis is your arg: ...%s...\n", dtst->arg);
	if (dtst->dir)
	{
		fd = open(dtst->file,  dtst->dir, 0666);
		write(fd, dtst->arg, ft_strlen(dtst->arg));
	}
	else 
	{
		if (!dtst->flags[0])
			dtst->arg = ft_strjoin(dtst->arg, "\n");
		write(1, dtst->arg, ft_strlen(dtst->arg));
		
	}
	dtst->interrodollar = 0;
	return (0);
}
