NAME =		philo

CC =		clang
CFLAGS =	-Wall -Wextra -Werror

INCLUDES =	-pthread -I ./includes 

SRC_FILES =	main.c \
			utils.c \
			utils2.c \
			free.c \
			ft_split.c \
			get_arguments.c \
			check_arguments.c \
			check_arguments_2.c \
			initialization.c \
			simulation.c \
			get_time.c \
			routines.c \
			actions_forks.c \
			print_actions.c \
			monitor.c

SRCS = $(addprefix srcs/,$(SRC_FILES))
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo ' '
	@clang $(OBJS) $(INCLUDES) $(CFLAGS) -o $@
	@echo "\033[1;32m\n[OK]\033[0m    \033[1;33mCreating \033[0m $@"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[1;32m[OK]\033[0m    \033[1;33mCompiling\033[0m $(<F)"

clean:
	@$(RM) $(OBJS)
	@echo "\033[1;32m[OK]\033[0m    \033[1;33mDeleting \033[0m object files of minishell\n"


fclean: clean
	@$(RM) $(NAME)
	@echo "\033[1;32m[OK]\033[0m    \033[1;33mDeleting \033[0m $(NAME)\n"

re: fclean all