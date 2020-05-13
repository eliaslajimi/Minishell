#include "minishell.h"

int	exportfunc(t_data *dtst)
{
	if (!ft_strcmp(dtst->arg, ""))
	{
		envfunc(dtst, 1);
	}
	else
	{
		t_list	*newnode = ft_lstnew(NULL);
		newnode->content = ft_strdup(dtst->arg);
		ft_lstadd_back(&dtst->env_lst, newnode);
	}
	return (0);
}
