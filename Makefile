# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: awehlbur <awehlbur@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/05 14:49:04 by awehlbur       #+#    #+#                 #
#    Updated: 2019/11/05 17:12:08 by awehlbur      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# ========== Colours= ========== #


# ========== Editable ========== #
ASM				= asm
COREWAR			= corewar

# ========== Standard ========== #
CC				= gcc
FLAGS			= # -g -Wall -Wextra -Werror #

# =========== Files ============ #
ASM_SRCS_FILES		=	op.c main.c compile.c

CORE_SRCS_FILES		=	op.c main.c

ASM_HEADERS_FILES	=	op.h

CORE_HEADERS_FILES	=	op.h

# ========== Sources =========== #
ASM_PATH		= ASM_S/
CORE_PATH		= VM_S/
ASM_SRCS			= $(addprefix $(ASM_PATH), $(ASM_SRCS_FILES))
CORE_SRCS			= $(addprefix $(CORE_PATH), $(CORE_SRCS_FILES))

# ========== Objects =========== #
OBJS_PATH		= objects/
ASM_OBJS_PATH	= objects/asm/
CORE_OBJS_PATH	= objects/corewar/
ASM_OBJS			= $(addprefix $(ASM_OBJS_PATH), $(ASM_SRCS_FILES:.c=.o))
CORE_OBJS 			= $(addprefix $(CORE_OBJS_PATH), $(CORE_SRCS_FILES:.c=.o))

# ========== Includes ========== #
INCLUDES_PATH	= includes/
INCLUDES		= -I $(INCLUDES_PATH)
ASM_HEADERS			= $(addprefix $(INCLUDES_PATH), $(ASM_HEADERS_FILES))
CORE_HEADERS		= $(addprefix $(INCLUDES_PATH), $(CORE_HEADERS_FILES))

# ========== Libraries ========= #
LIBFT_PATH		= libft/
LIBFT_INCLUDES	= -I libft/includes
LIBFT			= -L $(LIBFT_PATH) -lft

.PHONY: all libft clean fclean re

all: libft $(ASM) $(COREWAR)

libft:
	@make -C $(LIBFT_PATH)

$(ASM_OBJS_PATH)%.o: $(ASM_PATH)%.c $(ASM_HEADERS) $(LIBFT_PATH)libft.a
	@mkdir -p $(OBJS_PATH)
	@mkdir -p $(ASM_OBJS_PATH)
	@$(CC) $(FLAGS) $(INCLUDES) $(LIBFT_INCLUDES) -o $@ -c $<

$(CORE_OBJS_PATH)%.o: $(CORE_PATH)%.c $(CORE_HEADERS) $(LIBFT_PATH)libft.a
	@mkdir -p $(OBJS_PATH)
	@mkdir -p $(CORE_OBJS_PATH)
	@$(CC) $(FLAGS) $(INCLUDES) $(LIBFT_INCLUDES) -o $@ -c $<

$(ASM): $(ASM_OBJS)
	@$(CC) $(FLAGS) $(LIBFT) $(ASM_OBJS) -o $@
	@echo Assembler compiled

$(COREWAR): $(CORE_OBJS)
	@$(CC) $(FLAGS) $(LIBFT) $(CORE_OBJS) -o $@
	@echo "Virtual Machine compiled"

clean:
	@make -C $(LIBFT_PATH) clean
	@rm -fv $(ASM_OBJS) $(CORE_OBJS)
	@rm -rf $(OBJS_PATH)

fclean: clean
	@rm -fv $(ASM) $(COREWAR)

re: fclean all
