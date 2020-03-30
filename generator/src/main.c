/*
** EPITECH PROJECT, 2020
** main
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "generator.h"

int my_round(int nb)
{
    return (nb % 2 ? nb / 2 + 1 : nb / 2);
}

int check_good_number(int ac, char **av)
{
    if (ac != 3 || strlen(av[1]) > 5 || strlen(av[2]) > 5
        || atoi(av[1]) > 40000 || atoi(av[2]) > 40000)
        return (1);
    return (0);
}

int main(int ac, char **av)
{
    grid_t grid;
    node_t **stack;

    srand(time(NULL));
    if (check_good_number(ac, av))
        return (84);
    grid = new_grid(atoi(av[1]), atoi(av[2]));
    if (!grid.str || !(stack = malloc(sizeof(node_t) * (grid.v.x * grid.v.y))))
        return (84);

    destroy(grid, ac, av);
    if (atoi(av[1]) && atoi(av[2])) {
        if (atoi(av[1]) > 1 && atoi(av[2]) > 1)
            generator(&grid, stack);
        destroy(grid, ac, av);
        write(1, grid.str, (atoi(av[1]) + 1) * atoi(av[2]) - 1);
    }
    return (0);
}
