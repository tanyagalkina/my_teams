/*
** EPITECH PROJECT, 2019
** server
** File description:
** server
*/

#include "../../include/server.h"
#include "../../include/commons.h"
#include "../../libs/myteams/logging_server.h"
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
    user_fds_t *fds;

    r.request_type = CT_MESSAGES;
    r.status_code = STATUS_OK;
    r.extern_body_size = how_many(dm);
    r.extern_body_type = MESSAGE_TYPE;

    TAILQ_FOREACH(fds, &get_user_by_fd(server, fd)->user_fds_head, next) {
        send(fds->fd, &r, RESPONSE_SIZE, 0);
    }
}

static void send_messages(direct_message_t *dm, int fd, server_t *server)
{
    message_t *msg;
    user_fds_t *fds;

    TAILQ_FOREACH(msg, &dm->message_head, next) {
        response_t r;
        r.status_code = STATUS_OK;
        strcpy(r.user_uuid, msg->info->sender_uuid);
        strcpy(r.message, msg->info->message_body);
        r.timestamp = msg->info->message_timestamp;
        TAILQ_FOREACH(fds, &get_user_by_fd(server, fd)->user_fds_head, next) {
            send(fds->fd, &r, RESPONSE_SIZE, 0);
        }
    }
}

static void cmd_messages_error(server_t *server, request_t *req, int fd)
{
    response_t r;
    user_fds_t *fds;

    r.request_type = CT_MESSAGES;
    r.status_code = KO_UNKN_USER;
    strcpy(r.user_uuid, req->user_uuid);
    TAILQ_FOREACH(fds, &get_user_by_fd(server, fd)->user_fds_head, next) {
        send(fds->fd, &r, RESPONSE_SIZE, 0);
    }
}

int cmd_messages(server_t *server, request_t *req, int fd)
{
    const char *suuid = get_user_by_fd(server, fd)->info->user_uuid;
    const char *ruuid = req->user_uuid;
    direct_message_t *dm;
    bool fst;
    bool snd;

    if (get_user_by_uuid(server, ruuid) == NULL) {
        cmd_messages_error(server, req, fd);
        return SUCCESS;
    }

    TAILQ_FOREACH(dm, &server->admin->message_head, next) {
        fst = (strcmp(dm->user1, suuid) == 0 && strcmp(dm->user2, ruuid) == 0);
        snd = (strcmp(dm->user1, ruuid) == 0 && strcmp(dm->user2, suuid) == 0);
        if (fst || snd) {
            send_messages(dm, fd, server);
        }
    }
    return SUCCESS;
}
