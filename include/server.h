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
#include <assert.h>
#include "common_structs.h"

#define COLOR_BLUE    "\x1b[34m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_RESET   "\x1b[0m"
#define COLOR_YELLOW  "\x1b[33m"

#define SERVER_BACKLOG 10
#define FAILURE 1
#define SUCCESS 0
#define MAX_FD_PER_USER 10

typedef enum user_status_t {
    US_LOGGED_OUT,
    US_LOGGED_IN
} user_status_t;

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
    reply_info_t *info;
} comment_t;

typedef struct thread_t {
    TAILQ_ENTRY(thread_t) next;
    thread_info_t *info;
    comment_t *comments;                        /* list of comment */
    TAILQ_HEAD(, comment_t) comments_head;      /* comments of this thread */
} thread_t;

typedef struct channel_t {
    TAILQ_ENTRY(channel_t) next;
    channel_info_t *info;
    TAILQ_HEAD(, thread_t) thread_head;         /* list of threads */
} channel_t;

typedef struct team_user_info_t {
    TAILQ_ENTRY(team_user_info_t) next;
    char user_uuid[UUID_STR_LEN];
} team_user_info_t;

typedef struct team_t {
    TAILQ_ENTRY(team_t) next;
    team_info_t *info;
    channel_t *channels;                        /* list of channels */
    TAILQ_HEAD(, channel_t) channel_head;
    TAILQ_HEAD(, team_user_info_t) user_info_head;
} team_t;

typedef struct user_subscribed_teams_t {
    TAILQ_ENTRY(user_subscribed_teams_t) next;
    char team_uuid[UUID_STR_LEN];
} user_subscribed_teams_t;

typedef struct user_fds_t {
    TAILQ_ENTRY(user_fds_t) next;       /* 'linked list next pointer */
    int fd;
} user_fds_t;

typedef struct user_t {
    TAILQ_ENTRY(user_t) next;       /* 'linked list next pointer */
    user_info_t *info;
    TAILQ_HEAD(, user_fds_t) user_fds_head;
    TAILQ_HEAD(, user_subscribed_teams_t) subscribed_teams_head;
} user_t;

typedef struct message_t {
    TAILQ_ENTRY(message_t) next;    /* 'linked list next pointer */
    private_message_info_t *info;
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
int run_server(server_t *server, fd_set current, fd_set ready);

/* handle_connection.c */
void handle_connection(server_t *server, int fd, fd_set *current);

/* save_data.c */
void save_data(server_t *server);

/* restore_data.c */
void restore_data(server_t *server);

/* get_user_by.c */
user_t *get_user_by_fd(server_t *server, int fd);
user_t *get_user_by_name(server_t *server, const char *name);
user_t *get_user_by_uuid(server_t *server, const char *uuid);

/* get_team_by.c */
team_t *get_team_by_uuid(server_t *server, const char *uuid);

/* saving/.c */
void save_users(server_t *server);
void save_teams(server_t *server);

/* restoring/.c */
void restore_users(server_t *server);
void restore_teams(server_t *server);
/* create/errors.c */
void error_already_exist(user_t *user);
void error_unauthorized(int fd);
void error_not_exist(const char *uuid, user_t *user, int code, int level);
///create_channel_send_to_all
void channel_send_response(team_t *team, channel_t *ch, int fd);

#endif //SERVER_H_
