# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: awehlbur <awehlbur@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/05 14:49:04 by awehlbur       #+#    #+#                 #
#    Updated: 2020/01/09 14:14:59 by fhignett      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include makefilesrc/var.mk
include makefilesrc/src.mk

.PHONY: all libft clean fclean re

all: $(ASM) $(COREWAR) $(DISASSEMBLER)

$(LIBFT_PATH)libft.a: FORCE
	@make -C $(LIBFT_PATH)

$(COMM_OBJS_PATH)%.o: $(COMM_PATH)%.c $(COMM_HEADERS) $(LIBFT_PATH)libft.a
	@mkdir -p $(OBJS_PATH)
	@mkdir -p $(COMM_OBJS_PATH)
	@$(CC) $(FLAGS) $(INCLUDES) $(LIBFT_INCLUDES) -o $@ -c $<
	@echo "$(PLUS) $@"

$(ASM_OBJS_PATH)%.o: $(ASM_PATH)%.c $(ASM_HEADERS) $(LIBFT_PATH)libft.a
	@mkdir -p $(OBJS_PATH)
	@mkdir -p $(ASM_OBJS_PATH)
	@$(CC) $(FLAGS) $(INCLUDES) $(LIBFT_INCLUDES) -o $@ -c $<
	@echo "$(PLUS) $@"

$(CORE_OBJS_PATH)%.o: $(CORE_PATH)%.c $(CORE_HEADERS) $(LIBFT_PATH)libft.a
	@mkdir -p $(OBJS_PATH)
	@mkdir -p $(CORE_OBJS_PATH)
	@mkdir -p $(VIS_OBJS_PATH)
	@$(CC) $(FLAGS) $(INCLUDES) $(LIBFT_INCLUDES) -o $@ -c $<
	@echo "$(PLUS) $@"

$(DIS_OBJS_PATH)%.o: $(DIS_PATH)%.c $(DIS_HEADERS) $(LIBFT_PATH)libft.a
	@mkdir -p $(OBJS_PATH)
	@mkdir -p $(DIS_OBJS_PATH)
	@$(CC) $(FLAGS) $(INCLUDES) $(LIBFT_INCLUDES) -o $@ -c $<
	@echo "$(PLUS) $@"

$(ASM): $(COMM_OBJS) $(ASM_OBJS) $(ASM_HEADERS)
	@$(CC) $(FLAGS) $(LIBFT) $(COMM_OBJS) $(ASM_OBJS) -o $@
	@echo Assembler compiled

$(COREWAR): $(COMM_OBJS) $(CORE_OBJS) $(CORE_HEADERS)
	@$(CC) $(FLAGS) -lncurses $(LIBFT) $(COMM_OBJS) $(CORE_OBJS) -o $@
	@echo Virtual Machine compiled

$(DISASSEMBLER): $(COMM_OBJS) $(DIS_OBJS) $(DIS_HEADERS)
	@$(CC) $(FLAGS) $(LIBFT) $(COMM_OBJS) $(DIS_OBJS) -o $@
	@echo Disassembler compiled

clean:
	@make -C $(LIBFT_PATH) clean
	@rm -fv $(ASM_OBJS) $(CORE_OBJS) $(DISASSEMBLER)
	@rm -rf $(OBJS_PATH)

fclean: clean
	@rm -fv $(ASM) $(COREWAR) $(DISASSEMBLER)
	@rm -fv $(LIBFT)

re:
	@$(MAKE) fclean
	@$(MAKE) all

FORCE:
