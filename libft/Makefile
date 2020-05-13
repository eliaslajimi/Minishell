# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/29 14:54:07 by cmcgahan          #+#    #+#              #
#    Updated: 2020/03/02 13:30:06 by cmcgahan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FlAGS = -Wall -Wextra -Werror

NAME = libft.a

SOURCES = ft_putchar.c ft_putstr.c\
		  ft_memset.c ft_bzero.c\
		  ft_memcpy.c ft_memccpy.c\
		  ft_memmove.c ft_memchr.c\
		  ft_memcmp.c ft_strlen.c\
		  ft_isalpha.c ft_isdigit.c\
		  ft_isalnum.c ft_isascii.c\
		  ft_isprint.c ft_toupper.c\
		  ft_tolower.c ft_strchr.c\
		  ft_strrchr.c ft_strncmp.c\
		  ft_strlcpy.c ft_strlcat.c\
		  ft_strnstr.c ft_atoi.c\
		  ft_calloc.c ft_strdup.c\
		  ft_substr.c ft_strjoin.c\
		  ft_strtrim.c ft_split.c\
		  ft_itoa.c ft_strmapi.c\
		  ft_putchar_fd.c ft_putstr_fd.c\
		  ft_putendl_fd.c ft_putnbr_fd.c\
		  ft_putchar.c ft_putstr.c\
		  ft_putnbr.c\
		  ft_intheset.c ft_strdel.c\
		  ft_utoa_base.c\
		  ft_lstnew.c ft_lstadd_front.c\
		  ft_lstsize.c ft_lstlast.c\
		  ft_lstadd_back.c ft_lstiter.c\
		  ft_lstdelone.c ft_lstclear.c\
		  ft_lstmap.c\
		  get_next_line.c\
		  ft_free_tab.c ft_strcmp.c\
		  ft_strrcmp.c\
		  ft_isspace.c ft_lstprint.c
	
HEADERS = libft.h

HEADERS_GCH = libft.h.gch

OBJECT = $(SOURCES:.c=.o)

$(NAME):
	@echo "Compilation..."
	@gcc $(FLAGS) -c $(SOURCES) $(HEADERS)
	@ar rc $(NAME) $(OBJECT)
	@ranlib $(NAME)
	@echo "Compilation libft\t\t\033[0;32m[OK]\033[0m"

all: $(NAME)

clean:
	@rm -f $(OBJECT)
	@rm -f $(HEADERS_GCH)
	@echo "Cleaning Objects libft\t\t\033[0;32m[OK]\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "Cleaning libft.a\t\t\033[0;32m[OK]\033[0m"

re: fclean all
