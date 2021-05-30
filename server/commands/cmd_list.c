/*
** EPITECH PROJECT, 2020
** commands
** File description:
** cmd_create
*/

#include "../../include/server.h"
#include "../../include/commons.h"
#include "../../libs/myteams/logging_server.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/queue.h>


int cmd_list(server_t *server, request_t *req, int fd)
{
    printf("the context level was %d\n", req->context_level);
    //printf("the name was %s\n", req->name);
    //printf("description was %s\n", req->description);
}
