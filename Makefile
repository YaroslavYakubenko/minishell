NAME 			= minishell
HDRDIR			= incl/

EXECDIR			= ${SRCSDIR}execution/
# EXECSRCS		= ${EXECDIR}executor.c

PARSEDIR		= ${SRCSDIR}parse/
# PARSESRCS		= ${PARSEDIR}ft_input_parse.c \
				  ${PARSEDIR}ft_init_env.c

UTILDIR			= ${SRCSDIR}utils/
# UTILSRCS		= ${UTILDIR}ft_utils.c ft_env_utils.c

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
					${PARSEDIR}parse_env.c \
					${PARSEDIR}parse_dollar.c \
				  	${PARSEDIR}parse_token.c \
				  	${UTILDIR}ft_strlenn.c \
				  	${PARSEDIR}parse_quotes.c \
				#   ${UTILDIR}ft_error_parse_ext.c \
				#   ${UTILDIR}ft_str_utils.c \
				#   ${UTILDIR}ft_utils.c \
				#   ${UTILDIR}ft_init_env.c \
				#   ${UTILDIR}ft_env_utils.c \
				#   ${UTILDIR}ft_path_utils.c

VPATH			= ${SRCSDIR} ${SRCSDIR}parse/ ${SRCSDIR}utils/
OBJS			= $(SRCS:.c=.o)
CFLAGS 			= -Wall -Wextra -Werror -I$(HDRDIR) -g

LIBFTDIR		= libft/
LIBFT			= ${LIBFTDIR}libft.a

ALLOCDIR		= ft_destructor/
ALLOC			= $(ALLOCDIR)ft_alloc.a

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
	@make fclean -sC $(ALLOCDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean $(NAME)

.PHONY:	all clean fclean re