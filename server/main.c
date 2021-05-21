/*
** EPITECH PROJECT, 2019
** server
** File description:
** server
*/

#include "../include/server.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

void server_debug_print(debug_state_t state, const char *msg)
{
    printf("%s", debug_state_print[state]);
    printf("[SERVER] " COLOR_RESET);
    printf("%s\n", msg);
    fflush(stdout);
}

int errorhandling(int ac, char **av)
{
    char *end;
    long val;

    if (ac != 2)
        return FAILURE;

    errno = 0;

    val = strtol(av[1], &end, 10);

    if (errno == ERANGE)
        return FAILURE;

    return SUCCESS;
}

int add_team(server_t *server)
{
    team_t *new_team = (team_t *)malloc(sizeof(team_t));

    TAILQ_INSERT_TAIL(&server->admin->team_head, new_team, next);
    return 0;
}

int main(int ac, char **av)
{
    server_t *server = NULL;

    if (errorhandling(ac, av) != SUCCESS)
        return 84;

    if ((server = init_server(atoi(av[1]))) == NULL)
        return 84;
    if ((server = setup_server(server)) == NULL)
        return 84;

    run_server(server);
    cleanup(server);
    return 0;
}
