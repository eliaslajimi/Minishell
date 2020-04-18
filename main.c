#include "minishell.h"

void	put_command(t_data dtst)//TO BE DELETED
{
	int i;
	
	i = -1;
	printf("\n===================\n");
	printf("this is your cmd: %s\n", dtst.cmd);	
	while(dtst.flags[++i])
		printf("this is your flag n%d: %s\n", i+1, dtst.flags[i]);
	printf("this is your message: %s\n", dtst.message);
	printf("\n===================\n");
}

char 	*retrieve_from_flags(char **flags)
{
	int k;
	char *str;

	k	= -1;
	str 	= NULL;
	while (flags[++k])
		if (flags[k][0] != '-')//if k is inferior to the length of the **ptr, wrong input
		{
			str = ft_strdup(flags[k]);
			free(flags[k]);
			flags[k] = NULL;
			return (str);
		}
	return (NULL);

}

int	command_parsing(char *inputcmd, t_data *dtst)
{
	int i;	
	int k;

	k = -1;
	i = 0;
	while(!ft_isspace(inputcmd[i++]));
	dtst->cmd = ft_strndup(inputcmd, i);//allocation need to be freed
	dtst->flags = ft_split(inputcmd + i, ' ');//allocation need to be freed
	dtst->message = retrieve_from_flags(dtst->flags);//allocation need to be freed
	put_command(*dtst);//solely for debugging purposes
	return (0);
}

//BUG: segfault with repeted "enter"
int	main()
{
	char	*inputcmd;
	t_data	dtst;

	dtst.cmd = "";
	write(1, "$> ", 3);
	// lecture de STDIN en boucle, jusqu'a ce qu'on quitte (crl + C == 0))
	while (get_next_line(1, &inputcmd) > 0)
	{
		write(1, "$> ", 3);
		if (inputcmd)
			command_parsing(inputcmd, &dtst);
		free(inputcmd);
	}
	return (0);
}
