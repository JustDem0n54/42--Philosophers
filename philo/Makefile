NAME = philo

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

CFLAGS	= -Wall -Werror -Wextra -ggdb

SOURCES = ./philo.c ./utils.c

SRCDIR = src
OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

all: ${NAME}

${NAME}:	${OBJS}
	@echo "${YELLOW}Compiling program...${RESET}"
	@cc ${CFLAGS} ${OBJS} -o ${NAME}
	@echo "${GREEN}Compilation success !${RESET}"


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@cc $(CFLAGS) -c $< -o $@

clean:
	@echo "${YELLOW}Cleaning...${RESET}"
	@${RM} -rf ${OBJDIR}

fclean: clean
	@echo "$(RED)Cleaning all...$(RESET)"
	@rm -f $(NAME) obj

re: fclean all