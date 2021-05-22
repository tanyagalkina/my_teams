/*
** EPITECH PROJECT, 2019
** handle_connection
** File description:
** handle_connection
*/

#include "../include/server.h"
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>
#include <unistd.h>
#include <stdio.h>

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

    //@todo add user here
    /*user_t *user = create_user(client_fd);*/
    /*if (user == NULL)*/
        /*return FAILURE;*/

    /*server->users = server_add_user(server, user);*/
    return SUCCESS;
}

static char *get_message_from_client(server_t *server, int fd)
{
    //@todo get the struct from the user + parse it or something idk
    int r;
    char buffer[100];

    memset(buffer, 0, 100);

    if ((r = read(fd, &buffer, 100)) == -1)
        return NULL;

    return strdup(buffer);
    return NULL;
}

/* this is just a template to show easy use of uuid and the TAILQ stuff */
int add_team(server_t *server, const char *name)
{
    uuid_t binuuid;
    team_t *new_team = NULL;

    uuid_generate_random(binuuid);
    if ((new_team = (team_t *)malloc(sizeof(team_t))) == NULL)
        return FAILURE;

    strcpy(new_team->name, name);
    uuid_unparse(binuuid, new_team->uuid);

    TAILQ_INSERT_TAIL(&server->admin->team_head, new_team, next);
    return SUCCESS;
}

void handle_connection(server_t *server, int fd, fd_set *current)
{
    char *message = NULL;
    char **sp_message = NULL;

    if (fd == server->fd) {
        if (accept_new_connection(server, current) == FAILURE)
            return;
        server_debug_print(INFO, "got a new connection");
        FD_SET(fd, current);
        return;
    }
    if ((message = get_message_from_client(server, fd)) == NULL)
        return;
    if ((sp_message = split_string(message)) == NULL)
        return;

    team_t *tmp;
    if (strcmp(sp_message[0], "ls") == 0) {
        TAILQ_FOREACH(tmp, &server->admin->team_head, next) {
            printf("uuid: %s, name: %s\n", tmp->uuid, tmp->name);
        }
    } else {
        add_team(server, sp_message[0]);
    }

    free_2d(sp_message);
    free(message);
}
