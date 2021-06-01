/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../../include/client.h"

static void print_channels(int sd, response_t *resp)
{
    char channel_buffer[sizeof(channel_info_t)];
    channel_info_t *channel;

    if (resp->status_code == KO_UNKN_TEAM) {
        client_error_unknown_team(resp->team_uuid);
        return;
    }
    for (int i = 0; i < resp->extern_body_size; ++i) {
        read(sd, &channel_buffer, sizeof(channel_info_t));
        channel = (void *)channel_buffer;
        client_team_print_channels(channel->channel_uuid, \
channel->channel_name, channel->channel_description);
            }
}

static void print_threads(int sd, response_t *resp)
{
    char thread_buffer[sizeof(thread_info_t)];
    thread_info_t *thread;

    if (resp->status_code == KO_UNKN_CHANNEL) {
        client_error_unknown_channel(resp->channel_uuid);
        return;
    }
    for (int i = 0; i < resp->extern_body_size; ++i) {
        read(sd, &thread_buffer, sizeof(thread_info_t));
        thread = (void *)thread_buffer;
        client_channel_print_threads(thread->thread_uuid, \
thread->user_uuid, thread->thread_timestamp, \
thread->thread_title, thread->thread_body);
    }
}

static void print_replies(int sd, response_t *resp)
{
    char reply_buffer[sizeof(reply_info_t)];
    reply_info_t *reply;

    if (resp->status_code == KO_UNKN_THREAD) {
        client_error_unknown_thread(resp->thread_uuid);
        return;
    }
    for (int i = 0; i < resp->extern_body_size; ++i) {
        read(sd, &reply_buffer, sizeof(reply_info_t));
        reply = (void *)reply_buffer;
        client_thread_print_replies(reply->thread_uuid, \
reply->user_uuid, reply->reply_timestamp, reply->reply_body);
    }
}

void ct_list_print(int sd, response_t *resp)
{
    switch (resp->level)
    {
        case (TEAM):
            ct_subscribed_blank_print(sd, resp);
            break;
        case (CHANNEL):
            print_channels(sd, resp);
            break;
        case (THREAD):
            print_threads(sd, resp);
            break;
        case (REPLY_OR_LOGGED):
            print_replies(sd, resp);
            break;
        default:
            break;
    }
}