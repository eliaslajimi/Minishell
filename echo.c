#include "minishell.h"

int	echofunc(t_data *dtst)
{
	int fd;

	fd = 0;
//	if (dtst->dir)
//	{
//		fd = open(dtst->file,  dtst->dir, 0666);
//		write(fd, dtst->arg, ft_strlen(dtst->arg));
//	}
//	else 
//	{
	if (!dtst->flags[0])
		dtst->arg = ft_strjoin(dtst->arg, "\n");
		//write(1, dtst->arg, ft_strlen(dtst->arg));
		
//	}
	printcommand(dtst);//fd is for the file/mod is append or not
	dtst->interrodollar = 0;
	return (0);
}
