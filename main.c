#include "minishell.h"

int	minishell_wrapper(t_data *dtst)
{
	char	*inputcmd;

	deleteme();//TO BE DELETED

	init(dtst);	
	inputcmd = NULL;
	write(1, "$> ", 3);
	get_next_line(1, &inputcmd);
	if ((inputcmd = ft_strtrim(inputcmd, " "))
	&& !ft_strcmp(inputcmd, ""))
		minishell_wrapper(dtst);
	dtst->split_cmd = ft_split(inputcmd, ';');
	formatdata(dtst, inputcmd);
	return (0);
}

void	error(t_data *dtst)
{
	put_command(*dtst);//TO BE DELETED
	write(1, "Command not found\n", 18);
	free(dtst->arg);
	free(dtst->cmd);
	dtst->interrodollar = 1;
	minishell_wrapper(dtst);
}


int	init(t_data *dtst)
{
	dtst->cmd = ft_calloc(1,1);
	dtst->arg = ft_calloc(1,1);
	dtst->file = ft_calloc(1,1);
	dtst->dir = 0;
	dtst->pipe = 0;
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
