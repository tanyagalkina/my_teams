
/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../../include/client.h"

void creat_reply_print(response_t *resp)
{
    if (resp->status_code == KO_UNKN_THREAD)
        client_error_unknown_thread(resp->team_uuid);
    else
        client_print_reply_created(resp->thread_uuid, \
resp->user_uuid, resp->timestamp, resp->message);

}

void creat_thread_print(response_t *resp)
{
    if (resp->status_code == KO_UNKN_CHANNEL)
        client_error_unknown_channel(resp->team_uuid);
    else if (resp->status_code == KO_ERROR_EXISTS)
        client_error_already_exist();
    else
        client_print_thread_created(resp->thread_uuid, \
resp->user_uuid, resp->timestamp, resp->name, resp->description);
}

void creat_channel_print(response_t *resp)
{
    if (resp->status_code == KO_UNKN_TEAM)
        client_error_unknown_team(resp->team_uuid);
    else if (resp->status_code == KO_ERROR_EXISTS)
        client_error_already_exist();
    else
        client_print_channel_created(resp->channel_uuid, \
resp->name, resp->description);
}

void creat_team_print(response_t *resp)
{
    if (resp->status_code == KO_ERROR_EXISTS)
        client_error_already_exist();
    else
        client_print_team_created(resp->team_uuid, \
resp->name, resp->description);
}

void ct_creat_print(int sd, response_t *resp)
{
    if (resp->status_code == KO_UNAUTHOR) {
        client_error_unauthorized();
        return;
    }
    switch (resp->level)
    {
        case TEAM:
            creat_team_print(resp);
            break;
        case CHANNEL:
            creat_channel_print(resp);
            break;
        case THREAD:
            creat_thread_print(resp);
            break;
        case REPLY_OR_LOGGED:
            creat_reply_print(resp);
            break;
    }
}
