#include "minishell.h"

t_list	*get_env_var(char **envp)
{
	int	i;
	t_list	*env_lst;

	i = 0;
	env_lst = ft_lstnew(NULL);
	env_lst->content = ft_strdup(envp[i]);
	i++;
	while (envp[i])
	{
		t_list *newlst = ft_lstnew(NULL);
		newlst->content = ft_strdup(envp[i]);
		ft_lstadd_back(&env_lst, newlst);
		i++;
	}
	ft_lstadd_back(&env_lst, NULL);
	return (env_lst);
}

void	envfunc(t_data *dtst, int fd)
{
	while (dtst->env_lst->next)
	{
		ft_putendl_fd(dtst->env_lst->content, fd);
		dtst->env_lst = dtst->env_lst->next;
	}
}
