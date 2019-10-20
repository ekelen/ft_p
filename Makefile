# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/20 14:34:40 by ekelen            #+#    #+#              #
#    Updated: 2019/10/20 14:47:52 by ekelen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET=\033[0m
GREEN=\033[32m

CC = gcc

CFLAGS = -Werror -Wall -Wextra

LIBS = -Llibft -lft

SRCS_DIR = srcs
INC_DIR = inc
OBJS_DIR = objs

INC = -I$(INC_DIR) -Ilibft/inc

SERVER_NAME = server
CLIENT_NAME = client

SERVER_FS_ROOT = ftproot

COMMONS_DIR = commons
SERVER_DIR = server
CLIENT_DIR = client

SERVER_SRC_NAMES += server.c
SERVER_SRC_NAMES += server_socket.c
SERVER_SRC_NAMES += server_listen.c
SERVER_SRC_NAMES += server_handler.c
SERVER_SRC_NAMES += reply.c
SERVER_SRC_NAMES += process_commands.c
SERVER_SRC_NAMES += filesystem.c
SERVER_SRC_NAMES += file_transfert.c
SERVER_SRC_NAMES += control_connection.c
SERVER_SRC_NAMES += exec_builtin.c
SERVER_SRC_NAMES += path.c
SERVER_SRC_NAMES += types.c

CLIENT_SRC_NAMES +=	client_dtp.c
CLIENT_SRC_NAMES +=	client_interface.c
CLIENT_SRC_NAMES +=	client_pi.c
CLIENT_SRC_NAMES +=	client.c
CLIENT_SRC_NAMES +=	parse_cli_cmd.c
CLIENT_SRC_NAMES +=	reply_actions.c
CLIENT_SRC_NAMES +=	client_handler.c
CLIENT_SRC_NAMES +=	replies.c
CLIENT_SRC_NAMES +=	cmd_connection.c
CLIENT_SRC_NAMES +=	cmd_settings.c
CLIENT_SRC_NAMES +=	cmd_transfer.c
CLIENT_SRC_NAMES +=	cmd_fs.c
CLIENT_SRC_NAMES +=	dtp_actions.c
CLIENT_SRC_NAMES +=	send_command.c

COMMONS_SRC_NAMES += errors.c
COMMONS_SRC_NAMES += builtins.c
COMMONS_SRC_NAMES += ascii.c
COMMONS_SRC_NAMES += utils_str.c
COMMONS_SRC_NAMES += files.c
COMMONS_SRC_NAMES += inputs.c
COMMONS_SRC_NAMES += ascii_data.c
COMMONS_SRC_NAMES += data_utils.c

SERVER_SRCS = $(addprefix $(SRCS_DIR)/$(SERVER_DIR)/, $(SERVER_SRC_NAMES))
CLIENT_SRCS = $(addprefix $(SRCS_DIR)/$(CLIENT_DIR)/, $(CLIENT_SRC_NAMES))
COMMON_SRCS = $(addprefix $(SRCS_DIR)/$(COMMONS_DIR), $(COMMONS_SRC_NAMES))

SERVER_OBJ_NAMES = $(SERVER_SRC_NAMES:.c=.o)
CLIENT_OBJ_NAMES = $(CLIENT_SRC_NAMES:.c=.o)
COMMON_OBJ_NAMES = $(COMMONS_SRC_NAMES:.c=.o)

SERVER_OBJS_DIR = $(OBJS_DIR)/$(SERVER_DIR)
CLIENT_OBJS_DIR = $(OBJS_DIR)/$(CLIENT_DIR)
COMMON_OBJS_DIR = $(OBJS_DIR)/$(COMMONS_DIR)

SERVER_OBJS = $(addprefix $(SERVER_OBJS_DIR)/, $(SERVER_OBJ_NAMES))
CLIENT_OBJS = $(addprefix $(CLIENT_OBJS_DIR)/, $(CLIENT_OBJ_NAMES))
COMMON_OBJS = $(addprefix $(COMMON_OBJS_DIR)/, $(COMMON_OBJ_NAMES))

all: libft/libft.a $(SERVER_NAME) $(CLIENT_NAME)

libft/libft.a:
	@make -C libft/

$(SERVER_NAME): $(SERVER_OBJS) $(COMMON_OBJS) libft/libft.a
	@$(CC) -o $@ $^ $(LIBS)
	@echo "[$(GREEN)server compiled!$(RESET)]"

$(CLIENT_NAME): $(CLIENT_OBJS) $(COMMON_OBJS) libft/libft.a
	@$(CC) -o $@ $^ $(LIBS)
	@echo "[$(GREEN)client compiled!$(RESET)]"

$(SERVER_OBJS_DIR)/%.o: $(SRCS_DIR)/$(SERVER_DIR)/%.c
	@mkdir -p $(SERVER_OBJS_DIR)
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $^

$(CLIENT_OBJS_DIR)/%.o: $(SRCS_DIR)/$(CLIENT_DIR)/%.c
	@mkdir -p $(CLIENT_OBJS_DIR)
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $^

$(COMMON_OBJS_DIR)/%.o: $(SRCS_DIR)/$(COMMONS_DIR)/%.c
	@mkdir -p $(COMMON_OBJS_DIR)
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $^

clean:
	@echo "make clean -C libft/"
	@make clean -C libft/
	@rm -rf $(OBJS_DIR)
	@echo "[$(GREEN)object files removed!$(RESET)]"

fclean: clean
	@echo "make fclean -C libft/"
	@make fclean -C libft/
	@rm -f $(SERVER_NAME)
	@rm -f $(CLIENT_NAME)
	@rm -rf $(SERVER_FS_ROOT)
	@echo "[$(GREEN)server, server fs, and client programs removed!$(RESET)]"

re: fclean all