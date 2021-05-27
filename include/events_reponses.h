/*
** EPITECH PROJECT, 2020
** client.h
** File description:
** myteams
*/

#ifndef TEAMS_EVENTS_REPONSES_H
#define TEAMS_EVENTS_REPONSES_H

#include "commons.h"

typedef struct event_print
{
    event_t event;
    void (*func)(int sd, response_t *response);

}event_print_t;

void et_logged_in_print(int sd, response_t *response);
void et_logged_out_print(int sd, response_t *response);
void ct_users_print(int sd, response_t *response);
void ct_user_print(int sd, response_t *response);

/*void ct_send_print(int sd, response_t *response);
void ct_messages_print(int sd, response_t *response);
void ct_subscribe_print(int sd, response_t *response);
void ct_subscribed_uuid_print(int sd, response_t *response);
void ct_subscribed_blank_print(int sd, response_t *response);
void ct_unsubscribe_print(int sd, response_t *response);
void ct_create_print(int sd, response_t *response);
void ct_list_print(int sd, response_t *response);
void et_message_rec_print(int sd, response_t *response);
void et_reply_rec_print(int sd, response_t *response);
void et_team_creat_print(int sd, response_t *response);
void et_channel_creat_print(int sd, response_t *response);
void et_thread_creat_print(int sd, response_t *response);*/

static const event_print_t event_table[] = {
        {ET_LOGGED_IN,  &et_logged_in_print},
        {ET_LOGGED_OUT, &et_logged_out_print},
        {CT_USERS, &ct_users_print},
        {CT_USER, &ct_user_print},
        {0, NULL}
};
 /*       CT_SEND,
        CT_MESSAGES,
        CT_SUBSCRIBE,
        CT_SUBSCRIBED_UUID,
        CT_SUBSCRIBED_BLANK,
        CT_UNSUBSCRIBE,
        CT_CREATE,
        CT_LIST,
        CT_INFO,
        CT_USE,
        ///int client_event_logged_in(char const *user_uuid, const char *user_name);
        ET_LOGGED_IN = 100,
        ///int client_event_logged_out(char const *user_uuid, const char *user_name);
        ET_LOGGED_OUT,
        ///int client_event_private_message_received(
        ///char const *user_uuid,
        ///char const *message_body);
        ET_MESSAGE_REC,
        ///int client_event_thread_reply_received(
        ///char const *team_uuid,
        ///char const *thread_uuid,
        ///char const *user_uuid,
        ///char const *reply_body);
        ET_REPLY_REC,
        ///int client_event_team_created(
        ///char const *team_uuid,
        ///char const *team_name,
        ///char const *team_description);
        ET_TEAM_CREAT,
        ///int client_event_channel_created(
        ///char const *channel_uuid,
        ///char const *channel_name,
        ///char const *channel_description);
        ET_CHANNEL_CREAT,
        ///int client_event_thread_created(
        ///char const *thread_uuid,
        ///char const *user_uuid,
        ///time_t thread_timestamp,
        ///char const *thread_title,
        ///char const *thread_body);
        ET_THREAD_CREAT
void ct_send_print(int sd, response_t *response);
void ct_messages_print(int sd, response_t *response);
void ct_subscribe_print(int sd, response_t *response);
void ct_subscribed_uuid_print(int sd, response_t *response);
void ct_subscribed_blank_print(int sd, response_t *response);
void ct_unsubscribe_print(int sd, response_t *response);
void ct_create_print(int sd, response_t *response);
void ct_list_print(int sd, response_t *response);
void et_logged_in_print(int sd, response_t *response);
void et_logged_out_print(int sd, response_t *response);
void et_message_rec_print(int sd, response_t *response);
void et_reply_rec_print(int sd, response_t *response);
void et_team_creat_print(int sd, response_t *response);
void et_channel_creat_print(int sd, response_t *response);
void et_thread_creat_print(int sd, response_t *response);
};*/

#endif //TEAMS_EVENTS_REPONSES_H
