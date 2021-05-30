/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../../include/client.h"

void get_info_thread(int sd, response_t *resp)
{
    if (resp->status_code == KO_UNKN_THREAD)
        client_error_unknown_thread(resp->thread_uuid);
    else if (resp->status_code == KO_UNAUTHOR)
        client_error_unauthorized();
    else
        client_print_thread(resp->thread_uuid, resp->user_uuid, \
resp->timestamp, resp->name, resp->message);
}

void get_info_channel(int sd, response_t *resp)
{
    if (resp->status_code == KO_UNKN_CHANNEL)
        client_error_unknown_channel(resp->channel_uuid);
    else if (resp->status_code == KO_UNAUTHOR)
        client_error_unauthorized();
    else
        client_print_channel(resp->channel_uuid, \
resp->name, resp->description);
}

void get_info_team(int sd, response_t *resp)
{
    if (resp->status_code == KO_UNKN_TEAM)
        client_error_unknown_channel(resp->team_uuid);
    else if (resp->status_code == KO_UNAUTHOR)
        client_error_unauthorized();
    else
        client_print_team(resp->team_uuid, resp->name, \
resp->description);
}

void get_info_logged(int sd, response_t *resp)
{
    char user_buffer[sizeof(user_info_t)];
    user_info_t *user;

    for (int i = 0; i < resp->extern_body_size; ++i) {
        read(sd, &user_buffer, sizeof(user_info_t));
        user = (void *)user_buffer;
        client_print_user(user->user_uuid, user->user_name, user->user_status);
    }
}

void ct_info_print(int sd, response_t *resp)
{
    switch (resp->level)
    {
        case (TEAM):
            get_info_team(sd, resp);
            break;
        case (CHANNEL):
            get_info_channel(sd, resp);
            break;
        case (THREAD):
            get_info_thread(sd, resp);
            break;
        case (REPLY_OR_LOGGED):
            get_info_logged(sd, resp);
            break;
        default:
            break;
    }
}