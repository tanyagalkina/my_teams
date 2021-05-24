/*
** EPITECH PROJECT, 2020
** commons
** File description:
** myteams
*/

#include <uuid/uuid.h>

#ifndef TEAMS_COMMONS_H
#define TEAMS_COMMONS_H

enum command_type {
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
    USE
};

typedef enum use_context_level {
    TEAM = 1,
    CHANNEL,
    THREAD
}use_level_t;

typedef enum status_code {
    STATUS_OK = 200,
    STATUS_KO = 400
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
