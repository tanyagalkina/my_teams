/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../../include/client.h"

void ct_messages_print(int sd, response_t *resp)
{
    char message_buffer[sizeof(private_message_info_t)];
    private_message_info_t *message;

    for (int i = 0; i < resp->extern_body_size; ++i) {
        read(sd, &message_buffer, sizeof(private_message_info_t));
        message = (void *)message_buffer;
        client_private_message_print_messages(message->sender_uuid, \
message->message_timestamp, message->message_body);
    }
}

void ct_subscribed_uuid_print(int sd, response_t *resp)
{
    char subscribed_buffer[sizeof(private_message_info_t)];
    user_info_t *user;

    for (int i = 0; i < resp->extern_body_size; ++i) {
        read(sd, &subscribed_buffer, sizeof(user_info_t));
        user = (void *)subscribed_buffer;
        client_print_users(user->user_uuid, user->user_name, user->user_status);
    }
}

void ct_subscribed_blank_print(int sd, response_t *resp)
{
    char teams_buffer[sizeof(team_info_t)];
    team_info_t *team;

    for (int i = 0; i < resp->extern_body_size; ++i) {
        read(sd, &teams_buffer, sizeof(team_info_t));
        team = (void *)teams_buffer;
        client_print_teams(team->team_uuid, team->team_name, \
team->team_description);
    }
}

static void print_channels(int sd, response_t *resp)
{
    char channel_buffer[sizeof(channel_info_t)];
    channel_info_t *channel;

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
            ///int client_error_unknown_team(char const *team_uuid);
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

void ct_info_print(int sd, response_t *resp)
{
    switch (resp->level)
    {
        case (TEAM):
           /// int client_error_unknown_team(char const *team_uuid);
            break;
        case (CHANNEL):
            break;
        case (THREAD):
            break;
        case (REPLY_OR_LOGGED):
            break;
        default:
            break;
    }
}