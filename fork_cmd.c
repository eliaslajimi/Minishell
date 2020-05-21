#include "minishell.h"

int	fork_cmd(t_data *dtst)
{
	pid_t	pid;
	char	*new_argv[2];
	char	*new_envp[1];

	new_argv[0] = ft_strdup(dtst->cmd);
	new_argv[1] = NULL;
	new_envp[0] = NULL;
	pid = fork();
	if (pid < 0)
	{
		ft_putstr("fork failed\n");
		ft_strdel(&new_argv[0]);
		return (0);
	}
	else if (pid == 0)
		execve(dtst->abs_path_cmd, new_argv, new_envp);
	else
	{
		waitpid(pid, 0, 0);
		kill(pid, SIGTERM);
	}
	ft_strdel(&new_argv[0]);
	return (0);
}
