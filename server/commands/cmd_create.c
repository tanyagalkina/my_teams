/*
** EPITECH PROJECT, 2020
** commands
** File description:
** cmd_create
*/

#include "../../include/server.h"
#include "../../include/commons.h"
#include "../../libs/myteams/logging_server.h"
#include "../../include/commands.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/queue.h>

int cmd_create(server_t *server, request_t *req, int fd)
{
    switch (req->context_level) {
        case UNDEFINED:
            break;
        case TEAM:
            create_new_team(server, req, fd);
            break;
        case CHANNEL:
            break;
        case THREAD:
            break;
        case REPLY_OR_LOGGED:
            break;
    }
    printf("Why am I here?\n");
    printf("the context level was %d", req->context_level);
    printf("the name was %s\n", req->name);
    printf("description was %s\n", req->description);
    return 0;
}
