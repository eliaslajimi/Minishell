/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 12:50:32 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/10/08 18:25:23 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void		dollar_token(char *line, t_data *d)
{
	int		i;

	i = 1;
	if (line[1] == '?')
	{
		d->token = 1;
		d->index += 2;
	}
	else if (ft_isalpha(line[1]) == 1)
	{
		while (ft_isalpha(line[i]) == 1)
			i++;
		d->tok_word = ft_strndup(line, i);
		d->token = 2;
		d->index += i;
	}
	else if (line[1] == ' ')
	{
		d->token = 3;
		d->index += 2;
	}
}

void		pipe_token(char *line, t_data *d)
{
	d->token = 4;
	d->index += 1;
}

void		semic_token(char *line, t_data *d)
{
	d->token = -1;
	d->word = 0;
	d->cmd++;
	d->index++;
}

void		word_token(char *line, t_data *d)
{
	int		i;

	i = 0;
	while (ft_isalpha(line[i]) == 1)
		i++;
	d->tok_word = ft_strndup(line, i);
	d->token = 5;
	d->index += i;
}

void		redirec_token(char *line, t_data *d)
{
	if (line[0] == '>')
	{
		if (line[1] == '>')
		{
			d->token = 6;
			d->index += 2;
		}
		else
		{
			d->token = 7;
			d->index++;
		}
	}
	else if (line[0] == '<')
	{
		if (line[1] == '<')
		{
			d->token = 8;
			d->index += 2;
		}
		else
		{
			d->token = 9;
			d->index++;
		}
	}
}

void	quote_token(char *line, t_data *d)
{
	if (line[0] == '\'')
	{
		d->token = 10;
		d->index++;
	}
	else if (line[0] == '\"')
	{
		d->token = 10;
		d->index++;
	}
}
