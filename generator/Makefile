##
## EPITECH PROJECT, 2019
## make file
## File description:
## sdf
##

SRC	=	src/main.c	\
		src/generator.c

OBJ     =       $(SRC:.c=.o)

NAME    =       generator

CFLAGS	=	-Iinclude

LDFLAGS	=	-lm

all:    $(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:     fclean all

valgrind:
	gcc -o $(NAME) $(SRC) $(CFLAGS) $(LDFLAGS) -g -Wextra -Wall