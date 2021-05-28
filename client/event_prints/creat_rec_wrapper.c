/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../../include/client.h"

void et_message_rec_print(int sd, response_t *resp)
{
    client_event_private_message_received(resp->user_uuid, resp->message);
}

void et_reply_rec_print(int sd, response_t *resp)
{
    client_event_thread_reply_received(resp->team_uuid, \
resp->thread_uuid, resp->user_uuid, resp->message);
}

void et_team_creat_print(int sd, response_t *resp)
{
    client_event_team_created(resp->team_uuid, \
resp->name, resp->description);
}

void et_channel_creat_print(int sd, response_t *resp)
{
    client_event_channel_created(resp->channel_uuid, \
resp->name, resp->description);
}

void et_thread_creat_print(int sd, response_t *resp)
{
    client_event_thread_created(resp->thread_uuid, resp->user_uuid, \
resp->timestamp, resp->name, resp->message);
}