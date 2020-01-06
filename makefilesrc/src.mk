# =========== Files ============ #
ASM_SRCS_FILES		=	op.c \
						main.c \
						read_file.c \
						parse.c \
						structs.c \
						calculate_size.c \
						parse_nc.c \
						make_exc_code.c \
						trim.c \
						hex.c \
						misc.c \
						free_shizzl.c \
						arg.c


CORE_SRCS_FILES		=	main.c \
						validate_format.c \
						assign_positions.c \
						check_flag_stuff.c \
						count_and_check_champs.c \
						extra_functions.c \
						read_file.c \
						op.c \
						startvm.c \
						cursor.c \
						setup_game.c \
						game.c \
						dump.c \
						free.c \
						debug.c #DELETE ME LATER

DIS_SRCS_FILES		=	main.c \
						decode_code.c \
						read_file.c \
						structs.c \
						op.c

ASM_HEADERS_FILES	=	op.h asm.h

CORE_HEADERS_FILES	=	op.h vm.h

DIS_HEADERS_FILES	=	op.h dis.h