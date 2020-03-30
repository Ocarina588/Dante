/*
** EPITECH PROJECT, 2020
** main
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "solver.h"

const int tab[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

void read_file_2(file_t *file, int fd, struct stat *st, char *str)
{
    if (fd == -1 || stat(str, st) == -1 ||
        st->st_size > __INT32_MAX__ - 2 ||
        !(file->str = malloc(sizeof(char) * (st->st_size + 1))) ||
        !(file->visited = malloc(sizeof(char) * st->st_size)))
        exit (84);

    read(fd, file->str, st->st_size);
    file->str[st->st_size] = '\0';

    for (int i = 0; file->str[i] ; i++) {
        if (file->str[i] == '\n')
            file->y++;
        if (!file->y)
            file->x++;
    }

    if ((file->y + 1) * file->x + file->y != st->st_size)
        exit (84);
    file->y++;
}

file_t read_file(char *str)
{
    int fd = open(str, O_RDONLY);
    struct stat st;
    file_t file = {.x = 0, .y = 0};

    read_file_2(&file, fd, &st, str);
    memset(file.visited, '\0', st.st_size);

    return (file);
}

int get_neighbour(file_t file, int current, int *nb)
{
    int xb;
    int yb;

    for (int i = 0; i < 4 ; i++) {
        xb = (current % (file.x + 1)) + tab[i][0];
        yb = (current / (file.x + 1)) + tab[i][1];

        if (xb < 0 || yb < 0 || xb > file.x - 1 || yb > file.y - 1 ||
            file.str[(yb * (file.x + 1) + xb)] == 'X')
            continue;
        if (!file.visited[(yb * (file.x + 1) + xb)])
            return (yb * (file.x + 1) + xb);
    }

    return (-1);
}

int solver(file_t file, int *stack, int *size)
{
    static int current = 0;
    int tmp = 0;
    int nb = 0;
    int neighbour = -1;

    file.visited[current] = 1;
    neighbour = get_neighbour(file, current, &nb);
    if (neighbour >= 0) {
        tmp = neighbour;
        stack[(*size)++] = current;
        current = tmp;
    } else if (*size)
        current = stack[--(*size)];
    if (file.str + current == file.end) {
        stack[(*size)++] = current;
        return (-1);
    }

    return (*size);
}

int main(int ac, char **av)
{
    file_t file = read_file(av[1]);
    int *stack = malloc(sizeof(char *) * file.x *file.y);
    int size = 0;
    int res = 0;

    file.end = &file.str[(file.x + 1) * file.y - 2];
    if (!file.str || !stack)
        return (84);
    if (file.str[0] == 'X') {
        printf("no solution found");
        return (0);
    }

    while (1) {
        if (!(res = solver(file, stack, &size))) {
            break;
        } else if (res == -1) {
            for (int i = 0; i < size ; i++)
                file.str[stack[i]] = 'o';
            write(1, file.str, (file.x + 1) * file.y - 1);
            return (0);
        }
    }
    printf("no solution found");
    return (0);
}
