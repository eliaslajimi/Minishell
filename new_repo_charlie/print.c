#include "minishell.h"

int	creatfile(t_data *dtst,char *file, char *arg)
{
	int fd;	
	
	fd = 1;
	if (file)
		fd = open(file, dtst->dir, 0666);
	else if (!file && dtst->pipe > 0)
		fd = dtst->filedes[1];
	if (arg)
		write(fd, arg, ft_strlen(arg));
	return (0);
}

int	printcommand(t_data *dtst)
{
	int i;
	int issingle;
	char **files;

	i = 0;
	issingle = 1;
	files = ft_split(dtst->file, ' ');
	if (dtst->pipe)
		pipe(dtst->filedes);
	while(files[i])
		i++;
	(i > 1) ? issingle = 0 : 1;
	i = 0;
	while(!issingle && files[i+1])
		creatfile(dtst, files[i++], NULL);
	creatfile(dtst, files[i], dtst->arg);
	return (0);
}
