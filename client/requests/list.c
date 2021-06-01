/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../../include/client.h"

static request_t list_replies(client_t *cl)
{
    request_t new_req;

    new_req.type = CT_CREATE;
    new_req.context_level = REPLY_OR_LOGGED;
    strcpy(new_req.team_uuid, cl->context.team_uuid);
    strcpy(new_req.channel_uuid, cl->context.channel_uuid);
    strcpy(new_req.thread_uuid, cl->context.thread_uuid);
    return new_req;
}

static request_t list_threads(client_t *cl)
{
    request_t new_req;

    new_req.type = CT_CREATE;
    new_req.context_level = THREAD;
    strcpy(new_req.team_uuid, cl->context.team_uuid);
    strcpy(new_req.channel_uuid, cl->context.channel_uuid);
    return new_req;
}

static request_t list_channels(client_t *cl)
{
    request_t new_req;

    new_req.type = CT_CREATE;
    new_req.context_level = CHANNEL;
    strcpy(new_req.team_uuid, cl->context.team_uuid);
    return new_req;
}

static request_t list_teams(void)
{
    request_t new_req;

    new_req.type = CT_LIST;
    new_req.context_level = TEAM;
    return new_req;
}

request_t list_req(char *user_req, char *args, client_t *cl)
{
    (void)args;
    (void)user_req;

    switch (cl->context.context_level)
    {
        case (TEAM):
            return list_teams();
        case (CHANNEL):
            cl->context.context_level = TEAM;
            return list_channels(cl);
        case (THREAD):
            cl->context.context_level = TEAM;
            return list_threads(cl);
        case (REPLY_OR_LOGGED):
            cl->context.context_level = TEAM;
            return list_replies(cl);
        default:
            return bad_request(NO_USE);
    }
}