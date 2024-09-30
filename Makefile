NAME 			= minishell
HDRDIR			= incl/

GET_NEXT_LINEDIR= get_next_line/

EXECDIR			= ${SRCSDIR}execution/

PARSEDIR		= ${SRCSDIR}parse/

UTILDIR			= ${SRCSDIR}utils/

GREEN			= \033[0;92m
COLOR			= \033[0m

SUCCES			= @echo "$(GREEN)minishell compiled successfully$(COLOR)"

SRCSDIR			= srcs/
SRCS			= ${SRCSDIR}main.c \
					${EXECDIR}execute.c \
					${EXECDIR}ft_get_path_own.c \
					${EXECDIR}symbols.c \
					${EXECDIR}cd.c \
					${EXECDIR}export.c \
					${EXECDIR}export_ults.c \
					${EXECDIR}ft_start.c \
					${EXECDIR}ft_exit.c \
					${GET_NEXT_LINEDIR}get_next_line.c \
					${GET_NEXT_LINEDIR}get_next_line_utils.c \
					${PARSEDIR}parse_env.c \
					${PARSEDIR}parse_dollar.c \
				  	${UTILDIR}utils.c \
				  	${PARSEDIR}parse_quotes.c \
					${PARSEDIR}parse_spaces.c \
					${PARSEDIR}checks.c \
					${UTILDIR}signals.c \
					${PARSEDIR}parse_input.c \

VPATH			= ${SRCSDIR} ${SRCSDIR}parse/ ${SRCSDIR}utils/
OBJS			= $(SRCS:.c=.o)
CFLAGS 			= -Wall -Wextra -Werror -I$(HDRDIR) -g

LIBFTDIR		= libft/
LIBFT			= ${LIBFTDIR}libft.a


CC 				= @cc

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(ALLOC)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(ALLOC) -o $(NAME) -lreadline
	$(SUCCES)

$(LIBFT):
	@make -sC $(LIBFTDIR)
	@make bonus -sC $(LIBFTDIR)

$(ALLOC):
	@make -sC $(ALLOCDIR)

clean:
	@rm -f $(OBJS)
	@make fclean -sC $(LIBFTDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean $(NAME)

.PHONY:	all clean fclean re