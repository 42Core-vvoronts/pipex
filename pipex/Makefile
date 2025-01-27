# Compilation, flags, commands
CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -Wunreachable-code -g -MMD -MF
MFLAGS				=	--no-print-directory -C
RM					=	rm -rf
# Program name
NAME				=	pipex

# Directories and paths
INCLUDE_DIRS		=	./include \
						./lib/include \
VPATH				=	./src \

LIB					=	./lib/libft.a \

SRC 				=	main.c \
						pipex.c \
						memory.c \
						getenv.c \
						exits.c \

# Objects and dependencies
OBJ					=	$(SRC:%.c=obj/%.o)
DEP					=	$(SRC:%.c=dep/%.d)
INCLUDE				=	$(addprefix -I, $(INCLUDE_DIRS))


# Build all targets
all: lib $(NAME)

# Link object files
$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LIB) -o $@
	@echo "$(GREEN)$(NAME) has been build.$(RESET)"

# Build libraries
lib:
	@make $(MFLAGS) ./lib

# Object files
obj/%.o: src/%.c | objdir depdir
	@$(CC) $(CFLAGS) dep/$(@:obj/%.o=%.d) $(INCLUDE) -c $< -o $@ && echo "$(YELLOW)Compiling: $(notdir $<)$(RESET)"

# Create obj directory
objdir:
	@mkdir -p obj

# Create dep directory
depdir:
	@mkdir -p dep

clean: cleanlib
	@$(RM) obj
	@$(RM) dep
	@echo "$(YELLOW)Removing objects and deps...$(RESET)"
# Clean lib
cleanlib:
	@make clean $(MFLAGS) ./lib
	@echo "$(YELLOW)Cleaning library...$(RESET)"

fclean: clean cleanlib
	@make clean $(MFLAGS) ./lib
	@echo "$(RED)$(LIB) has been removed$(RESET)"
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) has been removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re lib
.DEFAULT_GOAL := all

# Include the dependency files
-include $(DEP)

# set colors
RED					= 	\033[0;31m
GREEN				= 	\033[0;32m
YELLOW				= 	\033[0;33m
RESET				= 	\033[0m