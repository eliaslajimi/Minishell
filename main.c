#include "minishell.h"

//Recursive Function seems more suitable
int	minishell_wrapper(t_data *dtst)
{
	char *inputcmd;
//FOR FUN
//-========================================
	char *buf;
	char *username;
	int color =90 +  rand() % 6;
	username = ft_calloc(1000,1);
	buf = NULL;
	!getlogin_r(username, 1000)? 
	printf("\033[0;%dm%s\033[0m", color, username) : (void)dtst;
	fflush(stdout);
	init(dtst);	
//=============================================
	inputcmd = NULL;
	write(1, "$> ", 3);
	get_next_line(1, &inputcmd);
	if ((inputcmd = ft_strtrim(inputcmd, " ")) && !ft_strcmp(inputcmd, ""))
		minishell_wrapper(dtst);
	if (inputcmd)
	{
		command_parsing(inputcmd, dtst);
		free(inputcmd);	
		check_error(dtst);
		cmdfunc(dtst);
	}
	return (0);
}

void	error(t_data *dtst)
{
	put_command(*dtst);//TO BE DELETED
	write(1, "Command not found\n", 18);
	free(dtst->arg);
	free(dtst->cmd);
	minishell_wrapper(dtst);
}

void	put_command(t_data dtst)//TO BE DELETED
{
	int i;
	
	i = -1;
	printf("\n===================\n");
	printf("this is your cmd: [\033[0;31m%s\033[0m]\n", dtst.cmd);	
	while(dtst.flags[++i])
		printf("this is your flag n%d: [\033[0;31m%s\033[0m]\n", i+1, dtst.flags[i]);
	printf("this is your argument: [\033[0;31m%s\033[0m]\n", dtst.arg);
	printf("\n===================\n");
}

void	retrieve_from_flags(t_data *dtst)
{
	int k;
	int j;
	char *str;

	k = 0;
	j = 0;
	str = NULL;
	while (dtst->flags[k])
	{
		if (dtst->flags[k][0] != '-')
		{
			j = k + 1;
			dtst->arg = ft_strjoin(dtst->arg, " ");//allocation need to be freed
			dtst->arg = ft_strjoin(dtst->arg, dtst->flags[k]);//allocation need to be freed
			free(dtst->flags[k]);
			dtst->flags[k] = NULL;
		}
		++k;
	}
	if (j != k)
		error(dtst);
}

int	command_parsing(char *inputcmd, t_data *dtst)
{
	int i;	
	int k;

	k = -1;
	i = 0;
	while(inputcmd[i] && !ft_isspace(inputcmd[i++]));
	dtst->cmd = ft_strndup(inputcmd, i);//allocation need to be freed
	dtst->flags = ft_split(inputcmd + i, ' ');//allocation need to be freed
	retrieve_from_flags(dtst);
	dtst->cmd = ft_strtrim(dtst->cmd, " ");//Is this allocating memory ??
	dtst->arg = ft_strtrim(dtst->arg, " ");//Is this allocating memory ??
	return (0);
}


int	check_error(t_data *dtst)
{
	if (!ft_strcmp(dtst->cmd,"echo") && dtst->flags && dtst->flags[0] && ft_strcmp(dtst->flags[0], "-n"))
		error(dtst);
	if ((!ft_strcmp(dtst->cmd,"cd") || !ft_strcmp(dtst->cmd, "pwd") ||
	 !ft_strcmp(dtst->cmd, "export") || !ft_strcmp(dtst->cmd, "unset") ||
	!ft_strcmp(dtst->cmd, "exit")) && dtst->flags[0])
		error(dtst);
	if (!ft_strcmp(dtst->cmd, "env") && (dtst->flags[0] || dtst->arg))	
		error(dtst);
	if (ft_strcmp(dtst->cmd, "echo") && ft_strcmp(dtst->cmd, "cd")  && ft_strcmp(dtst->cmd, "pwd") && 
		ft_strcmp(dtst->cmd, "export") && ft_strcmp(dtst->cmd, "unset") && ft_strcmp(dtst->cmd, "env")
		&& ft_strcmp(dtst->cmd, "exit"))
		error(dtst);
	return (0);
}


int	cmdfunc(t_data *dtst)
{
	(void)dtst;
	if (!ft_strcmp(dtst->cmd,"echo"))
		echofunc(dtst);
	if (!ft_strcmp(dtst->cmd,"cd"))
		cdfunc(dtst);//Done
	if (!ft_strcmp(dtst->cmd,"pwd"))
		pwdfunc(dtst);//Done
	if (!ft_strcmp(dtst->cmd,"export"))
		//exportfunc();
	if (!ft_strcmp(dtst->cmd,"unset"))
		//unsetfunc();
	if (!ft_strcmp(dtst->cmd,"env"))
		//envfunc();
	if (!ft_strcmp(dtst->cmd,"exit"))
		//exitfunc();
	put_command(*dtst);//TO BE DELETED
	minishell_wrapper(dtst);
	 return (0);
}

int	init(t_data *dtst)
{
	dtst->cmd = ft_calloc(1,1);
	dtst->arg = ft_calloc(1,1);
	return (0);
}

int	main()
{
	t_data	dtst;
	minishell_wrapper(&dtst);
	return (0);
}
