# Compiler and flags
CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -g -MMD -MP
RM					=	rm -rf
MFLAGS				=	--no-print-directory -C
# Name of the output library
NAME 				=	libft.a

# Directories and paths
INCLUDE_DIRS		=	./include \
VPATH				=	./src \

# Source files
SRC					= 	ft_isalpha.c ft_isdigit.c ft_isalnum.c \
						ft_isascii.c ft_isprint.c \
						\
						ft_memset.c ft_bzero.c ft_memcpy.c \
						ft_memmove.c ft_memchr.c ft_memcmp.c \
						ft_calloc.c \
						\
						ft_strlen.c ft_strlcpy.c ft_strlcat.c \
						ft_strchr.c ft_strrchr.c ft_strncmp.c  ft_strnstr.c \
						ft_atoi.c  ft_strdup.c ft_substr.c \
						ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
						ft_strmapi.c ft_striteri.c \
						ft_atoier.c ft_parrlen.c ft_parrjoin.c ft_parrclean.c ft_strcmp.c \
						ft_toupper.c ft_tolower.c \
						\
						ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c \
						ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c \
						ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c \
						\
						ft_get_next_liner.c \
						ft_putchar_fd.c ft_putstr_fd.c \
						ft_putendl_fd.c ft_putnbr_fd.c \
						ft_printf.c ft_print_alfa.c ft_print_numeric.c \

# Object and dep files
OBJ 				=	$(SRC:%.c=obj/%.o)
DEP 				= 	$(SRC:%.c=dep/%.d)
INCLUDE				=	$(addprefix -I, $(INCLUDE_DIRS))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "$(GREEN)$(NAME) has been build.$(RESET)"

# Object files
obj/%.o: src/%.c | objdir depdir
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ && echo "$(YELLOW)Compiling $(notdir $<)$(RESET)"

# Create obj directory
objdir:
	@mkdir -p obj

# Create dep directory
depdir:
	@mkdir -p dep

clean:
	@$(RM) obj
	@$(RM) dep
	@echo "$(YELLOW)Removing lib objs and deps...$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) has been removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re
.DEFAULT_GOAL := all

# Include the dependency files
-include $(DEP)

# set colors
RED					= 	\033[0;31m
GREEN				= 	\033[0;32m
YELLOW				= 	\033[0;33m
RESET				= 	\033[0m