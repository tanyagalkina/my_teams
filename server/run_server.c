/*
** EPITECH PROJECT, 2019
** server
** File description:
** server
*/

#include "../include/server.h"
#include <stdio.h>
#include <signal.h>

static volatile sig_atomic_t done;

void signal_handle(int sig_num)
{
    server_debug_print(WARNING, "Ctrl + C stopping ...");
    done = 1;
}

int run_server(server_t *server)
{
    server_debug_print(INFO, "started listening ...");
    fd_set current, ready;
    FD_ZERO(&current);
    FD_SET(server->fd, &current);
    signal(SIGINT, signal_handle);

    while (!done) {
        ready = current;
        if (select(FD_SETSIZE, &ready, 0, 0, 0) < 0) {
            perror("select()");
            return FAILURE;
        }
        for (int fd = 0; fd < FD_SETSIZE; fd++) {
            if (FD_ISSET(fd, &ready)) {
                handle_connection(server, fd, &current);
            }
        }
    }
    return SUCCESS;
}
