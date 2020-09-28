/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 14:18:59 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/09/28 17:44:34 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	myparser(char *line, t_data d)
{
	char	***tmp;
	char	***cmd_grid;

/*
 * Pas besoin de realloc le ***cmd_grid vu quil est directement init a la bonne taille
 */	
	if ((d.nb_cmd = how_many_cmd(line)) == 0)
	{
		printf("Il y a une commande invalide.\n"); //si il n'y a rien entre deux ; ;, ou que la commande commence avec un ;. Si elle finit par ;, cést pas grave.
		return ;
	}
	else
	{
		cmd_grid = malloc(sizeof(char ***) * (d.nb_cmd + 1));
		cmd_grid[d.nb_cmd] = NULL;
	}
/*
 * TO DELETE, juste pour voir si ca marche comme voulu.
 */
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
	//
	//
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
