/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../../include/client.h"

static request_t create_reply(char *input, client_t *cl)
{
    char **req_args;
    request_t new_req;

    if (NULL == (req_args = get_args(input, 1)))
        return (bad_request(BAD_INPUT));
    new_req.type = CT_CREATE;
    new_req.context_level = REPLY_OR_LOGGED;
    strcpy(new_req.message, req_args[0]);
    strcpy(new_req.team_uuid, cl->context.team_uuid);
    strcpy(new_req.channel_uuid, cl->context.channel_uuid);
    strcpy(new_req.thread_uuid, cl->context.thread_uuid);
    free(req_args);
    return new_req;
}

static request_t create_thread(char *input, client_t *cl)
{
    char **req_args;
    request_t new_req;

    if (NULL == (req_args = get_args(input, 2)))
        return (bad_request(BAD_INPUT));
    new_req.type = CT_CREATE;
    new_req.context_level = THREAD;
    strcpy(new_req.name, req_args[0]);
    strcpy(new_req.description, req_args[1]);
    strcpy(new_req.team_uuid, cl->context.team_uuid);
    strcpy(new_req.channel_uuid, cl->context.channel_uuid);
    free(req_args);
    return new_req;
}

static request_t create_channel(char *input, client_t *cl)
{
    char **req_args;
    request_t new_req;

    if (NULL == (req_args = get_args(input, 2)))
        return (bad_request(BAD_INPUT));
    new_req.type = CT_CREATE;
    new_req.context_level = CHANNEL;
    strcpy(new_req.name, req_args[0]);
    strcpy(new_req.description, req_args[1]);
    strcpy(new_req.team_uuid, cl->context.team_uuid);
    free(req_args);
    return new_req;
}

static request_t create_team(char *input)
{
    char **req_args;
    request_t new_req;

    if (NULL == (req_args = get_args(input, 2))) {
        free(input);
        return (bad_request(BAD_INPUT));
    }
    new_req.type = CT_CREATE;
    new_req.context_level = TEAM;
    strcpy(new_req.name, req_args[0]);
    strcpy(new_req.description, req_args[1]);
    for (int y = 0; req_args[y]; y++) {
        free(req_args[y]);
    }
    free(req_args);
    return new_req;
}

request_t create_req(char *user_req, char *input, client_t *cl)
{
    switch (cl->context.context_level)
    {
        case (TEAM):
            printf("the context level was TEAM\n");
            return create_team(input);
        case (CHANNEL):
            printf("the context level was CHANNEL\n");
            cl->context.context_level = TEAM;
            return create_channel(input, cl);
        case (THREAD):
            printf("the context level was THREAD\n");
            cl->context.context_level = TEAM;
            return create_thread(input, cl);
            break;
        case (REPLY_OR_LOGGED):
            printf("the context level was REPLY\n");
            cl->context.context_level = TEAM;
            return create_reply(input, cl);
            break;
        default:
            return bad_request(NO_USE);
    }
}