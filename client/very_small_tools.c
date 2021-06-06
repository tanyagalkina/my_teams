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
    FILE *help_file_ptr;
    char ch;

    help_file_ptr = fopen("myteams_documentation/help.txt", "r");
    if (help_file_ptr == NULL) {
        printf("help info is currently not available, we apologize\n");
        printf("try to see rfc.txt\n");
        return;
    }
    do {
        ch = fgetc(help_file_ptr);
        putchar(ch);
    } while (ch != EOF);
    fclose(help_file_ptr);
    return;
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