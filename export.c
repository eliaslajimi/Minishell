#include "minishell.h"

int	exportfunc(t_data *dtst)
{
	int	i;

	i = 0;
	if (!ft_strcmp(dtst->arg, ""))
	{
		return (envfunc(dtst, 1));
	}
	else if (ft_intheset('=', dtst->arg))
	{
		while (dtst->arg[i] != '=')
			i++;
		if (i == 0)
		{
			printf("pas de premier arg\n");
			return (1);
		}
		t_list	*newnode = ft_lstnew(NULL);
		newnode->content = ft_strdup(dtst->arg);
		ft_lstadd_back(&dtst->env_lst, newnode);
	}
	return (0);
}
