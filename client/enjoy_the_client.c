/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../include/client.h"

void process_resp_or_event(int sd, char *buffer, int valread)
{
    char user_buffer[sizeof(user_info_t)];

    if (valread == 0) {
        printf("our server is gone on vacation, what a pitty...\n");
        go = 0;
        return;
    }
    response_t *resp = (void *)buffer;
    switch (resp->request_type) {
        case (LOGGED_IN):
            client_event_logged_in(resp->user_uuid, resp->name);
            break;
        case (LOGGED_OUT):
            client_event_logged_out(resp->user_uuid, resp->name);
            break;
        case (USERS):
            for (int i = 0; i < resp->extern_body_size; ++i) {
                read(sd, &user_buffer, sizeof(user_info_t));
                user_info_t *user = (void *)user_buffer;
                client_print_users(user->user_uuid, user->user_name, user->user_status);
            }
            break;
    }
    /*printf("the request type was: %d\n", resp->request_type);
    printf("the response code was: %d\n", resp->status_code);
    printf("the message was: %s\n", resp->message);
    client_print_channel("uuid", resp->message, resp->description);*/
}

void show_help()
{
    printf("USAGE: ./myteams_cli ip port\n");
    printf("\t\tip\tis the server ip address on which the server socket listens\n");
    printf("\t\tport\tis the port number on which the server socket listens\n");
    printf("the protocol and the commands to be updated...\n");
}

///if the input is invalid returns request of type 84))
request_t generate_request(char *input, client_t *cl)
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
            req = req_table[i].func(user_req[0], input, cl);
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

void process_cli_request(int sd, client_t *cl)
{
    size_t size = INPUT_SIZE;
    char *input = (char *)malloc(INPUT_SIZE);
    request_t new_request;
    getline(&input, &size, stdin);
    new_request = generate_request(input, cl);
    if (new_request.type == 84) {
        printf("Your request is invalid\n");
        printf(new_request.message);
        return;
    }
    if (new_request.type == 42 || new_request.type == USE) {
        printf("the request type was use if not help\n");
        return;
    }
    else
        send(sd, &new_request, sizeof(request_t), 0);
}

void enjoy_the_client(client_t *cl)
{
    int valread = 0;
    char buffer[RESPONSE_SIZE];
    while (go) {
        cl->reading = cl->master;
        if (select(cl->sd + 1, &cl->reading, NULL, NULL, NULL) < 0) {
            if (go)
                exit(84);
            else continue;
        }
        for (int i = 0; i < (cl->sd + 1); i++) {
            if (FD_ISSET(i, &cl->reading)) {
                if (i == 0)
                    process_cli_request(cl->sd, cl);
                else {
                    valread = read(cl->sd, &buffer, RESPONSE_SIZE);
                    process_resp_or_event(cl->sd, buffer, valread);
                    memset(buffer, 0, RESPONSE_SIZE);
                }
            }
        }
    }
    printf("here i would free the stuff... but what?\n");
}