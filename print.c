#include "minishell.h"

int	creatfile(t_data *dtst,char *file, char *arg)
{
	int fd;	
	
	fd = 1;
	printf("these are the files going through [%s]\n", file);
	if (file)
		fd = open(file, dtst->dir, 0666);
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
	
	while(files[i])
		i++;
	(i > 1) ? issingle = 0 : 1;
	i = 0;
	while(!issingle && files[i+1])
		creatfile(dtst, files[i++], NULL);
	creatfile(dtst, files[i], dtst->arg);
	return (0);
}
