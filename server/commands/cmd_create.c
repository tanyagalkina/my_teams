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
            create_new_channel(server, req, fd);
            break;
        case THREAD:
            create_new_thread(server, req, fd);
            break;
        case REPLY_OR_LOGGED:
            break;
    }
    return 0;
}
