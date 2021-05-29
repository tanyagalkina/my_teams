/*
** EPITECH PROJECT, 2020
** commands
** File description:
** cmd_create
*/

#include "../../include/server.h"
#include "../../include/commons.h"
#include "../../libs/myteams/logging_server.h"
#include <string.h>
#include <stdio.h>
#include <sys/queue.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

static void send_response(server_t *server, const char *r_uuid, request_t *req)
{
    response_t r;
    user_t *user = NULL;
    user_fds_t *fds = NULL;

    if (!r_uuid) {
        server_debug_print(WARNING, "no given receiver uuid for the dm");
        return;
    }
    if ((user = get_user_by_uuid(server, r_uuid)) == NULL) {
        server_debug_print(WARNING, "no given user to that receiver uuid");
        return;
    }
    r.request_type = CT_SEND;
    r.status_code = STATUS_OK;
    strcpy(r.user_uuid, req->user_uuid);
    strcpy(r.message, req->message);

    TAILQ_FOREACH(fds, &user->user_fds_head, next) {
        send(fds->fd, &r, RESPONSE_SIZE, 0);
    }
}

static void append_message(direct_message_t *dm, request_t *req, \
private_message_info_t *dm_info)
{
    message_t *new_message = NULL;
    private_message_info_t *info = NULL;

    if ((new_message = malloc(sizeof(message_t))) == NULL)
        return;
    if ((info = malloc(sizeof(private_message_info_t))) == NULL)
        return;

    strcpy(info->message_body, dm_info->message_body);
    strcpy(info->sender_uuid, dm_info->sender_uuid);
    info->message_timestamp = dm_info->message_timestamp;

    new_message->info = info;

    TAILQ_INSERT_TAIL(&dm->message_head, new_message, next);
}

static void create_new_dm(server_t *server, const char *ruuid, \
request_t *req, const char *suuid)
{
    direct_message_t *dm;

    if ((dm = malloc(sizeof(direct_message_t))) == NULL)
        return;
    strcpy(dm->user1, get_user_by_uuid(server, ruuid)->info->user_name);
    strcpy(dm->user2, get_user_by_uuid(server, suuid)->info->user_name);

    private_message_info_t *info;
    if ((info = malloc(sizeof(private_message_info_t))) == NULL)
        return;
    strcpy(info->message_body, req->message);
    strcpy(info->sender_uuid, suuid);

    TAILQ_INIT(&dm->message_head);
    append_message(dm, req, info);
    TAILQ_INSERT_TAIL(&server->admin->message_head, dm, next);
}

static void process_message(server_t *server, request_t *req, \
private_message_info_t *dm_info, const char *ruuid)
{
    direct_message_t *dm;
    const char *suuid = dm_info->sender_uuid;
    bool snd;
    bool fst;

    TAILQ_FOREACH(dm, &server->admin->message_head, next) {
        fst = (strcmp(dm->user1, suuid) == 0 && strcmp(dm->user2, ruuid) == 0);
        snd = (strcmp(dm->user1, ruuid) == 0 && strcmp(dm->user2, suuid) == 0);
        if (fst || snd) {
            append_message(dm, req, dm_info);
            return;
        }
    }
    server_debug_print(INFO, "This is the start of a new conversation");
    create_new_dm(server, ruuid, req, suuid);
}

int cmd_send(server_t *server, request_t *req, int fd)
{
    private_message_info_t dm_info;
    const char *sender_uuid = get_user_by_fd(server, fd)->info->user_uuid;
    const char *receiver_uuid = req->user_uuid;
    const char *message = req->message;

    strcpy(dm_info.sender_uuid, sender_uuid);
    strcpy(dm_info.message_body, message);
    dm_info.message_timestamp = time(0);

    process_message(server, req, &dm_info, receiver_uuid);
    server_event_private_message_sended(sender_uuid, receiver_uuid, message);
    send_response(server, receiver_uuid, req);

    return SUCCESS;
}
