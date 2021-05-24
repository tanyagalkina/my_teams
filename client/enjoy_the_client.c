/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../include/commons.h"
#include "../include/client.h"

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


void process_response(int sd, char *buffer)
{
    response_t *resp = (void *)buffer;
    printf("the request type was: %d\n", resp->request_type);
    printf("the response code was: %d\n", resp->status_code);
    printf("the message was: %s\n", resp->message);
    ///todo: cast the response and check the info volumes (if the case)
    ///char response[RESPONSE_SIZE];

    //read(sock, response, RESPONSE_SIZE);
    //printf("The proseccing showed %s:", response);
}

request_t create_req(char **user_req, int context_level)
{
    request_t new_req;

    switch (context_level)
    {
        case(0):
            new_req.type = CREATE;
            strcpy(new_req.name, (user_req[1]));
            new_req.context_level = 0;
            strcpy(new_req.description, (user_req[2]));
            return new_req;
        default:
            new_req.type = 84;
    }
}

void show_help()
{
    printf("USAGE: ./myteams_cli ip port\n");
    printf("\t\tip\tis the server ip address on which the server socket listens\n");
    printf("\t\tport\tis the port number on which the server socket listens\n");
    printf("the protocol and the commands to be updated\n");
}

///if the input is invalid returns request of type 84))
request_t generate_request(char *input, int context_level)
{
    printf("the user has entered: %s\n", input);
    request_t req;

    char **user_req = my_str_to_word_array(input);
    if (!strcmp("/help", user_req[0])) {
        show_help();
        req.type = 42;
        return req;
    }
    ///this will be done with fpointers for all the requests
    if (!strcmp("/create", user_req[0]))
        return create_req(user_req, context_level);

    req.type = 3;
    strcpy(req.message, "Hello, my dear, how do u feel?");
    strcpy(req.name, "Tanya");
    strcpy(req.description, "This is our very best time ever!");
    return req;
}

void enjoy_the_client(int sd)
{
    int context_level = 0; /// stores the value of prev use request (if the case) otherwise == 0
    size_t size = INPUT_SIZE;
    int valread = 0;
    char *input = (char *)malloc(INPUT_SIZE);
    request_t new_request;
    char buffer[RESPONSE_SIZE];

    while (1)
    {
        getline(&input, &size, stdin);
        new_request = generate_request(input, context_level);
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