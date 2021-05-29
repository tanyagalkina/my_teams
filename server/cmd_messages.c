/*
** EPITECH PROJECT, 2019
** server
** File description:
** server
*/

#include "../include/server.h"
#include "../include/commons.h"
#include "../libs/myteams/logging_server.h"
#include <sys/queue.h>
#include <string.h>

static int how_many(direct_message_t *dm)
{
    int counter = 0;
    message_t *msg;

    TAILQ_FOREACH(msg, &dm->message_head, next) {
        counter++;
    }
    return counter;
}

static void send_status(server_t *server, int fd, direct_message_t *dm)
{
    response_t r;

    r.request_type = CT_MESSAGES;
    r.status_code = STATUS_OK;
    r.extern_body_size = how_many(dm);
    r.extern_body_type = MESSAGE_TYPE;
    send(fd, &r, RESPONSE_SIZE, 0);
}

static void send_messages(direct_message_t *dm, int fd)
{
    message_t *msg;

    TAILQ_FOREACH(msg, &dm->message_head, next) {
        response_t r;
        r.status_code = STATUS_OK;
        strcpy(r.user_uuid, msg->info->sender_uuid);
        strcpy(r.message, msg->info->message_body);
        r.timestamp = msg->info->message_timestamp;
        send(fd, &r, RESPONSE_SIZE, 0);
    }
}

int cmd_messages(server_t *server, request_t *req, int fd)
{
    const char *suuid = get_user_by_fd(server, fd)->info->user_uuid;
    const char *ruuid = req->user_uuid;
    direct_message_t *dm;
    bool found_pair;

    TAILQ_FOREACH(dm, &server->admin->message_head, next) {
        found_pair = (strcmp(dm->user1, suuid) == 0 && strcmp(dm->user2, ruuid) == 0) ||
            (strcmp(dm->user1, ruuid) == 0 && strcmp(dm->user2, suuid) == 0);
        if (found_pair) {
            send_messages(dm, fd);
        }
    }
    return SUCCESS;
}
