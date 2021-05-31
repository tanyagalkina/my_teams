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
        go = 0;
        return;
    }
    response_t *resp = (void *)cl->re_buffer;
    if (resp->request_type == ET_LOGGED_OUT) {
        client_event_logged_out(resp->user_uuid, resp->name);
        if (!strcmp(resp->name, cl->own_name))
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

request_t help_request(void)
{
    request_t req;
    show_help();
    req.type = 42;
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
            req = req_table[i].func(user_req[0], input, cl);
            break;
        }
        ++i;
    }
    if (i == 13)
        return bad_request(BAD_INPUT);
    free_2d(user_req);
    return req;
}

void process_cli_request(int sd, client_t *cl)
{
    size_t size = INPUT_SIZE;
    char *input = (char *)malloc(INPUT_SIZE);
    request_t new_request;
    if (-1 == getline(&input, &size, stdin)) {
        new_request.type = CT_LOGOUT;
    }
    else new_request = generate_request(strdup(input), cl);
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