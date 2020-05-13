FLAGS = -Wall -Wextra -Werror

NAME = minishell

SOURCES = main.c\
	echo.c\
	cd.c\
	pwd.c\
	env.c\
	parsing.c\
	absolute_path.c\
	fork_cmd.c\
	export.c\
	unset.c\
	exit.c\
	dollar.c

HEADERS = minishell.h

HEADERS_GCH = minishell.h.gch

LIBFT = libft/libft.a

OBJECT = $(SOURCES:.c=.o)

$(NAME):
	@echo "Compilation..."
	@gcc $(FLAGS) $(SOURCES) $(HEADERS) $(LIBFT)
	@echo "Compilation libft\t\t\033[0;32m[OK]\033[0m"
	@rm -f $(HEADERS_GCH)

all: $(NAME)

clean:
	@rm -f $(OBJECT)
	@echo "Cleaning Objects libft\t\t\033[0;32m[OK]\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "Cleaning libft.a\t\t\033[0;32m[OK]\033[0m"

re: fclean all
