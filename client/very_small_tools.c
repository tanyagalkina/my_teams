/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../include/client.h"

request_t help_request(void)
{
    request_t req;
    show_help();
    req.type = 42;
    return req;
}

void free_2d(char **s)
{
    for (int i = 0; s[i]; i++) {
        char *cur = s[i];
        free(cur);
    }
    free(s);
}

void show_help(void)
{
    printf("the protocol and the commands to be updated...\n");
}

void sig_handler(int sig)
{
    write(1, "\nGoodbye!\n", 10);
    go = 0;
}

void set_signals(void)
{
    signal(SIGINT, sig_handler);
    signal(SIGPIPE, sig_handler);
    signal(SIGTERM, sig_handler);
}