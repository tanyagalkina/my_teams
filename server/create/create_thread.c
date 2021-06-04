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
#include <sys/queue.h>
#include <string.h>
#include <stdio.h>

static channel_t *get_channel_by_uuid(team_t *team, const char *ch_uuid)
{
    channel_t *ch;

    TAILQ_FOREACH(ch, &team->channel_head, next) {
        if (strcmp(ch->info->channel_uuid, ch_uuid) == 0) {
            return ch;
        }
    }
    server_debug_print(WARNING, "There is no channel with that uuid");
    return NULL;
}

void create_new_thread(server_t *server, request_t *req, int fd)
{
    printf("why am i here");
    channel_t *ch = NULL;
    const char *team_uuid = req->team_uuid;

    team_t *team = get_team_by_uuid(server, team_uuid);

    if (team == NULL) {
        server_debug_print(ERROR, "TODO implement s/c/create_thread.c");
        return;
    }

    if ((ch = get_channel_by_uuid(team, req->channel_uuid)) == NULL) {
        server_debug_print(ERROR, "TODO implement s/c/create_thread.c");
        return;
    }

    server_event_thread_created(ch->info->channel_uuid, req->thread_uuid, \
req->user_uuid, req->name, req->description);
}
