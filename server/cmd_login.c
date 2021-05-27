/*
** EPITECH PROJECT, 2019
** handle_connection
** File description:
** handle_connection
*/

#include "../include/commons.h"
#include "../include/server.h"
#include "../libs/myteams/logging_server.h"
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

static void send_response(server_t *server, const char *name)
{
    user_t *user;
    response_t r;

    r.request_type = ET_LOGGED_IN;
    r.status_code = STATUS_OK;
    strcpy(r.name, name);
    strcpy(r.user_uuid, get_user_by_name(server, name)->info->user_uuid);

    TAILQ_FOREACH(user, &server->admin->user_head, next) {
        if (user->info->user_status == ET_LOGGED_IN) {
            send(user->current_fd, &r, RESPONSE_SIZE, 0);
        }
    }
}

static bool is_existing(server_t *server, const char *name)
{
    user_t *user = NULL;

    TAILQ_FOREACH(user, &server->admin->user_head, next) {
        if (strcmp(user->info->user_name, name) == 0) {
            return true;
        }
    }
    return false;
}

static int add_new_user(server_t *server, request_t *req, int fd)
{
    user_t *user = NULL;
    uuid_t binuuid;

    if ((user = malloc(sizeof(user_t))) == NULL)
        return FAILURE;
    if ((user->info = malloc(sizeof(user_info_t))) == NULL)
        return FAILURE;

    uuid_generate_random(binuuid);
    strcpy(user->info->user_name, req->name);
    uuid_unparse(binuuid, user->info->user_uuid);
    user->info->user_status = ET_LOGGED_IN;
    user->current_fd = fd;
    server_event_user_created(user->info->user_uuid, user->info->user_name);
    TAILQ_INSERT_TAIL(&server->admin->user_head, user, next);
    send_response(server, user->info->user_name);
    return SUCCESS;
}

int cmd_login(server_t *server, request_t *req, int fd)
{
    user_t *user;

    if (is_existing(server, req->name)) {
        if ((user = get_user_by_name(server, req->name)) == NULL)
            return FAILURE;
        if (user->info->user_status == ET_LOGGED_IN) {
            server_debug_print(WARNING, "The user is already logged in");
        }
        user->info->user_status = ET_LOGGED_IN;
        user->current_fd = fd;
        server_event_user_logged_in(user->info->user_uuid);
        send_response(server, user->info->user_name);
        return SUCCESS;
    }
    return add_new_user(server, req, fd);
}
