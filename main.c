#include "minishell.h"

int main()
{
	char	*input_command;
	
	write(1, "$> ", 3);
	// lecture de STDIN en boucle, jusqu'a ce qu'on quitte (crl + C == 0))
	while (get_next_line(1, &input_command) > 0) {
		printf("cmd = %s\n", input_command);
		write(1, "$> ", 3);
		free(input_command);
	}
	return (0);
}
