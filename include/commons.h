/*
** EPITECH PROJECT, 2020
** commons
** File description:
** myteams
*/

#include <uuid/uuid.h>

#ifndef TEAMS_COMMONS_H
#define TEAMS_COMMONS_H

#pragma pack(1)
typedef struct response {
    char message[128];
    int request_type;
    int status_code;
    int extern_body_size;
    int extern_body_type;
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
