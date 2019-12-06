# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: awehlbur <awehlbur@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/05 14:49:04 by awehlbur       #+#    #+#                 #
#    Updated: 2019/12/06 12:58:39 by fhignett      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include makefilesrc/var.mk
include makefilesrc/src.mk

.PHONY: all libft clean fclean re

all: $(ASM) $(COREWAR)

$(LIBFT_PATH)libft.a:
	@make -C $(LIBFT_PATH)

$(ASM_OBJS_PATH)%.o: $(ASM_PATH)%.c $(ASM_HEADERS) $(LIBFT_PATH)libft.a
	@mkdir -p $(OBJS_PATH)
	@mkdir -p $(ASM_OBJS_PATH)
	@$(CC) $(FLAGS) $(INCLUDES) $(LIBFT_INCLUDES) -o $@ -c $<
	@echo "$(PLUS) $@"

$(CORE_OBJS_PATH)%.o: $(CORE_PATH)%.c $(CORE_HEADERS) $(LIBFT_PATH)libft.a
	@mkdir -p $(OBJS_PATH)
	@mkdir -p $(CORE_OBJS_PATH)
	@$(CC) $(FLAGS) $(INCLUDES) $(LIBFT_INCLUDES) -o $@ -c $<
	@echo "$(PLUS) $@"

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
	@rm -fv $(LIBFT)

re:
	@$(MAKE) fclean
	@$(MAKE) all
