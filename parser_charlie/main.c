/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 14:18:59 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/09/30 12:54:24 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	ft_strdup_token(t_data *d)
{
	if (d->token == 1)
		d->cmd_grid[d->cmd][d->word] = ft_strdup("$?");
	else if (d->token == 2)
		d->cmd_grid[d->cmd][d->word] = ft_strdup("$word");
	else if (d->token == 3)
	{
		d->cmd_grid[d->cmd][d->word] = ft_strdup("$");
	}
	else if (d->token == 4)
	{
		d->cmd_grid[d->cmd][d->word] = ft_strdup("$");
	}
	else if (d->token == 5)
		d->cmd_grid[d->cmd][d->word] = ft_strdup("|");
	d->word++;
}	


static void add_token(t_data *d)
{
	d->cmd_grid[d->cmd] = expansetab(d->cmd_grid[d->cmd], d->word);
	ft_strdup_token(d);
}

static void	check_token(char *line, t_data *d)
{
	int		i = 0;
	if (line[i] == '$')
	{
		if (line[i + 1] == '?')
			d->token = 1;
		else if (ft_isalpha(line[i + 1]) == 1)
			d->token = 2;
		else if (line[i + 1] == ' ')
			d->token = 3;
		else
			d->token = 4;
	}
	else if (line[i] == '|')
		d->token = 5;
	else
		d->token = -1;
}

static void	parse_line(char *line, t_data d)
{
	int		i = 0;
	int		token = 0;
	while (line[i])
	{
		i += skip_spaces(line + i);
		if (line[i] != '\0')
		{
				check_token(line + i, &d);
				add_token(&d);
		}
		i++;
	}
}

void	myparser(char *line, t_data d)
{
	if ((d.nb_cmd = how_many_cmd(line)) == 0)
	{
		ft_putstr("Il y a une commande invalide.\n"); //si il n'y a rien entre deux ; ;, ou que la commande commence avec un ;. Si elle finit par ;, cést pas grave.
		return ;
	}
	else
	{
		d.cmd_grid = ft_calloc(sizeof(char ***), (d.nb_cmd + 1));
		d.cmd_grid[d.nb_cmd] = NULL;
		d.cmd_grid[0] = ft_calloc(sizeof(char **), (1 + 1));
		d.cmd_grid[0][1] = NULL;
		parse_line(line, d);
	}
	printf("\n[%s]\n", d.cmd_grid[0][0]);
	printf("[%s]\n", d.cmd_grid[0][1]);
}

//D.CMD_GRID[NB_CMD][WORD];

int main(int argc, char **argv)
{
	t_data	d;
	init_struct(d);
	if (argc == 2)
		myparser(argv[1], d);
	else
		printf("One and only one input command needed.\n");
	return (0);
}
