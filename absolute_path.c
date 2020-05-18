#include "minishell.h"

//Havent checked if this thing works
static int	file_exists(const char *filename)
{
	static int ret;
	
	(access(filename, F_OK)) != -1 ?//function from unistd, allowed right???
	ret = -1  : (void)ret;
	return (ret);
//	if ((fd = open(filename, O_RDONLY)) > 0)
//	{
//		close(fd);
//		return (1);
//	}
//	else
//	{	
//		return (0);
//	}
}

int	cmdpath(t_data *dtst,char *path,char *cmd)
{
	int	i;
	char	*bin;
	char	*temp;
	char	**path_split;

	i = 0;
	temp = NULL;
	bin = NULL;
	if (cmd[0] != '/' && ft_strncmp(cmd, "./", 2) != 0)
	{
		path_split = ft_split(path, ':');
		ft_strdel(&path);

		while (path_split[i])
		{
			if (!(bin = ft_calloc(sizeof(char), ft_strlen
			(path_split[i]) + 1 + ft_strlen(cmd) + 1)))
				return (0);;
			temp = ft_strjoin(bin, path_split[i]);
			bin = temp;
			ft_strdel(&temp);
			temp = ft_strjoin(bin, "/");
			bin = temp;
			ft_strdel(&temp);
			temp = ft_strjoin(bin, cmd);
			bin = temp;
			ft_strdel(&temp);

			if (file_exists(bin) == 1)
			{
				dtst->file_exists = 1;
				dtst->abs_path_cmd = ft_strdup(bin);
				break;
			}
			i++;
		}
		ft_free_tab(path_split);
		if (dtst->file_exists == 0)
			error(dtst);
		else
			dtst->file_exists = 0;
	}
	else
	{
		dtst->abs_path_cmd = ft_strdup(cmd);
		ft_strdel(&path);
	}
	return (0);
}

void	absolute_path(t_data *dtst, char *cmd)
{
	t_list	*tmp;
	char	*path;

	tmp = dtst->env_lst;
	while (tmp->next && ft_strncmp(tmp->content, "PATH", 4))
		tmp = tmp->next;
	if (!(path = ft_strdup(tmp->content)))
		path = ft_strdup("/bin:/usr/local/bin:/usr/bin:/usr/local/sbin");
	cmdpath(dtst, path, cmd);
}
