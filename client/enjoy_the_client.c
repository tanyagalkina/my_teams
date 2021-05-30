/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../include/client.h"

void process_resp_or_event(client_t *cl)
{
    int i = 0;
    if (cl->bytes_read == 0) {
        printf("our server is gone on vacation, what a pitty...\n");
        go = 0;
        return;
    }
    response_t *resp = (void *)cl->re_buffer;
    if (resp->request_type == ET_LOGGED_OUT) {
        client_event_logged_out(resp->user_uuid, resp->name);
        if (!strcmp(resp->name, cl->own_name)) {
            printf("I HAVE HAD GREAT TIME WITH YOU, GUYS!\n");
            go = 0;
        }
        return;
    }
    while (event_table[i].event != 0) {
        if (event_table[i].event == resp->request_type) {
            event_table[i].func(cl->sd, resp);
            break;
        }
        ++i;
    }
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
    printf("the input was %s\n", input);
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
    printf("the couter was %d\n", i);
    if (i == 13) {
        printf("invalid request\n");
        req.type = 84;
    }
    return req;
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

void process_cli_request(int sd, client_t *cl)
{
    size_t size = INPUT_SIZE;
    char *input = (char *)malloc(INPUT_SIZE);
    request_t new_request;
    if (getline(&input, &size, stdin) == -1) {
        printf ("Goodbye!\n");
        go = 0;
        return;
    }
    new_request = generate_request(strdup(input), cl);
    free(input);
    if (new_request.type == 84) {
        printf("Your request is invalid\n");
        printf(new_request.message);
        return;
    }
    if (new_request.type == 42 || new_request.type == CT_USE) {
        printf("the request type was use if not help\n");
        return;
    }
    else
        send(sd, &new_request, sizeof(request_t), 0);
}

int enjoy_the_client(client_t *cl)
{
    while (go) {
        cl->reading = cl->master;
        if (select(cl->sd + 1, &cl->reading, NULL, NULL, NULL) < 0) {
            if (go)
                return (84);
            else continue;
        }
        for (int i = 0; i < (cl->sd + 1); i++) {
            if (FD_ISSET(i, &cl->reading)) {
                if (i == 0)
                    process_cli_request(cl->sd, cl);
                else {
                    cl->bytes_read = read(cl->sd, &cl->re_buffer, RESPONSE_SIZE);
                    process_resp_or_event(cl);
                    memset(cl->re_buffer, 0, RESPONSE_SIZE);
                }
            }
        }
    }
    printf("SEE U LATER...\n");
    return (0);
}