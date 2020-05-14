#include "minishell.h"

void	get_direc(t_data *dtst, int k)//Parsing
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

void	retrieve_from_flags(t_data *dtst)//Parsing
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
			dtst->dir = 1;	
		}
		else if (dtst->flags[k][0] != '-' &&  dtst->dir == -1)
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

int	command_parsing(char *inputcmd, t_data *dtst)//Parsing
{
	int i;	
	int k;

	k = -1;
	i = 0;
	while(inputcmd[i] && !ft_isspace(inputcmd[i++]));
	dtst->cmd = ft_strndup(inputcmd, i);//allocation need to be freed	
	dtst->cmd = ft_strtrim(dtst->cmd, " ");//Is this allocating memory ??
	if (ft_intheset('$', dtst->cmd))
	{
		dtst->cmd = ft_dollar(dtst);
		if (ft_strcmp(dtst->cmd, NULL) == 0)
			i = 0;
	}
	dtst->flags = ft_split(inputcmd + i, ' ');//allocation need to be freed
	retrieve_from_flags(dtst);
	dtst->arg = ft_strtrim(dtst->arg, " ");//Is this allocating memory ??
	if (ft_intheset('$', dtst->arg))
		dtst->arg = ft_dollar(dtst);
	return (0);
}

int	check_error(t_data *dtst)//Parsing
{
	if (!ft_strcmp(dtst->cmd,"echo") && dtst->flags && dtst->flags[0] && ft_strcmp(dtst->flags[0], "-n"))
	{
		error(dtst);
	}
	if ((!ft_strcmp(dtst->cmd,"cd") || !ft_strcmp(dtst->cmd, "pwd") ||
	 !ft_strcmp(dtst->cmd, "export") || !ft_strcmp(dtst->cmd, "unset") ||
	!ft_strcmp(dtst->cmd, "exit")) && dtst->flags[0])
	{
		error(dtst);
	
	}
	if (!ft_strcmp(dtst->cmd, "env") && (dtst->flags[0]))// || dtst->arg)) //dtst-arg pas conclu par nul, du coup on rentre d'office dans error
	{
		error(dtst);
	}
/*	if (ft_strcmp(dtst->cmd, "echo") && ft_strcmp(dtst->cmd, "cd")  && ft_strcmp(dtst->cmd, "pwd") && 
		ft_strcmp(dtst->cmd, "export") && ft_strcmp(dtst->cmd, "unset") && ft_strcmp(dtst->cmd, "env")
		&& ft_strcmp(dtst->cmd, "exit"))
	{
		error(dtst);
	}
*/
	return (0);
}
