/*
** EPITECH PROJECT, 2020
** commons
** File description:
** myteams
*/

#ifndef TEAMS_COMMONS_H
#define TEAMS_COMMONS_H

#include <uuid/uuid.h>
#include "server.h"

///from 1 ... client requests
///from 100 ... client events
/* maybe split those up into request and events and then name them properly */
typedef enum command_type {
    CT_LOGIN = 1,
    CT_LOGOUT,
    CT_USERS,
    CT_USER,
    CT_SEND,
    CT_MESSAGES,
    CT_SUBSCRIBE,
    CT_SUBSCRIBED_UUID,
    CT_SUBSCRIBED_BLANK,
    CT_UNSUBSCRIBE,
    CT_CREATE,
    CT_LIST,
    CT_INFO,
    CT_USE,
    CT_ERROR_UNAUTHOR,
    ///int client_event_logged_in(char const *user_uuid,
    /// const char *user_name);
    ET_LOGGED_IN = 100,
    ///int client_event_logged_out
    /// (char const *user_uuid, const char *user_name);
    ///int client_event_logged_out(char const *user_uuid,
    /// const char *user_name);
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
}event_t;

/* name these something like UCL_UNDEFINED ...*/
typedef enum use_context_level {
    UNDEFINED,
    TEAM,
    CHANNEL,
    THREAD,
    REPLY_OR_LOGGED
}use_level_t;

/* name these something like ST_OK, ST_UNKN_TEAM ...*/
typedef enum status_code {
    STATUS_OK = 200,
    ///int client_error_unknown_team(char const *team_uuid);
    KO_UNKN_TEAM = 400,
    ///int client_error_unknown_channel(char const *channel_uuid);
    KO_UNKN_CHANNEL = 500,
    ///int client_error_unknown_thread(char const *thread_uuid);
    KO_UNKN_THREAD = 600,
    ///int client_error_unknown_user(char const *user_uuid);
    KO_UNKN_USER = 700,
    ///int client_error_unauthorized(void);
    KO_UNAUTHOR = 800,
    ///int client_error_already_exist(void);
    KO_ERROR_EXISTS = 900
}code_t;

/* name these something like DT_USER, DT_MESSAGE ... */
typedef enum data_type
{
    USER_TYPE = 1, ///names only
    MESSAGE_TYPE,
    TEAM_TYPE,
    CHANNEL_TYPE,
    THREAD_TYPE,
    REPLY_TYPE
}datatype_t;

typedef struct response {
    char message[MAX_BODY_LENGTH];
    char name[MAX_NAME_LENGTH];
    event_t request_type;
    code_t status_code;
    int extern_body_size;
    datatype_t extern_body_type;
    use_level_t level;
    char description[MAX_DESCRIPTION_LENGTH];
    time_t timestamp;
    char team_uuid[UUID_STR_LEN];
    char user_uuid[UUID_STR_LEN];
    char channel_uuid[UUID_STR_LEN];
    char thread_uuid[UUID_STR_LEN];
}response_t;

typedef struct request {
    int type;
    use_level_t context_level;
    char name[32];
    char description[255];
    char message[512];
    char team_uuid[UUID_STR_LEN];
    char user_uuid[UUID_STR_LEN];
    char channel_uuid[UUID_STR_LEN];
    char thread_uuid[UUID_STR_LEN];
}request_t;

#define REQUEST_SIZE  sizeof(struct request)
#define RESPONSE_SIZE sizeof(struct response)

#endif //TEAMS_COMMONS_H
