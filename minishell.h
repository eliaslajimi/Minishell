#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

typedef	struct		s_data
{
	char	*cmd;
	char	**flags;		
	char	*message;
}			t_data;
# endif
