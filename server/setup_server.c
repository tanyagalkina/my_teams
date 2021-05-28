/*
** EPITECH PROJECT, 2019
** server
** File description:
** server
*/

#include "../include/server.h"
#include <stdlib.h>
#include <string.h>

static int setup_teams(server_t **server)
{
    if (((*server)->admin->teams = malloc(sizeof(team_t))) == NULL)
        return FAILURE;

    memset((*server)->admin->teams, 0, sizeof(team_t));

    TAILQ_INIT(&(*server)->admin->team_head);
    return SUCCESS;
}

static int setup_users(server_t **server)
{
    if (((*server)->admin->users = malloc(sizeof(user_t))) == NULL)
        return FAILURE;

    memset((*server)->admin->users, 0, sizeof(user_t));

    TAILQ_INIT(&(*server)->admin->user_head);
    return SUCCESS;
}

static int setup_messages(server_t **server)
{
    if (((*server)->admin->messages = malloc(sizeof(direct_message_t))) == NULL)
        return FAILURE;

    memset((*server)->admin->messages, 0, sizeof(direct_message_t));

    TAILQ_INIT(&(*server)->admin->message_head);
    return SUCCESS;
}

server_t *setup_server(server_t *server)
{
    if ((server->admin = (admin_t *)malloc(sizeof(admin_t))) == NULL)
        return NULL;
    if (setup_teams(&server) == FAILURE)
        return NULL;
    if (setup_users(&server) == FAILURE)
        return NULL;
    if (setup_messages(&server) == FAILURE)
        return NULL;

    return server;
}
