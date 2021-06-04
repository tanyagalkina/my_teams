/*
** EPITECH PROJECT, 2019
** server
** File description:
** server
*/

#include "../include/server.h"
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

static volatile sig_atomic_t done;

void signal_handle(int sig)
{
    server_debug_print(WARNING, "Gracefully stopping services...");
    if (sig != SIGPIPE)
        done = 1;
}

static void pre_loop(void)
{
    server_debug_print(INFO, "started listening ...");
    signal(SIGINT, signal_handle);
    signal(SIGPIPE, signal_handle);
    signal(SIGTERM, signal_handle);
}

int run_server(server_t *server, fd_set current, fd_set ready)
{
    FD_ZERO(&current);
    FD_SET(server->fd, &current);
    pre_loop();

    while (!done) {
        ready = current;
        if (select(FD_SETSIZE, &ready, 0, 0, 0) < 0) {
            if (!done) {
                printf("select error\n");
                return FAILURE;
            }
            else continue;
        }
        for (int fd = 0; fd < FD_SETSIZE; fd++) {
            if (FD_ISSET(fd, &ready)) {
                handle_connection(server, fd, &current);
            }
        }
    }
    return SUCCESS;
}
