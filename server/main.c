/*
** EPITECH PROJECT, 2019
** server
** File description:
** server
*/

#include "../include/server.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
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
    if (ac != 2)
        return FAILURE;

    for (int i = 0; av[1][i]; i++) {
        if (!isdigit(av[1][i])) {
            server_debug_print(ERROR, "Port is unusable");
            return FAILURE;
        }
    }
    return SUCCESS;
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

    restore_data(server);
    run_server(server);

    save_data(server);
    cleanup(server);
    return 0;
}