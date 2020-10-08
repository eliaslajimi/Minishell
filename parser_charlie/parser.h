/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 14:20:37 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/10/08 18:49:06 by cmcgahan         ###   ########.fr       */
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
		int		index;
		int		cmd;
		int		nb_cmd;
		int		word;
		int		token;
		char	*tok_word;
		int		check_between;
		char	***cmd_grid;
}				t_data;

typedef struct	s_test
{
		int		wc;
		char	**ans;
}				t_test;


void	init_struct(t_data *d);
int		ft_isin(int c, char *set);
int		skip_spaces(char *line);
int		check_in_between(int start, int end, char *line);
int		how_many_cmd(char *line);
int		skip_quote(char *line, char quote, int i);
char	**expansetab(char **tab, int previouslen);
void	free_parser(t_data *d);
void	dollar_token(char *line, t_data *d);
void	pipe_token(char *line, t_data *d);
void	semic_token(char *line, t_data *d);
void	word_token(char *line, t_data *d);
void	redirec_token(char *line, t_data *d);
void	quote_token(char *line, t_data *d);


#endif
