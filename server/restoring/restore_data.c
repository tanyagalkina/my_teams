/*
** EPITECH PROJECT, 2019
** server
** File description:
** server
*/

#include "../../include/server.h"
#include "../../libs/myteams/logging_server.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/queue.h>
#include <string.h>

void restore_data(server_t *server)
{
    server_debug_print(INFO, "Starting getting the data");
    restore_users(server);
    restore_teams(server);
    server_debug_print(INFO, "Done with getting the data");
}
