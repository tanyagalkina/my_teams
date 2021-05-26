/*
** EPITECH PROJECT, 2019
** handle_connection
** File description:
** handle_connection
*/

#include "../include/server.h"
#include "../include/commons.h"
#include "../libs/myteams/logging_server.h"
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

int cmd_logout(server_t *server, request_t *req, int fd)
{
    user_t *user = NULL;

    if ((user = get_user_by_fd(server, fd)) == NULL)
        return FAILURE;

    user->current_fd = -1;
    user->info->user_status = LOGGED_OUT;
    server_event_user_logged_out(user->info->user_uuid);
    return SUCCESS;
}
