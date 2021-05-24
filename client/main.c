/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../include/commons.h"
#include "../include/client.h"

void check_args(char **av)
{
    return;
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

    // Convert IPv4 and IPv6 addresses from text to binary form
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

/// client code
int main(int argc, char **argv) {

    check_args(argv);
    int sock = do_connection(argv[1], atoi(argv[2]));
    enjoy_the_client(sock);
    /*request_t req;
    req.type = 3;
    strcpy(req.message, "Hello, my dear, how do u feel?");
    strcpy(req.name, "Tanya");
    strcpy(req.description, "This is our very best time ever!");
    int valread = 0;
    char buffer[RESPONSE_SIZE];
    while (1) {
      //  printf(" I am in the loop\n");
        send(sock, &req, sizeof(request_t), 0);
        //send (sock, hello, strlen(hello), 0);

        //send(sock , hello , strlen(hello) , 0 );
        //printf("Hello message sent\n");
        valread = read(sock, buffer, RESPONSE_SIZE);
        printf("%s\n", buffer);
    }*/
    return 0;
}