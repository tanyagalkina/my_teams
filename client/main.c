/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../include/client.h"

static int is_valid_port(char *av)
{
    int pid = atoi(av);
    int num_length = 0;

    while (pid) {
        num_length++;
        pid /= 10;
    }
    if (atoi(av) < 1 || atoi(av) > 65353 || strlen(av) != (size_t)num_length) {
        printf("port number is invalid\n");
        return (0);
    }
    return (1);
}

void display_help(void)
{
    printf("USAGE: ./myteams_cli ip port\n");
    printf("\t\tip\tis the server ip address on which the server socket listens\n");
    printf("\t\tport\tis the port number on which the server socket listens\n");
}

void check_args(int argc, char **av)
{
    if (argc == 2 && !strcmp("-help", av[1])) {
        display_help();
        exit (0);
    }
    if (argc != 3 ) {
        display_help();
        exit (84);
    }
    if (is_valid_port(av[2]))
        return;
    else
        exit (84);
}

int do_connection(char *ip, int port)
{
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    return sock;
}

void init_client_stuff(client_t *client_stuff, int sock)
{
    client_stuff->sd = sock;
    client_stuff->context.context_level = UNDEFINED;
    client_stuff->bytes_read = 0;
    client_stuff->own_name[0] = '\0';
    FD_ZERO(&client_stuff->master);
    FD_ZERO(&client_stuff->reading);
    FD_SET(sock, &client_stuff->master);
    FD_SET(0, &client_stuff->master);
}

int main(int argc, char **argv)
{
    int sock;
    client_t *client_stuff;
    check_args(argc, argv);
    sock = do_connection(argv[1], atoi(argv[2]));
    if (sock == -1)
        return (84);
    init_client_stuff(client_stuff, sock);
    set_signals();
    return (enjoy_the_client(client_stuff));
    //return 0;
}