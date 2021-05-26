##
## EPITECH PROJECT, 2019
## d
## File description:
## d
##

END        		= \033[0m
BOLD        	= \033[1m
GREY        	= \033[30m
RED        		= \033[31m
GREEN        	= \033[32m
YELLOW        	= \033[33m
BLUE        	= \033[34m
PURPLE        	= \033[35m
CYAN        	= \033[36m
WHITE        	= \033[37m

EXTENSION 		= .c
CC 				= @gcc
CXX 			= @g++
LINKLIB			+= -L ./libs/myteams/ -lmyteams -luuid
LIB 			+= ./libs/myteams/libmyteams.so -luuid
# CFLAGS 			+= -Wall -Werror -Wextra

SERVER_NAME 	= 	myteams_server

SERVER_SRC 		= 	server/main.c 				\
					server/init_server.c		\
					server/setup_server.c		\
					server/cleanup.c			\
					server/handle_connection.c	\
					server/utils.c				\
					server/run_server.c			\
					server/save_data.c			\
					server/restore_data.c		\
					server/cmd_login.c			\
					server/get_user_by.c		\
					server/cmd_logout.c			\
					server/cmd_create.c			\
					server/cmd_users.c			\

CLIENT_NAME 	= 	myteams_cli

CLIENT_SRC 		= 	client/main.c 				\
					client/enjoy_the_client.c	\
					client/my_str_to_word.c		\
					client/requests/info.c		\
					client/requests/list.c		\
					client/requests/login.c		\
					client/requests/logout.c	\
					client/requests/messages.c	\
					client/requests/send.c		\
					client/requests/subscribe.c	\
					client/requests/create.c	\
					client/requests/subscribed.c	\
					client/requests/unsubscribe.c	\
					client/requests/use.c		\
					client/requests/user.c		\
					client/requests/users.c		\
					client/requests/request_tools.c


SERVER_OBJ 		= $(SERVER_SRC:.c=.o)
CLIENT_OBJ 		= $(CLIENT_SRC:.c=.o)

all: 			myteams_server myteams_cli

myteams_server:	$(SERVER_OBJ)
	@$(CC) -o $(SERVER_NAME) $(SERVER_OBJ) $(LIB)
	@echo -e "$(GREEN)* * * * * SERVER COMPLETED * * * * *$(END)\n"

myteams_cli:	$(CLIENT_OBJ)
	@$(CC) -o $(CLIENT_NAME) $(CLIENT_OBJ) $(LIB)
	@echo -e "$(GREEN)* * * * * CLIENT COMPLETED * * * * *$(END)"

clean:
	@rm -f $(SERVER_OBJ)
	@rm -f $(CLIENT_OBJ)
	@echo -e "$(RED)$(BOLD)* * * * *  CLEANED  * * * * *$(END)"

fclean: clean
	@rm -f $(SERVER_NAME)
	@rm -f $(CLIENT_NAME)
	@echo -e "$(RED)$(BOLD)* * * * *  CLEANED ALL  * * * * *$(END)"

re: 	fclean all

client/%.o:	client/%$(EXTENSION)
	@$(CC) $(LINKLIB) $(CFLAGS) -c -o $@ $<							\
	&& echo -e "$(GREEN)[- - OK - - - -]$(BOLD)" $< "$(END)"			\
	|| echo -e "$(RED)[- - - - KO - -]$(BOLD)" $< "$(END)"

server/%.o:	server/%$(EXTENSION)
	@$(CC) $(LINKLIB) $(CFLAGS) -c -o $@ $<							\
	&& echo -e "$(GREEN)[- - OK - - - -]$(BOLD)" $< "$(END)"			\
	|| echo -e "$(RED)[- - - - KO - -]$(BOLD)" $< "$(END)"

.PHONY: all clean fclean re
