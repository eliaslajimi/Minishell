#include "minishell.h"

//Function will reformated
int	formatdata(t_data *dtst, char *inputcmd)
{
	int i;

	i = 0;
	while (dtst->split_cmd[i])
	{

//Clean and format data
//=============================================
		dtst->split_cmd[i] = ft_strtrim(dtst->split_cmd[i], " ");
		commandquote(dtst);
		inputcmd = ft_strtrim(dtst->split_cmd[i],
		&dtst->quote_type);
		dtst->quoteresult = ft_strtrim(dtst->quoteresult,
		&dtst->quote_type);
		inputcmd = ft_strjoin(inputcmd, dtst->quoteresult);
//=============================================

		if (command_parsing(inputcmd, dtst) != -1)
		{
			free(inputcmd);
			//check_error(dtst);
			cmdfunc(dtst);
		}
		i++;
		if (dtst->split_cmd[i] == NULL)
		{
			//ft_free_tab(dtst->split_cmd);
			minishell_wrapper(dtst);
		}
	}
	return (0);
}
