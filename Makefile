GREEN = \033[1;32m
RED = \033[1;31m
DEFAULT = \033[0m

NAME				=	pipex
ARCHIVE_NAME		=	pipex.a

CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror
AR					=	ar rcs
RM					=	rm -rf

SRCS				=	split_pipex.c split_pipex_utils.c free.c \
						error_handling.c pipex_utils.c
SRCS_PATH			=	srcs/

BONUS_SRCS			=	$(SRCS) pipex_bonus_utils.c pipex_files.c \
						free_bonus.c
BONUS_SRCS_PATH		=	srcs_bonus/

MAIN				=	$(SRCS_PATH)pipex.c
BONUS_MAIN			=	$(BONUS_SRCS_PATH)pipex_bonus.c

OBJ_DIR				=	objects
OBJS				=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS			=	$(BONUS_SRCS:%.c=$(OBJ_DIR)/%.o)
ALL_OBJS			=	objects/*.o


LIBFT_PATH			=	libft
LIBFT				=	$(LIBFT_PATH)/libft.a

GNL_PATH			=	get_next_line
GNL					=	$(GNL_PATH)/get_next_line.a

$(OBJ_DIR)/%.o:		$(SRCS_PATH)%.c
					@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o:		$(BONUS_SRCS_PATH)%.c
					@$(CC) $(CFLAGS) -c $< -o $@

all:				$(NAME)

$(NAME):			$(OBJ_DIR) $(OBJS) $(LIBFT) $(ARCHIVE_NAME)
					@$(CC) $(CFLAGS) $(MAIN) $(ALL_OBJS) -o $(NAME)
					@echo "$(GREEN) $(NAME) executable created!$(DEFAULT)"
					@if norminette | grep -q -v "OK!"; then \
						norminette; echo "$(RED) Norminette has errors!$(DEFAULT)"; \
					else \
						echo "$(GREEN) Norminette OK!!$(DEFAULT)"; \
					fi

bonus:				$(OBJ_DIR) $(OBJS) $(BONUS_OBJS) $(LIBFT) $(GNL) $(ARCHIVE_NAME)
					@$(CC) $(CFLAGS) $(BONUS_MAIN) $(ALL_OBJS) -o $(NAME)
					@echo "$(GREEN) $(NAME) bonus executable created!$(DEFAULT)"

$(ARCHIVE_NAME):
					@${AR} ${ARCHIVE_NAME} ${ALL_OBJS}
					@echo "$(GREEN) Arquive for pipex created!$(DEFAULT)"

$(LIBFT):
					@make -s -C $(LIBFT_PATH) all
					@echo "$(GREEN) Arquive for libft created!$(DEFAULT)"

$(GNL):
					@make -s -C $(GNL_PATH) all
					@echo "$(GREEN) Arquive for get_next_line created!$(DEFAULT)"

$(OBJ_DIR):
					@mkdir -p $(OBJ_DIR)
					@echo "$(GREEN) $(OBJ_DIR) directory created!$(DEFAULT)"

clean:
					@$(RM) $(OBJ_DIR)
					@echo "$(RED) All objects and objects diretory removed!$(DEFAULT)"

fclean:				clean
					@$(RM) $(ARCHIVE_NAME)
					@$(RM) $(NAME)
					@$(RM) $(LIBFT)
					@$(RM) $(GNL)
					@echo "$(RED) All arquives and executables removed!$(DEFAULT)"

re:					fclean all


.PHONY:				all bonus clean fclean re bonus