/*
** EPITECH PROJECT, 2020
** commands
** File description:
** cmd_create
*/

#include "../../include/server.h"
#include "../../include/commons.h"
#include "../../libs/myteams/logging_server.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/queue.h>

static int create_new_team(server_t *server, request_t *req, int fd)
{
    team_t *team;
    uuid_t binuuid;
    const char *user_uuid = get_user_by_fd(server, fd)->info->user_uuid;

    if ((team = malloc(sizeof(team_t))) == NULL)
        return FAILURE;
    if ((team->info = malloc(sizeof(team_info_t))) == NULL)
        return FAILURE;

    TAILQ_INIT(&team->channel_head);
    uuid_generate_random(binuuid);

    strcpy(team->info->team_name, req->name);
    strcpy(team->info->team_description, req->description);
    uuid_unparse(binuuid, team->info->team_uuid);

    server_event_team_created(team->info->team_uuid, req->name, user_uuid);
    TAILQ_INSERT_TAIL(&server->admin->team_head, team, next);
    return SUCCESS;
}

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
