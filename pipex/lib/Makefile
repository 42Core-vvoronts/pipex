# Compiler and flags
CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -g -MMD -MP
RM					=	rm -rf
MFLAGS				=	-C
# Name of the output library
NAME 				=	libft.a

# Directories and paths
INCLUDE_DIRS		=	./include
VPATH				=	./src:
INCLUDE				=	$(addprefix -I, $(INCLUDE_DIRS))

# Source files
SRC					= 	ft_isalpha.c ft_isdigit.c ft_isalnum.c \
						ft_isascii.c ft_isprint.c ft_strlen.c \
						ft_memset.c ft_bzero.c ft_memcpy.c \
						ft_memmove.c ft_strlcpy.c ft_strlcat.c \
						ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
						ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
						ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
						ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
						ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
						ft_putendl_fd.c ft_putnbr_fd.c \
						ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c \
						ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c \
						ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c \
						ft_atoier.c ft_parrlen.c ft_parrjoin.c ft_parrclean.c ft_strcmp.c \
						ft_get_next_liner.c \
						ft_printf.c \
						ft_print_alfa.c \
						ft_print_numeric.c

# Object and dep files
OBJ := $(SRC:%.c=obj/%.o)
DEP = $(OBJ:obj/%.o=dep/%.d)

all: $(NAME)

# Rule to compile source files into object files
obj/%.o: src/%.c | dep obj
	@$(CC) $(CFLAGS) -I./include -MMD -MF dep/$(@:obj/%.o=%.d) -c $< -o $@

# Create obj directory if it doesn't exist
obj:
	@mkdir -p obj

# Create dep directory if it doesn't exist
dep:
	@mkdir -p dep

# Rule to create the library from object files
$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

# Rule to clean object files
clean:
	@$(RM) $(OBJ)

# Rule to clean object files and the library
fclean:	clean
	@$(RM) $(NAME)

# Rule to rebuild everything
re:	fclean all

# Phony targets
.PHONY: all clean fclean re
# Default goal
.DEFAULT_GOAL := all
# Include dependency files
-include $(DEP)