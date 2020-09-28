/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 14:18:59 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/09/28 17:34:17 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	myparser(char *line, t_data d)
{
	char	***tmp;
	char	***cmd_grid;
	
	if ((d.nb_cmd = how_many_cmd(line)) == 0)
	{
		printf("Aucune commande valide rentree\n");
		return ;
	}
	else
	{
		cmd_grid = malloc(sizeof(char ***) * (d.nb_cmd + 1));
		cmd_grid[d.nb_cmd] = NULL;
	}

	int i = 0;
	while (cmd_grid[i] != NULL)
	{
		cmd_grid[i] = malloc(sizeof(char **) * 2);
		cmd_grid[i][0] = strdup("salut");
		cmd_grid[i][1] = NULL;
		i++;
	}
	i = 0;
	while (i < d.nb_cmd)
	{
		printf("its working ! %s\n", cmd_grid[i][0]);
		i++;
	}
	/*
	while (line[i] != '\0')
	{
		word = pickword(line, d);
		putword_in_grid(word, cmd_grid, d);
		i += ft_strlen(word);
	}
	*/
}

int main(int argc, char **argv)
{
	t_data	d;
	init_struct(d);
	if (argc == 2)
	{
		myparser(argv[1], d);
	}
	else
		printf("One and only one input command needed.\n");
	return (0);
}
