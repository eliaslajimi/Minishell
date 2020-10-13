/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <cmcgahan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 14:43:54 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/10/13 13:52:38 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_strdup_token(t_parser *p)
{
	if (p->token == 1)
	{
		printf("adding dollar token		at [%d][%d]\n",p->cmd, p->word);
		p->cmd_grid[p->cmd][p->word] = ft_strdup("$?");
	}
	else if (p->token == 2)
	{
		printf("adding dollar token		at [%d][%d]\n",p->cmd, p->word);
		p->cmd_grid[p->cmd][p->word] = ft_strdup(p->tok_word);
		ft_strdel(&p->tok_word);
	}
	else if (p->token == 3)
	{
		printf("adding dollar token		at [%d][%d]\n",p->cmd, p->word);
		p->cmd_grid[p->cmd][p->word] = ft_strdup("$");
	}
	else if (p->token == 4)
	{
		printf("adding pipe token		at [%d][%d]\n", p->cmd, p->word);
		p->cmd_grid[p->cmd][p->word] = ft_strdup("|");
	}
	else if (p->token == 5)
	{
		printf("adding word token		at [%d][%d]\n", p->cmd, p->word);
		p->cmd_grid[p->cmd][p->word] = ft_strdup(p->tok_word);
		ft_strdel(&p->tok_word);
	}
	else if (p->token == 6)
	{
		printf("adding redirec token		at	[%d][%d]\n", p->cmd, p->word);
		p->cmd_grid[p->cmd][p->word] = ft_strdup(">>");
	}
	else if (p->token == 7)
	{
		printf("adding redirec token		at [%d][%d]\n", p->cmd, p->word);
		p->cmd_grid[p->cmd][p->word] = ft_strdup(">");
	}
	else if (p->token == 8)
	{
		printf("adding redirec token		at [%d][%d]\n", p->cmd, p->word);
		p->cmd_grid[p->cmd][p->word] = ft_strdup("<<");
	}
	else if (p->token == 9)
	{
		printf("adding redirec token		at [%d][%d]\n", p->cmd, p->word);
		p->cmd_grid[p->cmd][p->word] = ft_strdup("<");
	}
	else if (p->token == 10)
	{
		printf("adding quoted word token		at [%d][%d]\n", p->cmd, p->word);
		p->cmd_grid[p->cmd][p->word] = ft_strdup(p->tok_word);
		ft_strdel(&p->tok_word);
	}
	else if (p->token == -1)
		return ;
	p->word++;
}

static int	check_token(char *line, t_parser *p)
{
	if (*line == '$')
		dollar_token(line, p);
	else if (*line == '|')
		pipe_token(p);
	else if (*line == ';')
	{
		printf("semic reached !\n");
		semic_token(p);
	}
	else if (*line == '>' || *line == '<')
		redirec_token(line, p);
	else if (ft_isalpha(*line) == 1)
		word_token(line, p);
	else if (*line == 34 || *line == 39) //quotes
		quote_token(line, p);
//	else if (*line == 46 || 47) //dots and slashes
//		dslash_token(line, p);
	else
		p->token = -1;
	return (p->token);
}

static void	parse_line(char *line, t_parser *p)
{
	p->index = 0;
	while (line[p->index])
	{
		p->index += skip_spaces(line + p->index);
		if (line[p->index] != '\0')
		{
				if (check_token(line + p->index, p) == -1) //A TRAITER : si ca renvoie -1, c'est par ex pour problemes de matching quotes et on quitte tout
					return ;
				p->cmd_grid[p->cmd] = expansetab(p->cmd_grid[p->cmd], p->word);
				ft_strdup_token(p);
		}
	}
}

void	myparser(char *line, t_parser *p)
{
	if ((p->nb_cmd = how_many_cmd(line)) == 0)
	{
		ft_putstr("Il y a une commande invalide.\n");
		return ;
	}
	else
	{
		if (!(p->cmd_grid = ft_calloc(sizeof(char ***), (p->nb_cmd + 1))))
			return ;
		p->cmd_grid[p->nb_cmd] = NULL;
		if (!(p->cmd_grid[0] = ft_calloc(sizeof(char **), (1 + 1))))
			return ;
		p->cmd_grid[0][1] = NULL;
		parse_line(line, p);
	}
	int i = 0;
	int j = 0;
	write(1, "\n",1);
	while (i < p->nb_cmd)
	{
		j = 0;
		while (p->cmd_grid[i][j] != NULL)
		{
			printf("p->cmd_grid[%d][%d] [%s]\n", i,j, p->cmd_grid[i][j]);
			j++;
		}
		write(1,"\n",1);
		i++;
	}
}
