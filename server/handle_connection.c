/*
** EPITECH PROJECT, 2019
** handle_connection
** File description:
** handle_connection
*/

#include "../include/server.h"
#include "../include/commons.h"
#include "../include/commands.h"
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

static char *get_request_from_client(server_t *server, int fd)
{
    int r;
    request_t *req = NULL;
    char buffer[REQUEST_SIZE];

    memset(buffer, 0, REQUEST_SIZE);
    if ((r = read(fd, &buffer, REQUEST_SIZE)) == -1)
        return NULL;

    if (r == 0) {
        //@todo remove the clients from the list and close the fd
        printf("the client is disconnected\n");
        return NULL;
    }
    req = (void *)buffer;

    for (int i = 0; i < COMMANDS; i++) {
        if (cmd_table[i].cmd_type == req->type)
            cmd_table[i].f(server, req, fd);
    }


    /*printf("type:#%d#\n", req->type);*/
    /*printf("uuid #%s#\n", req->uuid);*/
    /*printf("the massage in request was #%s#\n", req->message);*/
    /*printf("the description was #%s#\n", req->description);*/
    /*printf("the name was #%s#\n", req->name);*/
    ///this was checking the client loop I will leave it for now
    if (req->type == SEND) {
        //send(fd - 1, &req->message, MAX_BODY_LENGTH, 0);
        printf("type was actually send\n");
    }
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

    strcpy(new_team->info->team_name, name);
    uuid_unparse(binuuid, new_team->info->team_uuid);

    TAILQ_INSERT_TAIL(&server->admin->team_head, new_team, next);
    return SUCCESS;
}

///generation example
response_t generate_response(int fd)
{
    response_t response;
    response.request_type = USERS; ///type of prev request which was answered
    response.status_code = STATUS_OK; /// 200 OK for example)
    response.extern_body_size = 2; /// the size of data list following (if the case))
    response.extern_body_type = USER_TYPE;
    strcpy(response.message, "Very good!"); /// comment message

    return response;
}

void handle_connection(server_t *server, int fd, fd_set *current)
{
    char *message = NULL;
    char **sp_message = NULL;
    response_t response;

    if (fd == server->fd) {
        if (accept_new_connection(server, current) == FAILURE)
            return;
        server_debug_print(INFO, "got a new connection");
        FD_SET(fd, current);
        return;
    }
    if ((message = get_request_from_client(server, fd)) == NULL)
        return;
    if ((sp_message = split_string(message)) == NULL)
        return;

    response = generate_response(fd); ///normally based on the request)))
    send(fd, &response, RESPONSE_SIZE, 0);
    //if ((sp_message = split_string(message)) == NULL)
    //    return;
    /*team_t *tmp;
    if (strcmp(sp_message[0], "ls") == 0) {
        TAILQ_FOREACH(tmp, &server->admin->team_head, next) {
            printf("uuid: %s, name: %s\n", tmp->uuid, tmp->name);
        }
    } else {
        add_team(server, sp_message[0]);
    }

    free_2d(sp_message);
    free(message);*/
}
