/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <cmcgahan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 14:35:52 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/10/12 16:22:04 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_wrapper(t_data *dtst)
{
	int		end = 0;
	char	*inputcmd;

	deleteme();//TO BE DELETED

	init(dtst);
	inputcmd = NULL;
	write(1, "$> ", 3);
	get_next_line(1, &inputcmd);
	if ((inputcmd = ft_strtrim(inputcmd, " "))
	&& !ft_strcmp(inputcmd, ""))
		minishell_wrapper(dtst);	
	myparser(inputcmd, &dtst->p);
	executor(dtst);
	free_parser(&dtst->p);
	if (end == 0)
		minishell_wrapper(dtst);
	return (0);
}

void	error(t_data *dtst, char *error_msg, int errnum)
{
	//put_command(*dtst);//TO BE DELETED
	write(1, dtst->env_shell, ft_strlen(dtst->env_shell));
	write(1, ": ", 2);
	if (errnum == 1 || errnum == 3)
	{
		write(1, dtst->cmd, ft_strlen(dtst->cmd));
		write(1, ": ", 2);
	}
	if (errnum == 2 || errnum == 3)
	{
		write(1, dtst->arg, ft_strlen(dtst->arg));
		write(1, ": ", 2);
	}
	write(1, error_msg, ft_strlen(error_msg));
	ft_strdel(&dtst->arg);
	ft_strdel(&dtst->cmd);
	dtst->interrodollar = 1;
	minishell_wrapper(dtst);
}

void	sigint_handler()
{
	write(1, "\n", 1);
	deleteme();
	write(1, "$> ", 3);
}

void	printusage()
{
	ft_putstr("Here are all the commands and options :\n");
	ft_putstr("	pwd\n");
	ft_putstr("	echo	<text>\n");
	ft_putstr("	env\n");

}

int		main(int argc, char **argv, char **envp)
{
	if (argc == 2 && !ft_strcmp(argv[1], "--help"))
	{
		printusage();
	}
	else if (argc != 1 || argv[1] != '\0')
	{
		ft_putendl_fd("The program doesn't need any arguments", 2);
		return (1);
	}
	t_data	dtst;
	init(&dtst);
	dtst.env_lst = get_env_var(envp);
	dtst.env_shell = find_node(&dtst.env_lst, "SHELL") + 6;
	dtst.interrodollar = 0;
//	signal(SIGINT, sigint_handler);
	minishell_wrapper(&dtst);
	return (0);
}
