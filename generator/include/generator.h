/*
** EPITECH PROJECT, 2020
** generator
** File description:
** sdf
*/

#ifndef GENERATOR_H
#define GENERATOR_H

typedef struct v_t
{
    int x;
    int y;
} v_t;

typedef struct node_t
{
    struct v_t v;
    int visited;
} node_t;

typedef struct grid_t
{
    struct v_t v;
    struct v_t s;
    node_t *tab;
    char *str;
} grid_t;

grid_t new_grid(int x, int y);
void generator(grid_t *grid, node_t **stack);
void destroy(grid_t grid, int ac, char **av);
int my_round(int nb);

#endif