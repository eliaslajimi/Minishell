#include "minishell.h"

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
