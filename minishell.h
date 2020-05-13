#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#include "libft/libft.h"

#define APPEND (O_RDWR | O_APPEND | O_CREAT)
#define OUTPUT (O_RDWR | O_RDONLY)
#define INPUT (O_RDWR | O_TRUNC | O_CREAT)


typedef	struct		s_data
{
	char		quote_type;
	char		*quoteresult;
	char		*cmd;
	char		**flags;		
	char		*arg;
	int		dir;
	char		*file;
	t_list		*env_lst;
	char		**split_cmd;
	char		*abs_path_cmd;
	int		file_exists;
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
void	get_direc(t_data *dtst, int k);

t_list	*get_env_var(char **envp);
void	envfunc(t_data *dtst, int fd);
void	absolute_path(t_data *dtst, char *cmd);
int	fork_cmd(t_data *dtst);
int	exportfunc(t_data *dtst);
void	unsetfunc(t_data *dtst);

# endif
