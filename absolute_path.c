#include "minishell.h"

//maybe needs a cleaner way to check for a file's existence
static int	file_exists(const char *filename)
{
	int	fd;	
	
	if ((fd = open(filename, O_RDONLY)) > 0)
	{
		close(fd);
		return (1);
	}
	else
	{	
		return (0);
	}
}

void	absolute_path(t_data *dtst, char *cmd)
{
	int	i;
	t_list	*tmp;
	char	*bin;
	char	*temp;
	char	*path;
	char	**path_split;

	i = 0;
	temp = NULL;
	tmp = dtst->env_lst;
	while (tmp->next && ft_strncmp(tmp->content, "PATH", 4))
	{
		tmp = tmp->next;
	}
	//if path doesn't exist, we put on an arbitrary one
	if (!(path = ft_strdup(tmp->content)))
	{
		path = ft_strdup("/bin:/usr/local/bin:/usr/bin:/usr/local/sbin");
	}

	
	// let's check if cmd is the absolute path
	if (cmd[0] != '/' && ft_strncmp(cmd, "./", 2) != 0)
	{
		path_split = ft_split(path, ':');
		ft_strdel(&path);

		while (path_split[i])
		{
			if (!(bin = ft_calloc(sizeof(char), ft_strlen(path_split[i]) + 1 + ft_strlen(cmd) + 1)))
				return;
			temp = ft_strjoin(bin, path_split[i]);
			bin = temp;
			ft_strdel(&temp);
			temp = ft_strjoin(bin, "/");
			bin = temp;
			ft_strdel(&temp);
			temp = ft_strjoin(bin, cmd);
			bin = temp;
			ft_strdel(&temp);

			if (file_exists(bin))
			{
				dtst->abs_path_cmd = ft_strdup(bin);
				break;
			}
			i++;
		}
		ft_free_tab(path_split);
	}
	else
	{
		dtst->abs_path_cmd = ft_strdup(cmd);
		ft_strdel(&path);
	}
}
