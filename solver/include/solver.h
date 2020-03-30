/*
** EPITECH PROJECT, 2020
** solver
** File description:
** sdf
*/

#ifndef SOLVER_H
#define SOLVER_H

typedef struct file_t
{
    char *str;
    char *visited;
    int y;
    int x;
    int res;
    char *end;
} file_t;


int p(int nb);
file_t read_file(char *str);


#endif
