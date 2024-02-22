NAME				=	pipex

CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror
SANITIZE			=	-g -fsanitize=address,undefined
RANDOM_MALLOC		=	-Xlinker --wrap=malloc
AR					=	ar rcs
RM					=	rm -rf

SRCS				=	split_pipex.c split_pipex_utils.c free.c \
						error_handling.c pipex_utils.c #malloc.c
SRCS_PATH			=	srcs/

BONUS_SRCS			=	pipex_bonus_utils.c pipex_files.c \
						free_bonus.c error_handling_bonus.c
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

TOTAL_SRCS          =   $(words $(SRCS))
TOTAL_BONUS_SRCS    =   $(words $(BONUS_SRCS))
TOTAL_OBJS          =   $(words $(wildcard $(OBJ_DIR)*))
FILES				=	0
BONUS_FILES			=	0

$(OBJ_DIR)/%.o:		$(SRCS_PATH)%.c
					@$(CC) $(CFLAGS) -c $< -o $@ && \
					$(eval FILES=$(shell echo $$(($(FILES) + 1)))) \
					$(call PRINT_PROGRESS,$(TOTAL_SRCS),$(GRN),$(YELLOW)Compiling$(DEFAULT) $@, $(FILES))
					

$(OBJ_DIR)/%.o:		$(BONUS_SRCS_PATH)%.c
					@if [ "$(BONUS_FILES)" -eq "0" ]; then \
        				printf "\033[2F\033[0K]"; \
					fi
					@$(CC) $(CFLAGS) -c $< -o $@ && \
					$(eval BONUS_FILES=$(shell echo $$(($(BONUS_FILES) + 1)))) \
					$(call PRINT_PROGRESS,$(TOTAL_BONUS_SRCS),$(GRN),$(YELLOW)Compiling$(DEFAULT) $@, $(BONUS_FILES))

all:				$(NAME)

$(NAME):			$(OBJ_DIR) $(LIBFT) $(GNL) $(OBJS)
					@$(CC) $(CFLAGS) $(MAIN) $(ALL_OBJS) -o $(NAME)
					@echo "\033[2F\033[0K$(CYAN)$(NAME)$(DEFAULT) successfully created\033[E"
					@if norminette | grep -q -v "OK!"; then \
						norminette | grep -v "OK!"; echo "$(RED) Norminette has errors!$(DEFAULT)"; \
					else \
						echo "Norminette$(GRN) OK!!$(DEFAULT)"; \
					fi
					$(eval FILES=0)

sanitize:			$(OBJ_DIR) $(LIBFT) $(GNL) $(OBJS)
					@$(CC) $(CFLAGS) $(SANITIZE) $(MAIN) $(ALL_OBJS) -o $(NAME)
					@echo "\033[2F\033[0K$(CYAN)$(NAME)$(DEFAULT) successfully created\033[E"

random_m:			$(OBJ_DIR) $(LIBFT) $(GNL) $(OBJS)
					@$(CC) $(CFLAGS) $(SANITIZE) $(RANDOM_MALLOC) $(MAIN) $(ALL_OBJS) -o $(NAME)
					@echo "\033[2F\033[0K$(CYAN)$(NAME)$(DEFAULT) successfully created\033[E"

bonus:				$(OBJ_DIR) $(LIBFT) $(GNL) $(OBJS) $(BONUS_OBJS)
					@$(CC) $(CFLAGS) $(BONUS_MAIN) $(ALL_OBJS) -o $(NAME)
					@echo "\033[2F\033[0K$(CYAN)$(NAME)$(DEFAULT) bonus successfully created\033[E"

sanitize_b:			$(OBJ_DIR) $(LIBFT) $(GNL) $(OBJS) $(BONUS_OBJS)
					@$(CC) $(CFLAGS) $(SANITIZE) $(BONUS_MAIN) $(ALL_OBJS) -o $(NAME)
					@echo "\033[2F\033[0K$(CYAN)$(NAME)$(DEFAULT) successfully created\033[E"

random_m_b:			$(OBJ_DIR) $(LIBFT) $(GNL) $(OBJS) $(BONUS_OBJS)
					@$(CC) $(CFLAGS) $(SANITIZE) $(RANDOM_MALLOC) $(BONUS_MAIN) $(ALL_OBJS) -o $(NAME)
					@echo "\033[2F\033[0K$(CYAN)$(NAME)$(DEFAULT) successfully created\033[E"

$(LIBFT):
					@make -s -C $(LIBFT_PATH) all

$(GNL):
					@make -s -C $(GNL_PATH) all

$(OBJ_DIR):
					@mkdir -p $(OBJ_DIR)

clean:
					@$(foreach file,$(wildcard $(OBJ_DIR)*), \
						$(eval FILES=$(shell echo $$(($(FILES) + 1)))) \
						$(call PRINT_PROGRESS,$(TOTAL_OBJS),$(RED),$(YELLOW)Deleting$(DEFAULT) $(file), $(FILES)); \
						$(RM) $(file); \
					)
					@$(RM) $(OBJ_DIR)
					$(eval FILES=0)

fclean:				clean
					@$(RM) $(OBJ_DIR)
					@echo "$(PURPLE)$(OBJ_DIR)$(DEFAULT) deleted"
					@$(RM) $(LIBFT)
					@echo "$(PURPLE)$(LIBFT)$(DEFAULT) deleted"
					@$(RM) $(GNL)
					@echo "$(PURPLE)$(GNL)$(DEFAULT) deleted"
					@$(RM) $(FT_PRINTF)
					@$(RM) $(NAME)
					@echo "$(PURPLE)$(NAME)$(DEFAULT) deleted"

re:					fclean all


.PHONY:				all bonus clean fclean re bonus

define PRINT_PROGRESS
    if [ "$(4)" -eq "1" ]; then \
        printf "\033[0K$(3)\n["; \
    else \
        printf "\033[0K\033[1F\033[0K$(3)\n["; \
    fi
    @for i in `seq 1 $(shell expr $(4) \* 70 / $(1))`; do \
        printf "$(2)=\033[0m"; \
    done
    @for i in `seq 1 $(shell expr 70 - $(4) \* 70 / $(1))`; do \
        printf " "; \
    done
    @printf "] $(shell echo $$(($(4) * 100 / $(1))))%%"
	if [ "$(4)" -eq "$(1)" ]; then \
        printf "\n"; \
	fi
endef

CYAN				=	\033[36m
PURPLE				=	\033[35m
YELLOW				=	\033[33m
GRN					=	\033[32m
RED					=	\033[31m
DEFAULT				=	\033[0m