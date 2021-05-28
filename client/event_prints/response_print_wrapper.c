/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/resp_print_wrapper
*/

#include "../../include/client.h"

void ct_users_print(int sd, response_t *resp)
{
    char user_buffer[sizeof(user_info_t)];
    user_info_t *user;

    for (int i = 0; i < resp->extern_body_size; ++i) {
        read(sd, &user_buffer, sizeof(user_info_t));
        user = (void *)user_buffer;
        client_print_users(user->user_uuid, \
user->user_name, user->user_status);
    }
}

void ct_user_print(int sd, response_t *resp)
{
    char user_buffer[sizeof(user_info_t)];

    if (resp->status_code == STATUS_OK) {
        read(sd, &user_buffer, sizeof(user_info_t));
        user_info_t *user = (void *) user_buffer;
        client_print_user(user->user_uuid, user->user_name, user->user_status);
    }
    ///in case of error reply_status
    else
    client_error_unknown_user(resp->user_uuid);
}

void et_logged_in_print(int sd, response_t *resp)
{
    client_event_logged_in(resp->user_uuid, resp->name);
}

void et_logged_out_print(int sd, response_t *resp)
{
    client_event_logged_out(resp->user_uuid, resp->name);
}