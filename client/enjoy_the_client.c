/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../include/client.h"

void process_response(int sd, char *buffer)
{
    response_t *resp = (void *)buffer;
    printf("the request type was: %d\n", resp->request_type);
    printf("the response code was: %d\n", resp->status_code);
    printf("the message was: %s\n", resp->message);
    ///todo: cast the response and check the info volumes (if the case)
    ///char response[RESPONSE_SIZE];

    //read(sock, response, sizeof(TYPE_USER);
    //printf("The proseccing showed %s:", response);
}

void show_help()
{
    printf("USAGE: ./myteams_cli ip port\n");
    printf("\t\tip\tis the server ip address on which the server socket listens\n");
    printf("\t\tport\tis the port number on which the server socket listens\n");
    printf("the protocol and the commands to be updated\n");
}

///if the input is invalid returns request of type 84))
request_t generate_request(char *input, use_level_t *context_level)
{
    request_t req;
    int i = 0;

    char **user_req = my_str_to_word_array(input);
    if (!strcmp("/help", user_req[0])) {
        show_help();
        req.type = 42;
        return req;
    }

    while (req_table[i].req != NULL) {
        if (!strcmp(req_table[i].req, user_req[0])) {
            req = req_table[i].func(user_req, context_level);
            break;
        }
        ++i;
    }
    if (i == 13) {
        printf("invalid request\n");
        req.type = 84;
    }

    return req;
}

void sig_handler(int sig)
{
    (void) sig;
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

void enjoy_the_client(int sd)
{
    use_level_t context_level = NONE; /// stores the value of prev use request (if the case) otherwise == NONE
    size_t size = INPUT_SIZE;
    int valread = 0;
    set_signals();
    char *input = (char *)malloc(INPUT_SIZE);
    request_t new_request;
    char buffer[RESPONSE_SIZE];
    fd_set master;
    fd_set reading;
    FD_ZERO(&master);
    FD_ZERO(&reading);
    FD_SET(sd, &master);
    FD_SET(0, &master);

    while (go)
    {
        reading = master;
        if (select(sd + 1, &reading, NULL, NULL, NULL) < 0) {
            if (go)
            exit(84);
            else continue;
        }
        for (int i = 0; i < (sd + 1); i++) {
            if (FD_ISSET(i, &reading)) {
                if (i == 0)
                {
                    getline(&input, &size, stdin);
                    new_request = generate_request(input, &context_level);
                    if (new_request.type == 84)
                        printf("Your request is invalid, please see the spec\n");
                    if (new_request.type == 42)
                        continue;
                    else {
                        send(sd, &new_request, sizeof(request_t), 0);
                        memset(buffer, 0, RESPONSE_SIZE);
                }
            }
                else {
                    valread = read(sd, &buffer, RESPONSE_SIZE);
                    process_response(sd, buffer);
                }
            }
        }
    }
    printf("here i would free the stuff\n");
}