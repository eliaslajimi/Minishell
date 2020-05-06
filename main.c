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

//void	get_direc(t_data *dtst, int k)
//{
//	dtst->flags[k] = ft_strtrim(dtst->flags[k], " ");	
//	if (!ft_strcmp(dtst->flags[k], "<"))
//		dtst->dir = 1;
//	else if (!ft_strcmp(dtst->flags[k], ">"))
//		dtst->dir = 2;
//	else if (!ft_strcmp(dtst->flags[k], ">>"))
//		dtst->dir = 3;
//	else
//		error(dtst);
//}

//void	retrieve_from_flags(t_data *dtst)
//{
//	int k;
//	int j;
//	char *str;
//
//	k = 0;
//	j = 0;
//	str = NULL;
//	while (dtst->flags[k])
//	{
//		if (dtst->flags[k][0] == '<' || dtst->flags[k][0] == '>')
//			get_direc(dtst, k);
//		else if (dtst->flags[k][0] != '-' && !dtst->dir)
//		{
//			j = k + 1;
//			dtst->arg = ft_strjoin(dtst->arg, " ");//allocation need to be freed
//			dtst->arg = ft_strjoin(dtst->arg, dtst->flags[k]);//allocation need to be freed
//			free(dtst->flags[k]);
//			dtst->flags[k] = NULL;
//		}
//		else 
//			dtst->file = ft_strtrim(dtst->flags[k], " ");
//		++k;
//	}
//	if (j != k)
//		error(dtst);
//}






//===========================================
void	get_direc(t_data *dtst, int k)
{
	dtst->flags[k] = ft_strtrim(dtst->flags[k], " ");	
	if (!ft_strcmp(dtst->flags[k], "<"))
		dtst->dir = OUTPUT;
	else if (!ft_strcmp(dtst->flags[k], ">"))
		dtst->dir = INPUT;
	else if (!ft_strcmp(dtst->flags[k], ">>"))
		dtst->dir = APPEND;
	else
		error(dtst);
}

//int	command_parsing(char *inputcmd, t_data *dtst)
//{
//	int i;	
//	int k;
//
//	k = -1;
//	i = 0;
//	while(inputcmd[i] && !ft_isspace(inputcmd[i++]));
//	dtst->cmd = ft_strndup(inputcmd, i);//allocation need to be freed
//	dtst->flags = ft_split(inputcmd + i, ' ');//allocation need to be freed
//	retrieve_from_flags(dtst);
//	dtst->cmd = ft_strtrim(dtst->cmd, " ");//Is this allocating memory ??
//	dtst->arg = ft_strtrim(dtst->arg, " ");//Is this allocating memory ??
//	return (0);
//}

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
		if (dtst->flags[k][0] == '<' || dtst->flags[k][0] == '>')
		{
			get_direc(dtst, k);
			dtst->flags[k] = NULL;
			
		}
		else if (dtst->flags[k][0] != '-' && dtst->dir == -1)
		{
			j = k + 1;
			dtst->arg = ft_strjoin(dtst->arg, " ");//allocation need to be freed
			dtst->arg = ft_strjoin(dtst->arg, dtst->flags[k]);//allocation need to be freed
			free(dtst->flags[k]);
			dtst->flags[k] = NULL;
		}
		else 
			dtst->file = ft_strtrim(dtst->flags[k], " ");
		++k;
	}
}

//===========================================
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
	if (!ft_strcmp(dtst->cmd, "env") && (dtst->flags[0]))// || dtst->arg)) //dtst-arg pas conclu par nul, du coup on rentre d'office dans error
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
		//exportfunc();
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
	put_command(*dtst);//TO BE DELETED
//	minishell_wrapper(dtst);
	return (0);
}

int	init(t_data *dtst)
{
	dtst->cmd = ft_calloc(1,1);
	dtst->arg = ft_calloc(1,1);
	dtst->file = ft_calloc(1,1);
	dtst->dir = 0;
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
