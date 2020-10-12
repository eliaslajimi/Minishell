#include "minishell.h"

static int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

static size_t	count_words(char *str, char *word)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[++i])
		if (ft_strnstr(&str[i], word, ft_strlen(str)) == &str[i])
			count++;
	return (count);
}

char		*replace_interrodollar(char *itoa_id, char *cmd)
{
	size_t	i;
	size_t	j;
	size_t	count;
	char	*result;

	count = count_words(cmd, "$?");
	if (!(result = malloc((ft_strlen(cmd) + count * (ft_strlen(itoa_id) - 2)) + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (j < ft_strlen(cmd) + count * (ft_strlen(itoa_id) - 2))
	{
		if (ft_strncmp(cmd + i, "$?", 2) == 0)
    		{
			ft_strcpy(&result[j], itoa_id, ft_strlen(itoa_id));
			i += 2;
			j += ft_strlen(itoa_id);
		}
		else
			result[j++] = cmd[i++];
	}
	result[j] = '\0';
	return (result);
} 

char	*dollar_swap(char *inputcmd, t_data *dtst)
{
	int	i = 0;
	int	last;
	char	*s;
	char	*sj;
	char	**split_ic;

	sj = ft_calloc(1,1);
	if (inputcmd != NULL)
	{
		split_ic = ft_split(inputcmd, ' ');
		last = tablen(split_ic);
		while (split_ic[i] != NULL)
		{
			if (split_ic[i][0] == '$' && split_ic[i][1] != '\0' && split_ic)
			{
				s = find_node(&dtst->env_lst, split_ic[i] + 1);
				if (s != NULL)
					sj = ft_strjoins(sj, s + ft_strlen(split_ic[i]), i - last + 1);
				else
					sj = ft_strjoins(sj, split_ic[i], i - last + 1);
			}
			else
				sj = ft_strjoins(sj, split_ic[i], 1);
			i++;
		}
	}
	return (sj);
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
