/*
** EPITECH PROJECT, 2019
** server
** File description:
** server
*/

#ifndef SERVER_H_
#define SERVER_H_

#include <arpa/inet.h>
#include <stdbool.h>
#include <sys/queue.h>
#include <uuid/uuid.h>
#include "common_structs.h"

#define COLOR_BLUE    "\x1b[34m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_RESET   "\x1b[0m"
#define COLOR_YELLOW  "\x1b[33m"

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512
#define SERVER_BACKLOG 10
#define FAILURE 1
#define SUCCESS 0

typedef enum debug_state_t {
    INFO,
    WARNING,
    ERROR
} debug_state_t;

static const char debug_state_print[3][10] = {
    COLOR_CYAN,
    COLOR_YELLOW,
    COLOR_RED
};

typedef struct comment_t {
    TAILQ_ENTRY(comment_t) next;
    char author_name[MAX_NAME_LENGTH];          /* name of the author */
    char body[MAX_BODY_LENGTH];                 /* message */
    time_t timestamp;                           /* timestamp of creation */
} comment_t;

typedef struct thread_t {
    TAILQ_ENTRY(thread_t) next;
    char author_name[MAX_NAME_LENGTH];          /* name of the thread author */
    char title[MAX_DESCRIPTION_LENGTH];         /* title of the thread */
    char body[MAX_BODY_LENGTH];                 /* message of the thread */
    time_t timestamp;                           /* timestamp of creation */
    comment_t *comments;                        /* list of comment */
    TAILQ_HEAD(, comment_t) comments_head;      /* comments of this thread */
} thread_t;

typedef struct channel_t {
    TAILQ_ENTRY(channel_t) next;
    char name[MAX_NAME_LENGTH];                 /* name of the channel */
    char uuid[UUID_STR_LEN];                    /* uuid of the channel */
    char description[MAX_DESCRIPTION_LENGTH];   /* description of channel */
    TAILQ_HEAD(, thread_t) thread_head;         /* list of threads */
} channel_t;

typedef struct team_t {
    TAILQ_ENTRY(team_t) next;
    char name[MAX_NAME_LENGTH];                 /* name of the team */
    char uuid[UUID_STR_LEN];                    /* uuid of the team */
    char description[MAX_DESCRIPTION_LENGTH];   /* description of the team */
    channel_t *channels;                        /* list of channels */
    TAILQ_HEAD(, channel_t) channel_head;
} team_t;

typedef struct user_t {
    char name[MAX_NAME_LENGTH];     /* name of the user */
    char uuid[UUID_STR_LEN];        /* uuid of the user */
    uuid_t *subscribed_teams;       /* list of subscribed teams */
    int isLoggedIn;                /* true if the user is loggged in */
} user_t;

typedef struct message_t {
    TAILQ_ENTRY(message_t) next;    /* 'linked list next pointer */
    time_t timestamp;               /* timestamp of the message */
    char from[UUID_STR_LEN];        /* uuid of the sender */
    char body[MAX_BODY_LENGTH];     /* body of the message */
} message_t;

typedef struct direct_message_t {
    TAILQ_ENTRY(direct_message_t) next;
    char user1[UUID_STR_LEN];       /* uuid of communication partner 1 */
    char user2[UUID_STR_LEN];       /* uuid of communication partner 2 */
    message_t *messages;            /* list of all messages between those */
    TAILQ_HEAD(, message_t) message_head;
} direct_message_t;

typedef struct admin_t {
    user_t *users;                          /* list of users */
    TAILQ_HEAD(, user_t) user_head;
    team_t *teams;                         /* list of teams */
    TAILQ_HEAD(, team_t) team_head;
    direct_message_t *messages;             /* list of direct messages */
    TAILQ_HEAD(, direct_message_t) message_head;
} admin_t;

typedef struct server_t {
    int fd;                         /* fd of the server */
    int port;                       /* port where the server is running on */
    struct sockaddr_in addr;        /* socket information */
    admin_t *admin;                 /* pointer to a admin structure */
} server_t;

void server_debug_print(debug_state_t state, const char *msg);

/* init_server.c */
server_t *init_server(int port);

/* cleanup.c */
void cleanup(server_t *server);

/* setup_server.c */
server_t *setup_server(server_t *server);

/* utils.h */
char **split_string(char *str);
void free_2d(char **s);

/* run_server.c */
int run_server(server_t *server);

/* handle_connection.c */
void handle_connection(server_t *server, int fd, fd_set *current);

/* save_data.c */
void save_data(server_t *server);

/* restore_data.c */
void restore_data(server_t *server);

#endif //SERVER_H_