/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../../include/client.h"

request_t create_req(char *user_req, char *args, use_level_t *context_level)
{
    request_t new_req;

    switch (*context_level)
    {
        case(NONE):
            new_req.type = CREATE;
            strcpy(new_req.name, "New_name");
            new_req.context_level = *context_level;
            strcpy(new_req.description, "New_description");
            return new_req;
        default:
            new_req.type = 84;
            *context_level = NONE;
            return new_req;
    }
}