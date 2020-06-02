#include "minishell.h"

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
		error(dtst, "no such file or command\n", 1);
}


void	retrieve_from_flags(t_data *dtst)//Needs some serious refactoring lol
{
	int k;
	int j;
	char *str;
	int isfile;

	k = 0;
	j = 0;
	str = NULL;
	isfile = 0;
	while (dtst->flags[k])
	{
		if (dtst->filedes[0] >= 0)
		{
			char *temp;
			dtst->arg = NULL;
			temp = calloc(1001, sizeof(char));
			dtst->cmd = ft_strtrim(dtst->flags[k], " ");
			read(dtst->filedes[0], temp,1000);//dirty padding of 1000/loop fails 
			dtst->arg = ft_strdup(temp);
			close(dtst->filedes[1]);
			close(dtst->filedes[0]);
			dtst->filedes[1] = -1;
			dtst->filedes[0] = -1;
		}
		if (dtst->flags[k][0] == '<' || dtst->flags[k][0] == '>')
		{
			get_direc(dtst, k);
			dtst->flags[k] = NULL;
			isfile = 1;
		}
		else if (isfile == 1)
		{
			dtst->file = realloc(dtst->file, sizeof(dtst->file) + 1 +
			sizeof(dtst->flags[k]));
			dtst->file = ft_strjoin(dtst->file, " ");
			dtst->file = ft_strjoin(dtst->file, dtst->flags[k]);
			dtst->file = ft_strtrim(dtst->file," ");
			isfile = 0;
			
		}
		else if ((dtst->flags[k][0] != '-'
		&&  dtst->flags[k][0] != '|' && isfile == 0 && dtst->pipe < 0) ||
		(isquote(dtst->flags[k][0]) && dtst->pipe < 0))
		{
			dtst->flags[k] = removequote(dtst->flags[k]);
			j = k + 1;
			dtst->arg = ft_strjoin(dtst->arg, " ");
			dtst->arg = ft_strjoin(dtst->arg, dtst->flags[k]);
			free(dtst->flags[k]);
			dtst->flags[k] = NULL;
		}
		else if (dtst->flags[k][0] == '|')
		{
			dtst->pipe = 1;
			dtst->arg = ft_strtrim(dtst->arg, " ");	//formating data
			if (ft_intheset('$', dtst->arg))	//formating data
				dtst->arg = ft_dollar(dtst);	//formating data
			check_error(dtst);
			cmdfunc(dtst);
			printf("this is the one I want to see %d, %d\n", dtst->pipe, dtst->filedes[0]);	
		}
		++k;
	}
	put_command(*dtst);
}

int	command_parsing(char *inputcmd, t_data *dtst)
{
	int i;	
	int k;

	k = -1;
	i = 0;
	while (inputcmd[i] && !ft_isspace(inputcmd[i++]));
	dtst->cmd = ft_strndup(inputcmd, i);//allocation need to be freed
	dtst->cmd = ft_strtrim(dtst->cmd, " ");//allocating memory
	if (ft_intheset('$', dtst->cmd))
	{
		dtst->cmd = ft_dollar(dtst);
		if (dtst->cmd == NULL)
			return (-1);
	}
	dtst->flags = ft_split(inputcmd + i, ' ');//need to be freed
	retrieve_from_flags(dtst);
	dtst->arg = ft_strtrim(dtst->arg, " ");	//formating data
	if (ft_intheset('$', dtst->arg))	//formating data
		dtst->arg = ft_dollar(dtst);	//formating data
	return (0);
}

int	check_error(t_data *dtst)
{
	if (!ft_strcmp(dtst->cmd,"echo")
	&& dtst->flags && dtst->flags[0]
	&& ft_strcmp(dtst->flags[0], "-n"))
		error(dtst, "no such file or command\n", 1);
	if ((!ft_strcmp(dtst->cmd,"cd") ||
	!ft_strcmp(dtst->cmd, "pwd") ||
	!ft_strcmp(dtst->cmd, "export") ||
	!ft_strcmp(dtst->cmd, "unset") ||
	!ft_strcmp(dtst->cmd, "exit")) &&
	dtst->flags[0])
		error(dtst, "no such file or command\n", 1);
	if (!ft_strcmp(dtst->cmd, "env") &&
	(dtst->flags[0]))
		error(dtst, "no such file or command\n", 1);
	return (0);
}
