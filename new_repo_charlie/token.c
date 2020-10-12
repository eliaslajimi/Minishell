/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 12:50:32 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/10/12 14:34:28 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		dollar_token(char *line, t_parser *p)
{
	int		i;

	i = 1;
	if (line[1] == '?')
	{
		p->token = 1;
		p->index += 2;
	}
	else if (ft_isalpha(line[1]) == 1)
	{
		while (ft_isalpha(line[i]) == 1)
			i++;
		p->tok_word = ft_strndup(line, i);
		p->token = 2;
		p->index += i;
	}
	else if (line[1] == ' ')
	{
		p->token = 3;
		p->index += 2;
	}
}

void		pipe_token(t_parser *p)
{
	p->token = 4;
	p->index += 1;
}

void		semic_token(t_parser *p)
{
	p->token = -1;
	p->word = 0;
	p->cmd++;
	p->index++;
}

void		word_token(char *line, t_parser *p)
{
	int		i;

	i = 0;
	while (ft_isalpha(line[i]) == 1)
		i++;
	p->tok_word = ft_strndup(line, i);
	p->token = 5;
	p->index += i;
}

void		redirec_token(char *line, t_parser *p)
{
	if (line[0] == '>')
	{
		if (line[1] == '>')
		{
			p->token = 6;
			p->index += 2;
		}
		else
		{
			p->token = 7;
			p->index++;
		}
	}
	else if (line[0] == '<')
	{
		if (line[1] == '<')
		{
			p->token = 8;
			p->index += 2;
		}
		else
		{
			p->token = 9;
			p->index++;
		}
	}
}

void	quote_token(char *line, t_parser *p)
{
	if (line[0] == '\'')
	{
		p->token = 10;
		p->index++;
	}
	else if (line[0] == '\"')
	{
		p->token = 10;
		p->index++;
	}
}
