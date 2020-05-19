#include "minishell.h"

int	creatfile(t_data *dtst,char *file, char *arg)
{
	int fd;	
	
	if (file)
		fd = open(file, dtst->dir, 0666);
	if (arg)
		write(fd, arg, ft_strlen(arg));
	return (0);
}

int	printcommand(t_data *dtst)
{
	int i;
	char **files;

	i = 0;
	files = ft_split(dtst->file, ' ');
	while(files[i])
		creatfile(dtst, files[i++], NULL);
	creatfile(dtst, files[i], dtst->arg);
	return (0);
}
