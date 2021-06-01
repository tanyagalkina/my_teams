/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../../include/client.h"

static int get_count_quotes(char *input)
{
    int i = 0;
    int count = 0;
    while (input[i]) {
        if (input[i] == '"')
            ++count;
        ++i;
    }
    return count;
}

static request_t use_thread_request(char *input, client_t *cl)
{
    request_t new_req;
    char **req_args;
    new_req.type = CT_USE;
    cl->context.context_level = THREAD;
    if (NULL == (req_args = get_args(input, 2)))
        return (bad_request(BAD_INPUT));
    strcpy(cl->context.team_uuid, req_args[0]);
    strcpy(cl->context.channel_uuid, req_args[1]);
    return new_req;
}

static request_t use_reply_or_logged_request(char *input, client_t *cl)
{
    request_t new_req;
    char **req_args;
    new_req.type = CT_USE;
    cl->context.context_level = REPLY_OR_LOGGED;
    if (NULL == (req_args = get_args(input, 3)))
        return (bad_request(BAD_INPUT));
    strcpy(cl->context.team_uuid, req_args[0]);
    strcpy(cl->context.channel_uuid, req_args[1]);
    strcpy(cl->context.thread_uuid, req_args[2]);
    return new_req;
}

static request_t use_channel_request(char *input, client_t *cl)
{
    request_t new_req;
    char **req_args;
    new_req.type = CT_USE;

    cl->context.context_level = CHANNEL;
    if (NULL == (req_args = get_args(input, 1)))
        return (bad_request(BAD_INPUT));
    strcpy(cl->context.team_uuid, req_args[0]);
    return new_req;
}

request_t use_req(char *input, client_t *cl)
{
    request_t new_req;
    new_req.type = CT_USE;

    switch (get_count_quotes(input))
    {
        case 0:
            cl->context.context_level = TEAM;
            return new_req;
        case 2:
            return use_channel_request(input, cl);
        case 4:
            return use_thread_request(input, cl);
        case 6:
            return use_reply_or_logged_request(input, cl);
        default:
            return (bad_request(QUOTES));
    }
}