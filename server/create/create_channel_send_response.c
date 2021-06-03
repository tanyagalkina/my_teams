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

void channel_send_response(team_t *team, channel_t *ch, int fd)
{
    response_t r;
    r.request_type = CT_CREATE;
    r.level = CHANNEL;
    strcpy(r.team_uuid, team->info->team_uuid);
    strcpy(r.channel_uuid, ch->info->channel_uuid);
    strcpy(r.name, ch->info->channel_name);
    strcpy(r.description, ch->info->channel_description);
    send(fd, &r, RESPONSE_SIZE, 0);
}

/*void channel_send_to_all(server_t *server, team_t *team, channel_t *ch)
{
    user_t *user;
    user_fds_t *fds;
    response_t r;

    TAILQ_FOREACH(user, &server->admin->user_head, next) {
        if (!is_user_in_team(user, ch->info->channel_uuid))
            continue;
        r.request_type = ET_CHANNEL_CREAT;
        strcpy(r.team_uuid, team->info->team_uuid);
        strcpy(r.channel_uuid, ch->info->channel_uuid);
        strcpy(r.name, ch->info->channel_name);
        strcpy(r.description, ch->info->channel_description);
        TAILQ_FOREACH(fds, &user->user_fds_head, next) {
            send(fds->fd, &r, RESPONSE_SIZE, 0);
        }
    }
}*/
