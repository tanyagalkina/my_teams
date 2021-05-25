/*
** EPITECH PROJECT, 2020
** commons
** File description:
** myteams
*/

#ifndef TEAMS_COMMON_STRUCTS_H
#define TEAMS_COMMON_STRUCTS_H

#pragma pack(1)
typedef struct info_user {
    char const *user_uuid;
    char const *user_name;
    int user_status;
}user_info_t;

typedef struct info_team {
    char const *team_uuid;
    char const *team_name;
    char const *team_description;
}team_info_t;

typedef struct info_channel {
    char const *channel_uuid;
    char const *channel_name;
    char const *channel_description;
}channel_info_t;

typedef struct info_thread {
    char const *thread_uuid;
    char const *user_uuid;
    time_t thread_timestamp;
    char const *thread_title;
    char const *thread_body;
}thread_info_t;

typedef struct info_reply {
    char const *thread_uuid;
    char const *user_uuid;
    time_t reply_timestamp;
    char const *reply_body;
}reply_info_t;

typedef struct info_private_message {
    char const *sender_uuid;
    time_t message_timestamp;
    char const *message_body;
}private_message_info_t;
#pragma pack(0)

#endif //TEAMS_COMMON_STRUCTS_H