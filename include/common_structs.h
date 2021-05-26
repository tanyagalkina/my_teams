/*
** EPITECH PROJECT, 2020
** commons
** File description:
** myteams
*/

#ifndef TEAMS_COMMON_STRUCTS_H
#define TEAMS_COMMON_STRUCTS_H

#include <uuid/uuid.h>

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512

#pragma pack(1)
typedef struct info_user {
    char user_uuid[UUID_STR_LEN];
    char user_name[MAX_NAME_LENGTH];
    int user_status;
}user_info_t;

typedef struct info_team {
    char team_uuid[UUID_STR_LEN];
    char team_name[MAX_NAME_LENGTH];
    char team_description[MAX_DESCRIPTION_LENGTH];
}team_info_t;

typedef struct info_channel {
    char channel_uuid[UUID_STR_LEN];
    char channel_name[MAX_NAME_LENGTH];
    char channel_description[MAX_DESCRIPTION_LENGTH];
}channel_info_t;

typedef struct info_thread {
    char thread_uuid[UUID_STR_LEN];
    char user_uuid[UUID_STR_LEN];
    time_t thread_timestamp;
    char thread_title[MAX_NAME_LENGTH];
    char thread_body[MAX_BODY_LENGTH];
}thread_info_t;

typedef struct info_reply {
    char thread_uuid[UUID_STR_LEN];
    char user_uuid[UUID_STR_LEN];
    time_t reply_timestamp;
    char reply_body[MAX_BODY_LENGTH];
}reply_info_t;

typedef struct info_private_message {
    char sender_uuid[UUID_STR_LEN];
    time_t message_timestamp;
    char message_body[MAX_BODY_LENGTH];
}private_message_info_t;
#pragma pack(0)

#endif //TEAMS_COMMON_STRUCTS_H
