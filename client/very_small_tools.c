/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../include/client.h"

void free_2d(char **s)
{
    for (int i = 0; s[i]; i++) {
        char *cur = s[i];
        free(cur);
    }
    free(s);
}

void show_help()
{
    printf("USAGE: ./myteams_cli ip port\n");
    printf("\t\tip\tis the server ip address on which the server socket listens\n");
    printf("\t\tport\tis the port number on which the server socket listens\n");
    printf("the protocol and the commands to be updated...\n");
}

void sig_handler(int sig)
{
    write(1, "\nGoodbye!\n", 10);
    //exit(0);
    go = 0;
}

void set_signals(void)
{
    signal(SIGINT, sig_handler);
    signal(SIGPIPE, sig_handler);
    signal(SIGTERM, sig_handler);
}