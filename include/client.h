/*
** EPITECH PROJECT, 2020
** client.h
** File description:
** myteams
*/

#ifndef TEAMS_CLIENT_H
#define TEAMS_CLIENT_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <uuid/uuid.h>

#define INPUT_SIZE 2048

void enjoy_the_client(int sd);
char **my_str_to_word_array(char const *str);

#endif //TEAMS_CLIENT_H
