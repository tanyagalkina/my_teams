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
void et_message_rec_print(int sd, response_t *response);
void et_reply_rec_print(int sd, response_t *response);
void et_team_creat_print(int sd, response_t *response);
void et_channel_creat_print(int sd, response_t *response);
void et_thread_creat_print(int sd, response_t *response);
void ct_messages_print(int sd, response_t *response);
void ct_subscribed_uuid_print(int sd, response_t *response);
void ct_subscribed_blank_print(int sd, response_t *response);
void ct_list_print(int sd, response_t *response);
void ct_info_print(int sd, response_t *response);
void ct_creat_print(int sd, response_t *response);
void ct_unauthorized(int sd, response_t *response);
///todo: check eventual error prints
/*void ct_send_print(int sd, response_t *response);
void ct_subscribe_print(int sd, response_t *response);
void ct_unsubscribe_print(int sd, response_t *response);
void ct_create_print(int sd, response_t *response);*/

static const event_print_t event_table[] = {
        {CT_USERS, &ct_users_print},
        {CT_USER, &ct_user_print},
        {CT_ERROR_UNAUTHOR, &ct_unauthorized},
        {CT_MESSAGES, &ct_messages_print},
        {CT_SUBSCRIBED_UUID, &ct_subscribed_uuid_print},
        {CT_SUBSCRIBED_BLANK, &ct_subscribed_blank_print},
        {CT_LIST, &ct_list_print},
        {CT_INFO, &ct_info_print},
        {CT_CREATE, &ct_creat_print},
        {ET_LOGGED_IN,  &et_logged_in_print},
        {ET_LOGGED_OUT, &et_logged_out_print},
        {ET_MESSAGE_REC, &et_message_rec_print},
        {ET_REPLY_REC, &et_reply_rec_print},
        {ET_TEAM_CREAT, &et_team_creat_print},
        {ET_CHANNEL_CREAT, &et_channel_creat_print},
        {ET_THREAD_CREAT, &et_thread_creat_print},
        {0, NULL}
};

#endif //TEAMS_EVENTS_REPONSES_H