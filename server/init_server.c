/*
** EPITECH PROJECT, 2019
** server
** File description:
** server
*/

#include "../include/server.h"
#include <stdio.h>
#include <stdlib.h>

static int create_socket(server_t **server, int port)
{
    server_debug_print(INFO, "creating socket ...");
    if (((*server)->fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket()");
        return FAILURE;
    }
    (*server)->addr.sin_family = AF_INET;
    (*server)->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    (*server)->addr.sin_port = htons(port);
    return SUCCESS;
}

static int setup_socket_opt(server_t **server)
{
    int opt = SO_REUSEADDR | SO_REUSEPORT;
    int level = SOL_SOCKET;

    if (setsockopt((*server)->fd, level, opt, &(int) {1}, sizeof(int)) < 0) {
        perror("setsockopt() failed");
        return FAILURE;
    }
    return SUCCESS;
}

static int bind_server(server_t **server)
{
    int size = sizeof((*server)->addr);

    server_debug_print(INFO, "binding server ...");
    if (bind((*server)->fd, (struct sockaddr *)&(*server)->addr, size) < 0) {
        perror("bind()");
        return FAILURE;
    }
    return SUCCESS;
}

server_t *init_server(int port)
{
    server_t *server = NULL;
    server_debug_print(INFO, "starting server ...");

    if ((server = (server_t *)malloc(sizeof(server_t))) == NULL)
        return NULL;

    server->port = port;
    server->admin = NULL;
    if (create_socket(&server, port) == FAILURE)
        return NULL;
    if (setup_socket_opt(&server) == FAILURE)
        return NULL;
    if (bind_server(&server) == FAILURE)
        return NULL;
    if (listen(server->fd, SERVER_BACKLOG) < 0) {
        perror("listen()");
        return NULL;
    }
    return server;
}
