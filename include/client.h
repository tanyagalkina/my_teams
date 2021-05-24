/*
** EPITECH PROJECT, 2020
** client.h
** File description:
** myteams
*/

#ifndef TEAMS_CLIENT_H
#define TEAMS_CLIENT_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <uuid/uuid.h>

#define INPUT_SIZE 2048

/*static const cmd_t cmd_table[] = {
        {"/login", &login_req},
        {"PASS", &pass},
        {"CWD", &cwd},
        {"CDUP", &cdup},
        {"QUIT", &quit},
        {"DELE", &dele},
        {"PWD", &pwd},
        {"PASV", &pasv},
        {"PORT", &port},
        {"HELP", &help},
        {"NOOP", &noop},
        {"RETR", &retr},
        {"STOR", &stor},
        {"LIST", &list},
        {NULL, NULL}
};*/

void enjoy_the_client(int sd);
char **my_str_to_word_array(char const *str);

#endif //TEAMS_CLIENT_H
