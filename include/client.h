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
#include "events_reponses.h"
#include "../libs/myteams/logging_client.h"

#define INPUT_SIZE 2048
#define QUOTES      "please, include all arguments in quotes\n"
#define BAD_INPUT   "invalid command line input\n"
#define INVALID_UUID "invalid uuid\n"
#define NO_USE "please, define the context with /use command\n"
#define ONE_USER "only one user can use the console\n"

static volatile sig_atomic_t go = 1;

typedef struct context {
    use_level_t context_level;
    char team_uuid[UUID_STR_LEN];
    char channel_uuid[UUID_STR_LEN];
    char thread_uuid[UUID_STR_LEN];
}context_t;

typedef struct client
{
    int sd;
    context_t context;
    fd_set master;
    fd_set reading;
    int logged_in;
    uuid_t own_uuid;
    int bytes_read;
    char own_name[MAX_NAME_LENGTH];
    char re_buffer[RESPONSE_SIZE];

}client_t;

typedef struct req
{
    char *req;
    request_t (*func)(char *, char *, client_t *);

}req_t;

request_t login_req(char *user_req, char *args, client_t *cl);
request_t logout_req(char *user_req, char *args, client_t *cl);
request_t users_req(char *user_req, char *args, client_t *cl);
request_t user_req(char *user_req, char *args, client_t *cl);
request_t send_req(char *user_req, char *args, client_t *cl);
request_t messages_req(char *user_req, char *args, client_t *cl);
request_t subscribe_req(char *user_req, char *args, client_t *cl);
request_t subscribed_req(char *user_req, char *args, client_t *cl);
request_t unsubscribe_req(char *user_req, char *args, client_t *cl);
request_t create_req(char *user_req, char *args, client_t *cl);
request_t list_req(char *user_req, char *args, client_t *cl);
request_t info_req(char *user_req, char *args, client_t *cl);
request_t use_req(char *user_req, char *args, client_t *cl);

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
int enjoy_the_client(client_t *client_stuff);
char **my_str_to_word_array(char const *str);
char **my_str_to_special_array(char const *str, char const *sep);

///request_tools.c
int is_not_valid_uuid(char *str);
int count_quotes(int nb_quotes, char *input);
request_t bad_request(char *comment);
char **get_args(char *input, int nb_args);

#endif //TEAMS_CLIENT_H