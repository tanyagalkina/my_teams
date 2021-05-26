/*
** EPITECH PROJECT, 2019
** handle_connection
** File description:
** handle_connection
*/

#include "../include/commands.h"
#include "../include/commons.h"
#include "../include/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>
#include <unistd.h>

static int accept_new_connection(server_t *server, fd_set *current)
{
    int client_fd;
    struct sockaddr_in client_addr;
    int addr_size = sizeof(struct sockaddr_in);

    client_fd = accept(server->fd, (struct sockaddr *)&client_addr, \
(socklen_t *)&addr_size);
    server_debug_print(INFO, "accepted new connection");

    if (client_fd == -1)
        return FAILURE;

    FD_SET(client_fd, current);
    return SUCCESS;
}

static int get_request_from_client(server_t *server, int fd)
{
    int r;
    request_t *req = NULL;
    char buffer[REQUEST_SIZE];

    memset(buffer, 0, REQUEST_SIZE);
    if ((r = read(fd, &buffer, REQUEST_SIZE)) == -1)
        return SUCCESS;

    if (r == 0) {
        server_debug_print(INFO, "a client disconnected");
        get_user_by_fd(server, fd)->info->user_status = LOGGED_OUT;
        return FAILURE;
    }
    req = (void *)buffer;

    for (int i = 0; i < COMMANDS; i++) {
        if (cmd_table[i].cmd_type == req->type)
            cmd_table[i].f(server, req, fd);
    }
    return (0);
}

/* this is just a template to show easy use of uuid and the TAILQ stuff */
int add_team(server_t *server, const char *name)
{
    uuid_t binuuid;
    team_t *new_team = NULL;

    uuid_generate_random(binuuid);
    if ((new_team = (team_t *)malloc(sizeof(team_t))) == NULL)
        return FAILURE;

    strcpy(new_team->info->team_name, name);
    uuid_unparse(binuuid, new_team->info->team_uuid);

    TAILQ_INSERT_TAIL(&server->admin->team_head, new_team, next);
    return SUCCESS;
}

void handle_connection(server_t *server, int fd, fd_set *current)
{
    if (fd == server->fd) {
        if (accept_new_connection(server, current) == FAILURE)
            return;
        server_debug_print(INFO, "got a new connection");
        FD_SET(fd, current);
        return;
    }
    if (get_request_from_client(server, fd) == FAILURE) {
        close(fd);
        FD_CLR(fd, current);
    }
}