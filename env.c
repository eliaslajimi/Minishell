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
	int count = 0;

	t_list	*tmp;

	tmp = dtst->env_lst;
	while (tmp->next)
	{
		count++;
		ft_putendl_fd(tmp->content, fd);
		tmp = tmp->next;
	}
	ft_putendl_fd(tmp->content, fd);
	count++;
	printf("il y a %d elements\n", count);
}
