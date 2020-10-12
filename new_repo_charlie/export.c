#include "minishell.h"

static void	printit(char *tmp)
{
	ft_putstr("declare -x \"");
	ft_putstr(tmp);
	ft_putstr("\"\n");
}

static void	iter_and_print(int nbfalse, char *booltab, t_list *env_lst)
{
	int	i;
	int	j;
	t_list	*iter;
	char	*tmp;

	while (--nbfalse >= 0)
	{
		i = -1;
		j = 0;
		iter = env_lst;
		while (booltab[++i] == '0')
			iter = iter->next;
		tmp = iter->content;
		while (i < ft_lstsize(env_lst))
		{
			if (ft_strcmp(tmp, iter->content) >= 0 && booltab[i] == '1')
			{
				tmp = iter->content;
				j = i;
			}
			i++;
			iter = iter->next;
		}
		booltab[j] = '0';
		printit(tmp);
	}
}

static int	print_sorted_list(t_list *env_lst)
{
	int	i;
	int	listsize;
	char	*booltab;
	t_list	*iter;
	int	nbfalse;

	i = 0;
	listsize = ft_lstsize(env_lst);
	booltab = ft_calloc(listsize, 1);
	iter = env_lst;
	while (i++ < listsize)
		booltab[i] = '1';
	nbfalse = listsize;
	iter_and_print(nbfalse, booltab, env_lst);
	return (0);
}

int	exportfunc(t_data *dtst)
{
	int	i;
	char	**split_arg;
	t_list	*newnode;

	i = 0;
	if (!ft_strcmp(dtst->arg, ""))
		return (print_sorted_list(dtst->env_lst));
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
		newnode = ft_lstnew(NULL);
		newnode->content = ft_strdup(dtst->arg);
		ft_lstadd_back(&dtst->env_lst, newnode);
	}
	return (0);
}
