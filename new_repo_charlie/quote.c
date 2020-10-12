#include "minishell.h"

char	*removequote(char *inputcmd)
{
	int	n;
	int	j;
	char	quote;

	n = 0;
	j = 0;
	quote = 0;
	while(inputcmd[n])
	{
		if (inputcmd[n] != 96 && inputcmd[n]
		!= 39 && inputcmd[n] != 34)
		{
			inputcmd[j] = inputcmd[n];
			j++;
		}
		else
		{
			quote = inputcmd[n++];
			while (inputcmd[n] && inputcmd[n] != quote)
				inputcmd[j++] = inputcmd[n++];
		}
		n++;
	}
	inputcmd[j] = 0;
	return (inputcmd);
}

int	inputquote(t_data *dtst)
{
	char *temp;

	temp = NULL;
	write(1, "quote> ", ft_strlen("quote> "));
	get_next_line(1, &temp);
 	dtst->quoteresult = ft_strjoin(dtst->quoteresult, temp);
	if (ft_strchr(temp, dtst->quote_type))
		return (0);
	dtst->quoteresult = ft_strjoin(dtst->quoteresult, "\n");
	inputquote(dtst);
	return (0);
}

int	isquote(char c)
{
	return (c == 96 || c == 39 || c == 34);
}

int	conditioncheck(char splitcmd, t_data *dtst)
{
	if (splitcmd == 96)	
		if (dtst->quote_type == 0 || dtst->quote_type == 96)
		{
			dtst->quote_type = 96;
			return (1);
		}
	if (splitcmd == 39)
		if (dtst->quote_type == 0 || dtst->quote_type == 39)
		{
			dtst->quote_type = 39;
			return (1);
		}
	if (splitcmd == 34)
		if (dtst->quote_type == 0 || dtst->quote_type == 34)
		{
			dtst->quote_type = 34;
			return (1);
		}
	return (0);
}

int	commandquote(t_data *dtst)
{
	int i;
	char *splitcmd;
	int quote_rec; 

	quote_rec = 0;
	splitcmd = dtst->split_cmd[0];
	dtst->quote_type = 0;
	dtst->quoteresult = NULL;
	i = 0;

	while(splitcmd[i])	
	{
		if (conditioncheck(splitcmd[i], dtst))
			quote_rec++;
		++i;
	}
	if (quote_rec%2)
	{
		dtst->split_cmd[0] = ft_strtrim(dtst->split_cmd[0],
		&dtst->quote_type);
		inputquote(dtst);
	}
	return (0);
}
