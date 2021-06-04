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
    if (cl->bytes == 0) {
        go = 0;
        return;
    }
    response_t *resp = (void *)cl->re_buffer;
    if (resp->request_type == CT_LOGOUT) {
        go = 0;
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

request_t check_if_logged_in(request_t req, int logged_in)
{
    if (req.type != CT_LOGIN && logged_in == 0) {
        client_error_unauthorized();
        req.type = 84;
    }
    return req;
}

request_t generate_request(char *input, client_t *cl)
{
    request_t req;
    int i = 0;
    char **user_req = my_str_to_word_array(input);
    if (NULL == user_req[0])
        return bad_request("type something!\n");
    if (!strcmp("/help", user_req[0]))
        return (help_request());
    while (req_table[i].req != NULL) {
        if (!strcmp(req_table[i].req, user_req[0])) {
            req = req_table[i].func(input, cl);
            break;
        }
        ++i;
    }
    if (i == 13)
        return bad_request(BAD_INPUT);
    free_2d(user_req);
    return check_if_logged_in(req, cl->logged_in);
}

void process_cli_request(int sd, client_t *cl)
{
    size_t size = INPUT_SIZE;
    char *input = (char *)malloc(INPUT_SIZE);
    request_t new_request;
    if (-1 == getline(&input, &size, stdin)) {
        new_request.type = CT_LOGOUT;
    }
    else new_request = generate_request(input, cl);
    free(input);
    if (new_request.type == 84) {
        printf("Your request is invalid\n");
        return;
    }
    if (new_request.type == 42 || new_request.type == CT_USE) {
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
                if (i == 0) {
                    process_cli_request(cl->sd, cl);}
                else {
                    cl->bytes = read(cl->sd, &cl->re_buffer, RESPONSE_SIZE);
                    if (cl->bytes == -1 || cl->bytes == 0) {
                        return 0;
                    }
                    process_resp_or_event(cl);
                    memset(cl->re_buffer, 0, RESPONSE_SIZE);}}}}
    return (0);
}
