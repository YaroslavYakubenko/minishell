NAME 			= minishell
HDRDIR			= incl/

EXECDIR			= ${SRCSDIR}execution/

PARSEDIR		= ${SRCSDIR}parse/

UTILDIR			= ${SRCSDIR}utils/

SUCCES			= @echo "minishell compiled successfully"

SRCSDIR			= srcs/
SRCS			= ${SRCSDIR}main.c \
					${EXECDIR}execute.c \
					${EXECDIR}ft_get_path_own.c \
					${EXECDIR}symbols.c \
					${EXECDIR}cd.c \
					${EXECDIR}export.c \
					${EXECDIR}export_ults.c \
					${EXECDIR}build_in.c \
					${EXECDIR}ft_start.c \
					${PARSEDIR}parse_env.c \
					${PARSEDIR}parse_dollar.c \
				  	${PARSEDIR}parse_token.c \
				  	${UTILDIR}utils.c \
				  	${PARSEDIR}parse_quotes.c \
					${PARSEDIR}parse_spaces.c \
					${PARSEDIR}checks.c \

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