/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../../include/client.h"

request_t create_info_logged(char *input, client_t *cl)
{
    request_t new_req;
    new_req.type = CT_INFO;
    new_req.context_level = REPLY_OR_LOGGED;
    return new_req;
}

request_t create_info_team(char *input, client_t *cl)
{
    request_t new_req;

    new_req.type = CT_INFO;
    new_req.context_level = TEAM;
    strcpy(new_req.team_uuid, cl->context.team_uuid);
    return new_req;
}

request_t create_info_channel(char *input, client_t *cl)
{
    request_t new_req;

    new_req.type = CT_INFO;
    new_req.context_level = CHANNEL;
    strcpy(new_req.team_uuid, cl->context.team_uuid);
    strcpy(new_req.channel_uuid, cl->context.channel_uuid);
    return new_req;
}

request_t create_info_thread(char *input, client_t *cl)
{
    request_t new_req;

    new_req.type = CT_INFO;
    new_req.context_level = THREAD;
    strcpy(new_req.team_uuid, cl->context.team_uuid);
    strcpy(new_req.channel_uuid, cl->context.channel_uuid);
    strcpy(new_req.thread_uuid, cl->context.thread_uuid);
    return new_req;
}

request_t info_req(char *user_req, char *input, client_t *cl)
{
    switch (cl->context.context_level)
    {
        case (TEAM):
            cl->context.context_level = UNDEFINED;
            return create_info_logged(input, cl);
        case (CHANNEL):
            cl->context.context_level = UNDEFINED;
            return create_info_team(input, cl);
        case (THREAD):
            cl->context.context_level = UNDEFINED;
            return create_info_channel(input, cl);
        case (REPLY_OR_LOGGED):
            cl->context.context_level = UNDEFINED;
            return create_info_thread(input, cl);
        default:
            return bad_request(NO_USE);
    }
}
