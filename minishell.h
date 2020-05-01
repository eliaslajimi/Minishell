#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

typedef	struct		s_data
{
	char		*cmd;
	char		**flags;		
	char		*arg;
	int		dir;
	char		*file;
	t_list		*env_lst;
}			t_data;


int	minishell_wrapper(t_data *dtst);
void	error(t_data *dtst);
void	put_command(t_data dtst);
void	retrieve_from_flags(t_data *dtst);
int	command_parsing(char *inputcmd, t_data *dtst);
int	check_error(t_data *dtst);
int	cmdfunc(t_data *dtst);
int	init(t_data *dtst);
int	echofunc(t_data *dtst);
int	cdfunc(t_data *dtst);
int	pwdfunc(t_data *dtst);

t_list	*get_env_var(char **envp);
void	envfunc(t_data *dtst, int fd);

# endif
