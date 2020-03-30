/*
** EPITECH PROJECT, 2020
** generator
** File description:
** sdf
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "generator.h"

const v_t tab[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

grid_t new_grid(int x, int y)
{
    grid_t grid;

    grid.v = (v_t){my_round(x), my_round(y)};
    grid.s = (v_t){x, y};
    grid.str = malloc(sizeof(char) * ((x + 1) * y));
    if (!grid.str || (x + 1) * y > __INT32_MAX__ - 2)
        exit(84);
    memset(grid.str, x > 1 && y > 1 ? 'X' : '*', (x + 1) * y);

    for (int i = 0; i < y ; i++)
        grid.str[i * (x + 1) + x] = '\n';
    grid.tab = malloc((sizeof(node_t) * grid.v.y * grid.v.x));
    if (!grid.tab)
        exit(84);
    for (int i = 0; i < grid.v.y * grid.v.x; i++) {
        grid.tab[i].visited = 0;
        grid.tab[i].v = (v_t){i % grid.v.x, i / grid.v.x};
    }

    return (grid);
}

node_t **get_neighbour(node_t *node, grid_t *grid, int *nb)
{
    static node_t *neighbour[4] = {NULL, NULL, NULL, NULL};
    int size = 0;
    v_t v;
    *neighbour = NULL;
    for (int i = 0; i < 4 ; i++) {
        v = (v_t){node->v.x + tab[i].x, node->v.y + tab[i].y};
        if (v.x < 0 || v.x > grid->v.x - 1 || v.y < 0 || v.y > grid->v.y - 1)
            continue;
        if (!grid->tab[grid->v.x * (v.y) + (v.x)].visited)
            neighbour[size++] = &grid->tab[grid->v.x * (v.y) + (v.x)];
    }
    *nb = size;
    return (neighbour);
}

void remove_wall(node_t *a, node_t *b, grid_t *grid)
{
    v_t v = {b->v.x - a->v.x, b->v.y - a->v.y};
    int i = b->v.y;
    int j = b->v.x;
    int h = grid->s.x + 1;

    grid->str[(i * h) * 2 + j * 2] = '*';
    i = a->v.y;
    j = a->v.x;
    grid->str[(i * h) * 2 + j * 2] = '*';
    grid->str[(i * h) * 2 + j * 2 + (h * v.y + v.x)] = '*';
}

void destroy(grid_t grid, int ac, char **av)
{
    int dec = (grid.s.x + 1) * grid.s.y;
    if (!grid.s.x || !grid.s.y)
        return;
    grid.str[0] = '*';
    grid.str[dec - 2] = '*';
    if (!(grid.s.x % 2) && !(grid.s.y % 2))
        grid.str[dec - 3] = '*';
}

void generator(grid_t *grid, node_t **stack)
{
    node_t *current = grid->tab;
    node_t **neighbour;
    node_t *tmp;
    int size = 0;
    int nb = 0;
    int times = grid->v.y * grid->v.x - 1;

    while (times) {
        current->visited = 1;
        neighbour = get_neighbour(current, grid, &nb);
        if (*neighbour) {
            times--;
            tmp = neighbour[rand() % nb];
            stack[size++] = current;
            remove_wall(current, tmp, grid);
            current = tmp;
        } else if (size)
            current = stack[--size];
    }
}