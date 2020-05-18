#include "minishell.h"

int	deleteme()
{
	char	*buf;
	char	*username;
	int	color =90 +  rand() % 6;
	username = ft_calloc(1000,1);
	buf = NULL;
	!getlogin_r(username, 1000)? 
	printf("\033[0;%dm%s\033[0m", color, username) : (void)buf;
	fflush(stdout);
	return (0);
}
void	put_command(t_data dtst)//TO BE DELETED
{
	int i;
	
	i = -1;
	char *red = "[\033[0;31m";
	char *reset = "\033[0m]";
	printf("===================\n");
	printf("this is your cmd: %s%s%s\n",red, dtst.cmd, reset);	
	while(dtst.flags[++i])
		printf("this is your flag n%d: %s%s%s\n", i+1, red, dtst.flags[i], reset);
	printf("this is your argument: %s%s%s\n", red, dtst.arg, reset);
	if (dtst.dir == 0)
		printf("this is your redirection: %s%s%s\n",red,  "", reset);
	if (dtst.dir == 1)
		printf("this is your redirection: %s%s%s\n", red,"<", reset);
	if (dtst.dir == 2)
		printf("this is your redirection: %s%s%s\n",red, ">", reset);
	if (dtst.dir == 3)
		printf("this is your redirection: %s%s%s\n",red, ">>",reset);
	if (dtst.pipe)
		printf("pipe activated");
	printf("this is your file: %s%s%s",red, dtst.file, reset);
	printf("\n===================\n");
	fflush(stdout);
}
