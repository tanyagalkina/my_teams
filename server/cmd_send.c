/*
** EPITECH PROJECT, 2020
** commands
** File description:
** cmd_create
*/

#include "../include/server.h"
#include "../include/commons.h"
#include "../libs/myteams/logging_server.h"
#include <string.h>
#include <stdio.h>

static void send_response(server_t *server, const char *r_uuid, request_t *req)
{
    response_t r;
    user_t *user = NULL;

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
    for (int i = 0; i < MAX_FD_PER_USER; i++) {
        if (user->fds[i] != 0)
            send(user->fds[i], &r, RESPONSE_SIZE, 0);
    }
}

int cmd_send(server_t *server, request_t *req, int fd)
{
    const char *sender_uuid = get_user_by_fd(server, fd)->info->user_uuid;
    const char *receiver_uuid = req->user_uuid;
    const char *message = req->message;

    server_event_private_message_sended(sender_uuid, receiver_uuid, message);
    send_response(server, receiver_uuid, req);

    return SUCCESS;
}
