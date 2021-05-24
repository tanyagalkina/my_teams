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
    printf("the user has entered: %s\n", input);
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

    ///this will be done with fpointers for all the requests
    /*if (!strcmp("/create", user_req[0]))
        return create_req(user_req, context_level);

    req.type = 3;
    strcpy(req.message, "Hello, my dear, how do u feel?");
    strcpy(req.name, "Tanya");
    strcpy(req.description, "This is our very best time ever!");
    return req;*/
    return req;
}

void enjoy_the_client(int sd)
{
    use_level_t context_level = NONE; /// stores the value of prev use request (if the case) otherwise == NONE
    size_t size = INPUT_SIZE;
    int valread = 0;
    char *input = (char *)malloc(INPUT_SIZE);
    request_t new_request;
    char buffer[RESPONSE_SIZE];

    while (1)
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
            valread = read(sd, &buffer, RESPONSE_SIZE);
            process_response(sd, buffer);
        }
    }
}