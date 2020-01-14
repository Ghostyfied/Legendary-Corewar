# =========== Files ============ #
COMM_SRCS_FILES		=	op.c \
						swap.c \
						valid.c \
						hex.c \
						code.c \

ASM_SRCS_FILES		=	main.c \
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
						arg.c \

CORE_SRCS_FILES		=	main.c \
						validate_format.c \
						assign_positions.c \
						check_flag_stuff.c \
						check_flag_stuff_helper.c \
						count_and_check_champs.c \
						extra_functions.c \
						read_file.c \
						cursor.c \
						setup_game.c \
						game.c \
						dump.c \
						free.c \
						check_op.c \
						misc.c \
						operations.c \
						operations2.c \
						operations3.c \
						operations4.c \
						$(VIS_SRCS_FILES) \
						debug.c #DELETE ME LATER \

VIS_SRCS_FILES		=	visualizer/visualizer.c \
						visualizer/info.c \
						visualizer/init.c \
						visualizer/misc.c \

DIS_SRCS_FILES		=	main.c \
						decode_code.c \
						read_file.c \
						structs.c \

ASM_HEADERS_FILES	=	communal.h asm.h op.h

CORE_HEADERS_FILES	=	communal.h vm.h visualizer.h op.h

DIS_HEADERS_FILES	=	communal.h dis.h op.h

COMM_HEADERS_FILES	=	communal.h op.h