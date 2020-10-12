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
