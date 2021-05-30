/*
** EPITECH PROJECT, 2019
** server
** File description:
** server
*/

#include "../../include/server.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <sys/stat.h>
#include <sys/types.h>

void save_data(server_t *server)
{
    server_debug_print(INFO, "starting to save now");
    save_teams(server);
    save_users(server);
    server_debug_print(INFO, "finished saving data");
}
