/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 14:20:37 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/09/28 17:14:01 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>

# include "../libft/libft.h"

typedef struct	s_data
{
		int		i;
		int		j;
		int		nb_cmd;
		int		check_between;
}				t_data;


void	init_struct(t_data d);
int		ft_isin(int c, char *set);
int		skip_spaces(char *line);
int		check_in_between(int start, int end, char *line);
int		how_many_cmd(char *line);
int		skip_quote(char *line, char quote, int i);

#endif
