/*
** EPITECH PROJECT, 2020
** commons
** File description:
** myteams
*/

#include <uuid/uuid.h>

#ifndef TEAMS_COMMONS_H
#define TEAMS_COMMONS_H

///from 1 ... client requests
///from 100 ... client events
typedef enum command_type {
    LOGIN = 1,
    LOGOUT,
    USERS,
    USER,
    SEND,
    MESSAGES,
    SUBSCRIBE,
    SUBSCRIBED,
    UNSUBSCRIBE,
    CREATE,
    LIST,
    INFOS,
    USE,
    LOGGED_IN = 100,
    LOGGED_OUT,
    MESSAGE_REC,
    REPLY_REC,
    TEAM_CREAT,
    CHANNEL_CREAT,
    THREAD_CREAT
    ///int client_event_logged_in(char const *user_uuid, const char *user_name);
    ///int client_event_logged_out(char const *user_uuid, const char *user_name);
    ///int client_event_private_message_received(
         ///char const *user_uuid,
         ///char const *message_body);
    ///int client_event_thread_reply_received(
        ///char const *team_uuid,
        ///char const *thread_uuid,
        ///char const *user_uuid,
        ///char const *reply_body);
    ///int client_event_team_created(
        ///char const *team_uuid,
        ///char const *team_name,
        ///char const *team_description);
    ///int client_event_channel_created(
        ///char const *channel_uuid,
        ///char const *channel_name,
        ///char const *channel_description);
    ///int client_event_thread_created(
        ///char const *thread_uuid,
        ///char const *user_uuid,
        ///time_t thread_timestamp,
        ///char const *thread_title,
        ///char const *thread_body);
}event_t;

typedef enum use_context_level {
    NONE,
    TEAM,
    CHANNEL,
    THREAD
}use_level_t;

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

typedef enum data_type
{
    USER_TYPE = 1, ///names only
    MESSAGE_TYPE,
    TEAM_TYPE,
    CHANNEL_TYPE,
    THREAD_TYPE,
    REPLY_TYPE
}datatype_t;

#pragma pack(1)
typedef struct response {
    char message[128];
    int request_type;
    int status_code;
    int extern_body_size;
    int extern_body_type;
    use_level_t level;
    char description[255];
    time_t timestamp;
    char team_uuid[UUID_STR_LEN];
    char user_uuid[UUID_STR_LEN];
    char channel_uuid[UUID_STR_LEN];
    char thread_uuid[UUID_STR_LEN];
}response_t;

typedef struct request {
    int type;
    int context_level;
    char name[32];
    char description[255];
    char message[512];
    char uuid[UUID_STR_LEN];
}request_t;
#pragma pack(0)

#define REQUEST_SIZE  sizeof(struct request)
#define RESPONSE_SIZE sizeof(struct response)

#endif //TEAMS_COMMONS_H
