#include "minishell.h"

int	fork_cmd(t_data *dtst)
{
	pid_t	pid;
	int	status;
	char	*new_argv[] = {"ls", NULL};
	char	*new_envp[] = {NULL};

	status = 0;
	pid = fork();
	if (pid < 0)
	{
		ft_putstr("fork failed\n");
		return (0);
	}
	else if (pid == 0)
	{
		//child process
		ft_putstr("Child process\n");
		execve(dtst->abs_path_cmd, new_argv, new_envp);
	}
	else
	{
		//parent process
		ft_putstr("we gotta wait or smthng \n");
	}
	return (0);
}
