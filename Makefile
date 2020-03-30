##
## EPITECH PROJECT, 2019
## make file
## File description:
## sdf
##

all:
	make -C solver/
	make -C generator/
clean:
	make clean -C solver/
	make clean -C generator/
fclean: clean
	make fclean -C solver/
	make fclean -C generator/
re:     fclean all