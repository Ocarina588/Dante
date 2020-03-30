##
## EPITECH PROJECT, 2019
## make file
## File description:
## sdf
##

SRC	=	src/main.c


OBJ     =       $(SRC:.c=.o)

NAME    =       solver

CFLAGS	=	-Iinclude

all:    $(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:     fclean all

valgrind:
	gcc -o $(NAME) $(SRC) $(CFLAGS) -g -Wextra -Wall