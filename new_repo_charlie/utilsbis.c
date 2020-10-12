/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsbis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 16:26:34 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/10/12 15:56:37 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_parser *p)
{
	p->i = 0;
	p->j = 0;
	p->cmd = 0;
	p->nb_cmd = 1;
	p->word = 0;
	p->token = 0;
	p->check_between = 0;
}

int		ft_isin(int c, char *set)
{
	while (set && *set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

int		skip_spaces(char *line)
{
	int	i = 0;
	while (ft_isin(line[i], " \t\n\r\v\f"))
	{
		i++;
	}
	return (i);
}

/*
 *On verifie que entre 2 ';' (et avant le premier ';') il y a bien qqe chose,
 *meme si errone. Si pas, on throw une erreur et on arrete.
 *Si apres le dernier ';'il n'y a rien, cest pas grave.
 */

int		check_in_between(int start, int end, char *line)
{
	int i = start + 1;
	while (i < end)
	{
		if (ft_isin(line[i], " \t\r\n\v\f") == 0)
			return (1);
		i++;
	}
	return (0);
}

int		skip_quote(char *line, char quote, int i)
{
	int skip = i + 1;
	while (line[skip] && line[skip] != quote)
		skip++;
	if (line[skip] == quote)
		return (skip - i);
	return (0);
}

int		how_many_cmd(char *line)
{
	int	i = 0;
	int	nb_cmd = 0;
	int	last_semic = 0;

	while (line[i] != '\0')
	{
		if (line[i] == ';')
		{
			if (check_in_between(last_semic, i, line) == 1)
			{
				nb_cmd++;
				last_semic = i;
			}
			else
				return (0);
		}
		else if (line[i] == 34 || line[i] == 39)
		{
			if (skip_quote(line, line[i], i) == 0)
				return (0);
			i += skip_quote(line, line[i], i);
		}
		i++;
	}
	if (check_in_between(last_semic, i, line) == 1)
		nb_cmd++;
	return (nb_cmd);
}

/*
 * realloc avec un espace vide de plus que avant, copie tout le precedent, null-terminated
 */

char		**expansetab(char **tab, int previouslen)
{
	int		i;
	char	**cpy;

	i = 0;
	cpy = ft_calloc(sizeof(char *), (previouslen + 1 + 1));
	cpy[previouslen + 1] = NULL;
	while (i < previouslen)
	{
		cpy[i] = ft_strdup(tab[i]);
		ft_strdel(&tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
	return (cpy);
}

void		free_parser(t_parser *p)
{
	int		i;
	int		j;

	i = 0;
	printf("\nFREEDOOOOOM\n");
	while (p->cmd_grid[i] != NULL)
	{
		j = 0;
		while (p->cmd_grid[i][j] != NULL)
		{
			printf("free grid [%d][%d]\n", i, j);
			free(p->cmd_grid[i][j]);
			p->cmd_grid[i][j] = NULL;
			j++;
		}
		printf("free grid [%d]\n", i);
		free(p->cmd_grid[i]);
		p->cmd_grid[i] = NULL;

		i++;
	}
	printf("free grid\n");
	free(p->cmd_grid);
	p->cmd_grid = NULL;
}
