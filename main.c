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

void	error(t_data *dtst, char *error_msg, int errnum)
{
	put_command(*dtst);//TO BE DELETED
	write(1, dtst->env_shell, ft_strlen(dtst->env_shell));
	write(1, ": ", 2);
	if (errnum == 1 || errnum == 3) // probleme de commande
	{
		write(1, dtst->cmd, ft_strlen(dtst->cmd));
		write(1, ": ", 2);
	}
	if (errnum == 2 || errnum == 3)
	{
		write(1, dtst->arg, ft_strlen(dtst->arg));
		write(1, ": ", 2);
	}
	// probleme d'argument
	write(1, error_msg, ft_strlen(error_msg));
	ft_strdel(&dtst->arg);
	ft_strdel(&dtst->cmd);
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

void	sigint_handler()
{
	write(1, "\n", 1);
	deleteme();
	write(1, "$> ", 3);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
		ft_putstr(argv[0]);
	t_data	dtst;
	dtst.env_lst = get_env_var(envp);
	dtst.env_shell = find_node(&dtst.env_lst, "SHELL") + 6;	
	signal(SIGINT, sigint_handler);
	minishell_wrapper(&dtst);
	return (0);
}
