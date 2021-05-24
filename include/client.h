/*
** EPITECH PROJECT, 2020
** client.h
** File description:
** myteams
*/

#ifndef TEAMS_CLIENT_H
#define TEAMS_CLIENT_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <uuid/uuid.h>
#include <assert.h>
#include "../include/commons.h"

#define INPUT_SIZE 2048

typedef struct req
{
    char *req;
    request_t (*func)(char **, use_level_t *);

}req_t;

request_t login_req(char **user_req, use_level_t *context_level);
request_t logout_req(char **user_req, use_level_t *context_level);
request_t users_req(char **user_req, use_level_t *context_level);
request_t user_req(char **user_req, use_level_t *context_level);
request_t send_req(char **user_req, use_level_t *context_level);
request_t messages_req(char **user_req, use_level_t *context_level);
request_t subscribe_req(char **user_req, use_level_t *context_level);
request_t subscribed_req(char **user_req, use_level_t *context_level);
request_t unsubscribe_req(char **user_req, use_level_t *context_level);
request_t create_req(char **user_req, use_level_t *context_level);
request_t list_req(char **user_req, use_level_t *context_level);
request_t info_req(char **user_req, use_level_t *context_level);
request_t use_req(char **user_req, use_level_t *context_level);

static const req_t req_table[] = {
        {"/login", &login_req},
        {"/logout", &logout_req},
        {"/users", &users_req},
        {"/user", &user_req},
        {"/send", &send_req},
        {"/messages", &messages_req},
        {"/subscribe", &subscribe_req},
        {"/subscribed", &subscribed_req},
        {"/unsubscribe", &unsubscribe_req},
        {"/create", &create_req},
        {"/list", &list_req},
        {"/info", &info_req},
        {"/use", &use_req},
        {NULL, NULL}
};

void enjoy_the_client(int sd);
char **my_str_to_word_array(char const *str);

#endif //TEAMS_CLIENT_H