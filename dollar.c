#include "minishell.h"

static int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

char	*dollar_swap(char *inputcmd, t_data *dtst)
{
	int	i = 0;
	int	last;
	char	*str;
	char	*strjoined;
	char	**split_inputcmd;
	
	strjoined = ft_calloc(1,1);
	if (inputcmd != NULL)
	{
		split_inputcmd = ft_split(inputcmd, ' ');
		last = tablen(split_inputcmd);
		while (split_inputcmd[i] != '\0')
		{
			if (split_inputcmd[i][0] == '$' && split_inputcmd[i][1] != '\0')
			{
				str = find_node(&dtst->env_lst, split_inputcmd[i] + 1);
				if (str != NULL)
					strjoined = ft_strjoin_space(strjoined, str + ft_strlen(split_inputcmd[i]), i - last + 1);
				else
					strjoined = ft_strjoin_space(strjoined, split_inputcmd[i], i - last + 1);
			}
			else
				strjoined = ft_strjoin_space(strjoined, split_inputcmd[i], i - last + 1);
			i++;
				
		}
	}
	return (strjoined);
}

char	*find_node(t_list **lst, char *data)
{
	t_list	*iter;

	iter = *lst;
	while (iter)
	{
		if (ft_strncmp(iter->content, data, ft_strlen(data)) == 0)
			return (iter->content);
		else if (iter->next == NULL)
			break;
		iter = iter->next;
	}
	return (NULL);
}

char	*ft_dollar(t_data *dtst)
{
	char *str;
	char *cpy;

	str = find_node(&dtst->env_lst, dtst->cmd + 1);
	if (str != NULL)
	{
		cpy = ft_strdup(dtst->cmd);
		ft_strdel(&dtst->cmd);
		dtst->cmd = ft_strdup(str + ft_strlen(cpy));
		ft_strdel(&cpy);
		return (dtst->cmd);
	}
	else
		return (NULL);
}
