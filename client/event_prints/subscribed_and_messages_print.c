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
    if (resp->status_code == KO_UNKN_USER) {
        client_error_unknown_user(resp->user_uuid);
        return;
    }
    for (int i = 0; i < resp->extern_body_size; ++i) {
        read(sd, &message_buffer, sizeof(private_message_info_t));
        message = (void *)message_buffer;
        client_private_message_print_messages(message->sender_uuid, \
message->message_timestamp, message->message_body);
    }
}

void ct_subscribed_uuid_print(int sd, response_t *resp)
{
    char subscribed_buffer[sizeof(user_info_t)];
    user_info_t *user;
    if (resp->status_code == KO_UNKN_TEAM) {
        client_error_unknown_team(resp->team_uuid);
        return;
    }
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