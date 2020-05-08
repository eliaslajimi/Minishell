#include "minishell.h"

int	fork_cmd(t_data *dtst)
{
	pid_t	pid;
	char	**new_argv;
	char	**new_envp;

	new_argv = malloc(sizeof(char*) * 2);
	new_envp = malloc(sizeof(char*) * 1);
	new_argv[0] = ft_strdup(dtst->cmd);
	new_argv[1] = NULL;
	new_envp[0] = NULL;
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
		waitpid(pid, 0, 0);
		kill(pid, SIGTERM); //default termination signal
	}
	return (0);
}
