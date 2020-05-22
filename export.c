#include "minishell.h"

int	exportfunc(t_data *dtst)
{
	int	i;
	char	**split_arg;

	i = 0;
	if (!ft_strcmp(dtst->arg, ""))
		return (envfunc(dtst, 1));
	else if (ft_intheset('=', dtst->arg))
	{
		split_arg = ft_split(dtst->arg, '=');
		if (find_node(&dtst->env_lst, split_arg[0]) != NULL)
			unsetfunc(dtst, split_arg[0]);
		ft_free_tab(split_arg);
		while (dtst->arg[i] != '=')
			i++;
		if (i == 0)
			return (1);
		t_list	*newnode = ft_lstnew(NULL);
		newnode->content = ft_strdup(dtst->arg);
		ft_lstadd_back(&dtst->env_lst, newnode);
	}
	return (0);
}
