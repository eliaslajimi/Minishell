#include "minishell.h"

//Recursive Function seems more suitable
int	minishell_wrapper(t_data *dtst)
{
	int	i;
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
	i = 0;
	write(1, "$> ", 3);
	get_next_line(1, &inputcmd);
	if ((inputcmd = ft_strtrim(inputcmd, " ")) && !ft_strcmp(inputcmd, ""))
		minishell_wrapper(dtst);
/*	if (inputcmd)
	{
		command_parsing(inputcmd, dtst);
		free(inputcmd);	
		check_error(dtst);
		cmdfunc(dtst);
	}
*/
	dtst->split_cmd = ft_split(inputcmd, ';');
	while (dtst->split_cmd[i])
	{
		inputcmd = ft_strtrim(dtst->split_cmd[i], " ");
		command_parsing(inputcmd, dtst);
		free(inputcmd);
		check_error(dtst);
		cmdfunc(dtst);
		i++;
		if (dtst->split_cmd[i] == NULL)
		{
			ft_free_tab(dtst->split_cmd);
			minishell_wrapper(dtst);
		}
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
	printf("this is your file: %s%s%s",red, dtst.file, reset);
	printf("\n===================\n");
	fflush(stdout);
}


int	cmdfunc(t_data *dtst)
{
	if (!ft_strcmp(dtst->cmd,"echo"))
	{
		echofunc(dtst);
	}
	else if (!ft_strcmp(dtst->cmd,"cd"))
	{
		cdfunc(dtst);//Done
	}
	else if (!ft_strcmp(dtst->cmd,"pwd"))
	{
		pwdfunc(dtst);//Done
	}
	else if (!ft_strcmp(dtst->cmd,"export"))
	{
		exportfunc(dtst);
	}
	else if (!ft_strcmp(dtst->cmd,"unset"))
	{
		//unsetfunc();
	}
	else if (!ft_strcmp(dtst->cmd, "env"))
	{
		envfunc(dtst, 1);//Done
	}
	else if (!ft_strcmp(dtst->cmd,"exit"))
	{
		//exitfunc();
	}
	else
	{
		absolute_path(dtst, dtst->cmd);
		fork_cmd(dtst);
	}
	put_command(*dtst);//TO BE DELETED
	return (0);
}

int	init(t_data *dtst)
{
	dtst->cmd = ft_calloc(1,1);
	dtst->arg = ft_calloc(1,1);
	dtst->file = ft_calloc(1,1);
	dtst->dir = -1;
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
		printf("%s\n", argv[0]);
	t_data	dtst;
	dtst.env_lst = get_env_var(envp);
	minishell_wrapper(&dtst);
	return (0);
}
