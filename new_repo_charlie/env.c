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

int	envfunc(t_data *dtst, int fd)
{
	char	*result;
	t_list	*tmp;
	(void)fd;

	tmp = dtst->env_lst;
	result = NULL;
	while (tmp->next)
	{
		//ft_putendl_fd(tmp->content, fd);
		result = ft_strjoin(result, tmp->content);
		result = ft_strjoin(result, "\n");
		tmp = tmp->next;
	}
	result = ft_strjoin(result, tmp->content);
	result = ft_strjoin(result, "\n");
	//ft_putendl_fd(tmp->content, fd);
	free(dtst->arg);
	dtst->arg = result;
	printcommand(dtst);
	return(0);
}
