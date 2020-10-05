/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 14:18:59 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/10/05 15:31:21 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	ft_strdup_token(t_data *d)
{
	if (d->token == 1)
	{
		printf("adding dollar token at	[%d][%d]\n",d->cmd, d->word);
		d->cmd_grid[d->cmd][d->word] = ft_strdup("$?");
	}
	else if (d->token == 2)
	{
		printf("adding dollar token at	[%d][%d]\n",d->cmd, d->word);
		d->cmd_grid[d->cmd][d->word] = ft_strdup(d->tok_word);
		ft_strdel(&d->tok_word);
	}
	else if (d->token == 3)
	{
		printf("adding dollar token at	[%d][%d]\n",d->cmd, d->word);
		d->cmd_grid[d->cmd][d->word] = ft_strdup("$");
	}
	else if (d->token == 4)
	{
		printf("adding pipe token at	[%d][%d]\n", d->cmd, d->word);
		d->cmd_grid[d->cmd][d->word] = ft_strdup("|");
	}
	else if (d->token == 5)
	{
		printf("adding word token at	[%d][%d]\n", d->cmd, d->word);
		d->cmd_grid[d->cmd][d->word] = ft_strdup(d->tok_word);
		ft_strdel(&d->tok_word);
	}
	else if (d->token == 6)
	{
		printf("adding redirec token at	[%d][%d]\n", d->cmd, d->word);
		d->cmd_grid[d->cmd][d->word] = ft_strdup(">>");
	}
	else if (d->token == 7)
	{
		printf("adding redirec token at	[%d][%d]\n", d->cmd, d->word);
		d->cmd_grid[d->cmd][d->word] = ft_strdup(">");
	}
	else if (d->token == 8)
	{
		printf("adding redirec token at	[%d][%d]\n", d->cmd, d->word);
		d->cmd_grid[d->cmd][d->word] = ft_strdup("<<");
	}
	else if (d->token == 9)
	{
		printf("adding redirec token at	[%d][%d]\n", d->cmd, d->word);
		d->cmd_grid[d->cmd][d->word] = ft_strdup("<");
	}
	else if (d->token == -1)
		return ;
	d->word++;
}	

static void	check_token(char *line, t_data *d)
{
	if (*line == '$')
		dollar_token(line, d);
	else if (*line == '|')
		pipe_token(line, d);
	else if (*line == ';')
		semic_token(line, d);
	else if (*line == '>' || *line == '<')
		redirec_token(line, d);
	else if (ft_isalpha(*line) == 1)
		word_token(line, d);
}

static void	parse_line(char *line, t_data d)
{
	d.index = 0;
	while (line[d.index])
	{
		d.index += skip_spaces(line + d.index);
		if (line[d.index] != '\0')
		{
				check_token(line + d.index, &d);
				d.cmd_grid[d.cmd] = expansetab(d.cmd_grid[d.cmd], d.word);
				ft_strdup_token(&d);
		}
	}
}

void	myparser(char *line, t_data d)
{
	if ((d.nb_cmd = how_many_cmd(line)) == 0)
	{
		ft_putstr("Il y a une commande invalide.\n");
		return ;
	}
	else
	{
		if (!(d.cmd_grid = ft_calloc(sizeof(char ***), (d.nb_cmd + 1))))
			return ;
		d.cmd_grid[d.nb_cmd] = NULL;
		if (!(d.cmd_grid[0] = ft_calloc(sizeof(char **), (1 + 1))))
			return ;
		d.cmd_grid[0][1] = NULL;
		parse_line(line, d);
	}
	int i = 0;
	int j = 0;
	write(1, "\n",1);
	while (i < d.nb_cmd)
	{
		j = 0;
		while (d.cmd_grid[i][j] != NULL)
		{
			printf("d.cmd_grid[%d][%d] [%s]\n", i,j, d.cmd_grid[i][j]);
			j++;
		}
		write(1,"\n",1);
		i++;
	}

}

int main(int argc, char **argv)
{
	t_data	d;
	init_struct(&d);

	if (argc == 2)
		myparser(argv[1], d);
	else
		printf("One and only one input command needed.\n");
	return (0);
}
