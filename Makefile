##
## EPITECH PROJECT, 2020
## PSU_nmobjdump_2019
## File description:
## Makefile
##

OUTPUT_SERVER = myteams_server
OUTPUT_CLI = myteams_cli

BUILD_DIR = build

CC = cc
CFLAGS += -I./libs/myteams -I./include
LDFLAGS += -L ./libs/myteams -lmyteams -luuid

OBJ_SERVER = $(SRC_SERVER_MAIN:%.c=$(BUILD_DIR)/%.o)
SRC_SERVER =      					server/init_server.c				\
                 					server/setup_server.c				\
                 					server/cleanup.c					\
                 					server/handle_connection.c			\
                 					server/utils.c						\
                 					server/run_server.c					\
                 					server/get_user_by.c				\
                 					server/get_team_by.c				\
                 					server/commands/cmd_login.c			\
                 					server/commands/cmd_logout.c		\
                 					server/commands/cmd_create.c		\
                 					server/commands/cmd_users.c			\
                 					server/commands/cmd_user.c			\
                 					server/commands/cmd_send.c			\
                 					server/commands/cmd_send_error.c	\
                 					server/commands/cmd_messages.c		\
                 					server/commands/cmd_subscribe.c		\
                 					server/commands/cmd_unsubscribe.c	\
                 					server/commands/cmd_list.c			\
                 					server/commands/cmd_login_error.c	\
                 					server/saving/save_data.c			\
                 					server/saving/save_teams.c			\
                 					server/saving/save_users.c			\
                 					server/restoring/restore_data.c		\
                 					server/restoring/restore_users.c	\
                 					server/restoring/restore_teams.c	\
                 					server/create/create_team.c			\
                 					server/create/create_channel.c		\
                 					server/create/errors.c		\

SRC_SERVER_MAIN =	server/main.c \
				$(SRC_SERVER)

OBJ_CLI = $(SRC_CLI_MAIN:%.c=$(BUILD_DIR)/%.o)
SRC_CLI =	client/enjoy_the_client.c	\
            					client/my_str_to_word.c		\
            					client/init_client_stuff.c	\
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
            					client/requests/request_tools.c		\
            					client/event_prints/response_print_wrapper.c	\
            					client/event_prints/creat_rec_wrapper.c		\
            					client/event_prints/list_prints.c		\
            					client/event_prints/info_req_print.c	\
            					client/event_prints/subscribed_and_messages_print.c	\
            					client/event_prints/creat_resp_print.c	\
            					client/my_str_to_special_array.c	\
            					client/very_small_tools.c

SRC_CLI_MAIN =	client/main.c \
				$(SRC_CLI)

all: options server cli

options:
	@echo "  CC       $(CC)"
	@echo "  CFLAGS   $(CFLAGS)"
	@echo "  LDFLAGS  $(LDFLAGS)"

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "  CC       $<"
	@$(CC) $(CFLAGS) -c $< -o $@

server: $(OBJ_SERVER)
	@echo "  BUILD    $(OUTPUT_SERVER)"
	@$(CC) -o $(OUTPUT_SERVER) $(OBJ_SERVER) $(LDFLAGS)

cli: $(OBJ_CLI)
	@echo "  BUILD    $(OUTPUT_CLI)"
	@$(CC) -o $(OUTPUT_CLI) $(OBJ_CLI) $(LDFLAGS)

clean:
	@rm -rf build

fclean: clean
	@echo "  RM       $(OUTPUT_SERVER)"
	@rm -f $(OUTPUT_SERVER)
	@echo "  RM       $(OUTPUT_CLI)"
	@rm -f $(OUTPUT_CLI)

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

.PHONY: all server cli clean fclean re
