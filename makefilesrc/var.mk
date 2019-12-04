# ========== Colours= ========== #
GREEN = $(shell printf "\e[38;5;10m")
WHITE = $(shell printf "\e[39m")
PLUS = $(GREEN)+$(WHITE)

# ========== Editable ========== #
ASM				= asm
COREWAR			= corewar

# ========== Flags ========== #
FLAGS			= # -g -Wall -Wextra -Werror #

# ========== Sources =========== #
ASM_PATH		= ASM_S/
CORE_PATH		= VM_S/
ASM_SRCS		= $(addprefix $(ASM_PATH), $(ASM_SRCS_FILES))
CORE_SRCS		= $(addprefix $(CORE_PATH), $(CORE_SRCS_FILES))

# ========== Objects =========== #
OBJS_PATH		= .objects/
ASM_OBJS_PATH	= .objects/asm/
CORE_OBJS_PATH	= .objects/corewar/
ASM_OBJS		= $(addprefix $(ASM_OBJS_PATH), $(ASM_SRCS_FILES:.c=.o))
CORE_OBJS 		= $(addprefix $(CORE_OBJS_PATH), $(CORE_SRCS_FILES:.c=.o))

# ========== Includes ========== #
INCLUDES_PATH	= includes/
INCLUDES_LIBFT	= libft/
INCLUDES		= -I $(INCLUDES_PATH) -I $(INCLUDES_LIBFT)
ASM_HEADERS		= $(addprefix $(INCLUDES_PATH), $(ASM_HEADERS_FILES))
CORE_HEADERS	= $(addprefix $(INCLUDES_PATH), $(CORE_HEADERS_FILES))

# ========== Libraries ========= #
LIBFT_PATH		= libft/
LIBFT_INCLUDES	= -I libft/includes
LIBFT			= -L $(LIBFT_PATH) -lft