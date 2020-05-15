#include "minishell.h"

static int	 ft_lstdelnode(t_list **lst, char *data, int datalen)
{
	t_list	*current;
	t_list	*previous;

	previous = NULL;
	current = *lst;
	while (current)
	{
		if (ft_strncmp(current->content, data, datalen) == 0)
		{
			if (previous == NULL)
				*lst = current->next;
			else
				previous->next = current->next;
			free(current);
			return (1);
		}
		if (current->next == NULL)
			break;
		previous = current;
		current = current->next;
	}
	return (0);
}

void	unsetfunc(t_data *dtst, char *exportarg)
{
	int	res;
	int	arglen;
	char	*param;
	if (ft_strcmp(dtst->arg, "") != 0)
	{
		if (ft_strcmp(exportarg, "void") == 0)
			param = dtst->arg;
		else
			param = exportarg;
		arglen = ft_strlen(param);
		res = ft_lstdelnode(&dtst->env_lst, param, arglen);
		dtst->interrodollar = 0;
	}
	else
		ft_putstr("unset: not enough arguments\n");
}
