# Compilation and flags
CC					=	cc
RM					=	rm -rf
CFLAGS				=	-Wall -Wextra -Werror -g -MMD -MP -MF
MFLAGS				=	-C
# Program name
NAME				=	pipex

# Directories and paths
INCLUDE_DIRS		=	./include \
						./lib/include

VPATH				=	./src/

INCLUDE				=	$(addprefix -I, $(INCLUDE_DIRS))

SRC 				=	pipex.c \

LIB					=	./lib/libft.a \

OBJ					=	$(SRC:%.c=obj/$(NAME)/%.o)

DEP					=	$(SRC:%.c=dep/%.d) $(BONUS_SRC:%.c=dep/%.d)


all: $(NAME)
	@echo "$(GREEN)Making $(NAME)...$(RESET)"

$(NAME): $(OBJ) libs
	@$(CC) $(OBJ) $(LIB) -o $@

libs:
	@make $(MFLAGS) ./lib

# Object files
obj/$(NAME)/%.o: %.c | depdir objdir
	@$(CC) $(CFLAGS) dep/$(@:obj/%.o=%.d) $(INCLUDE) -c $< -o $@

objdir:
	@mkdir -p obj
	@mkdir -p obj/$(NAME)

depdir:
	@mkdir -p dep
	@mkdir -p dep/$(NAME)

clean: cleanlib
	@echo "$(YELLOW)Removing objects and deps...$(RESET)"
	@$(RM) obj/$(NAME)
	@$(RM) dep/$(NAME)
# Clean lib
cleanlib:
	@echo "$(YELLOW)Cleaning library...$(RESET)"
	@make clean $(MFLAGS) ./lib

fclean: clean cleanlib
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) has been removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus
.DEFAULT_GOAL := all

# Include the dependency files
-include $(DEP)

# set colors
RED					= 	\033[0;31m
GREEN				= 	\033[0;32m
YELLOW				= 	\033[0;33m
RESET				= 	\033[0m