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
#include <signal.h>
#include <uuid/uuid.h>

#include "commons.h"
#include "common_structs.h"
#include "../libs/myteams/logging_client.h"

#define INPUT_SIZE 2048

static volatile sig_atomic_t go = 1;

typedef struct req
{
    char *req;
    request_t (*func)(char *, char *, use_level_t *);

}req_t;

typedef struct client
{
    int sd;
    use_level_t context_level;
    fd_set master;
    fd_set reading;

}client_t;

request_t login_req(char *user_req, char *args, use_level_t *context_level);
request_t logout_req(char *user_req, char *args, use_level_t *context_level);
request_t users_req(char *user_req, char *args, use_level_t *context_level);
request_t user_req(char *user_req, char *args, use_level_t *context_level);
request_t send_req(char *user_req, char *args, use_level_t *context_level);
request_t messages_req(char *user_req, char *args, use_level_t *context_level);
request_t subscribe_req(char *user_req, char *args, use_level_t *context_level);
request_t subscribed_req(char *user_req, char *args, use_level_t *context_level);
request_t unsubscribe_req(char *user_req, char *args, use_level_t *context_level);
request_t create_req(char *user_req, char *args, use_level_t *context_level);
request_t list_req(char *user_req, char *args, use_level_t *context_level);
request_t info_req(char *user_req, char *args, use_level_t *context_level);
request_t use_req(char *user_req, char *args, use_level_t *context_level);

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

void set_signals(void);
void enjoy_the_client(client_t *client_stuff);
char **my_str_to_word_array(char const *str);

#endif //TEAMS_CLIENT_H