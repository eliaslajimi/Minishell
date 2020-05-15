#include "minishell.h"

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

int commandquote(t_data *dtst)
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
		if (splitcmd[i] == 96)	
			if (dtst->quote_type == 0 || dtst->quote_type == 96)
			{
				dtst->quote_type = 96;
				quote_rec++;
			}
		if (splitcmd[i] == 39)
			if (dtst->quote_type == 0 || dtst->quote_type == 39)
			{
				dtst->quote_type = 39;
				quote_rec++;
			}
		if (splitcmd[i] == 34)
			if (dtst->quote_type == 0 || dtst->quote_type == 34)
			{
				dtst->quote_type = 34;
				quote_rec++;
			}
		++i;
	}
	if (quote_rec%2)
	{
		dtst->split_cmd[0] = ft_strtrim(dtst->split_cmd[0], &dtst->quote_type);
		inputquote(dtst);
	}
	return (0);
}

char *trim_quote(t_data *dtst, char *inputcmd)
{
	int i;
	int j;
	int counter;
	char *newinputcmd = NULL;
	
	i = 0;
	j = 0;
	counter = 0;

	newinputcmd = malloc(sizeof(inputcmd));
	ft_bzero(newinputcmd, ft_strlen(newinputcmd));
	while(inputcmd[i])
	{
		if (inputcmd[i] != dtst->quote_type || counter > 0)
		{
			//newinputcmd[j++] = inputcmd[i];
			//newinputcmd[j] = 0;
			inputcmd[j++] = inputcmd[i];
			counter++;
		}
		i++;
	}
	inputcmd[j] = inputcmd[i];
	return (inputcmd);
}


char*	removequotes(char **newcommand)
{

	int	i;
	int	j;
	char	quote;
	char	**inputcmd = NULL;

	*inputcmd = ft_strdup(*newcommand);
	i = 0;
	j = 0;

	
	while(*inputcmd[i])
	{
		if (*inputcmd[i] != 96 && *inputcmd[i] != 39 && *inputcmd[i] != 34)
		{
			*inputcmd[j] = *inputcmd[i];
		}
		else
		{
			write(1, "\n", 1);
			write(1, &(*inputcmd[i]), 1);
			quote = *inputcmd[i++];
			while (*inputcmd[i] != quote)
				*inputcmd[j++] = *inputcmd[i++];
		}
		i++;
		j++;
		write(1, "\n", 1);
		write(1, &(*inputcmd[i]), 1);
	}
	*inputcmd[++j] = 0;
	return (*inputcmd);
}
