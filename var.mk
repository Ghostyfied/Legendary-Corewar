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
INCLUDES		= -I $(INCLUDES_PATH)
ASM_HEADERS		= $(addprefix $(INCLUDES_PATH), $(ASM_HEADERS_FILES))
CORE_HEADERS	= $(addprefix $(INCLUDES_PATH), $(CORE_HEADERS_FILES))

# ========== Libraries ========= #
LIBFT_PATH		= libft/
LIBFT_INCLUDES	= -I libft/includes
LIBFT			= -L $(LIBFT_PATH) -lft