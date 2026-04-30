# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miouali <miouali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/07 11:04:43 by miouali           #+#    #+#              #
#    Updated: 2026/04/30 11:52:12 by miouali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

DEF_COLOR = \033[0;39m
CYAN    = \033[0;96m
GREEN = \033[0;92m
PURPLE  = \033[0;95m
YELLOW  = \033[0;93m
RED     = \033[0;91m
RESET   = \033[0m

ERR_LOG = .errors.log

CC = cc
CFLAGS = -O3 -Wall -Wextra -Werror -I includes #-std=c99
DFLAGS_COMMON = -g -Wshadow -fno-omit-frame-pointer

#ASan + UBSan
DFLAGS_ASAN = $(DFLAGS_COMMON) \
			-fsanitize=address,undefined \
			-fno-sanitize-recover=all

#TSan
DFLAGS_TSAN = $(DFLAGS_COMMON) \
			-fsanitize=thread

#Dossiers
SRCS_DIR = srcs/
OBJS_DIR = objs/
HEADER_DIR = includes/

SRCS_PHILO = main.c prog_usage.c parser.c routine.c body_guard.c exit.c utils_0.c

ALL_SRCS = $(addprefix $(SRCS_DIR), $(SRCS_PHILO))

OBJS = $(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(ALL_SRCS))

HEADER = $(HEADER_DIR)philo.h

RM = rm -rf

all: header start_timer $(NAME) end_timer

header:
	@printf "$(YELLOW) Démarrage de la compilation de Philosophers...$(RESET)\n"

start_timer:
	$(eval START_TIME := $(shell date +%s))

debug debug_asan debug_tsan: \
	CC = gcc
    CFLAGS = -O0 -Wall -Werror -Wextra -I includes -g

debug: DFLAGS = $(DFLAGS_COMMON)
debug: header start_timer $(OBJS) end_timer
	@$(CC) $(OBJS) $(DFLAGS) -o $(NAME)
	@printf "$(GREEN) Philosophers debug ready !$(DEF_COLOR)"

debug_asan: DFLAGS = $(DFLAGS_ASAN)
debug_asan: header start_timer $(OBJS) end_timer
	@$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) -o $(NAME)
	@printf "$(GREEN) Philosophers debug [ASan+UBSan] ready !$(DEF_COLOR)\n"

debug_tsan: DFLAGS = $(DFLAGS_TSAN)
debug_tsan: header start_timer $(OBJS) end_timer
	@$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) -o $(NAME)
	@printf "$(YELLOW) Philosophers debug [TSan] ready ! $(DEF_COLOR)\n"

$(NAME): $(OBJS)
	@printf "\n\n$(CYAN)██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗\n"
	@sleep 0.1
	@printf "██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝\n"
	@sleep 0.1
	@printf "██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗\n"
	@sleep 0.1
	@printf "██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║\n"
	@sleep 0.1
	@printf "██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║\n"
	@sleep 0.1
	@printf "╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝$(DEF_COLOR)\n"
	@$(CC) $(OBJS) -o $(NAME)
	@printf "\n\n$(GREEN) Philo is ready to be used !$(DEF_COLOR)\n"


# Variables pour la barre
TOTAL_FILES := $(words $(ALL_SRCS))
CURRENT_FILE := 0

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(eval CURRENT_FILE=$(shell printf $$(($(CURRENT_FILE) + 1))))
	@$(eval PERCENT=$(shell printf $$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES)))))
	@printf "\r$(CYAN)🛠️  Compiling Philosophers... [%-20s] %d%%" \
		"$(shell printf '#%.0s' $$(seq 1 $$(($(PERCENT) / 5))))" $(PERCENT)
	@$(CC) $(CFLAGS) -c $< -o $@ 2> .temp_err || \
		(printf "\n$(PURPLE)❌ Erreur dans $< :$(RESET)\n" && cat .temp_err >> $(ERR_LOG) && cat .temp_err && rm -f .temp_err)


end_timer:
	@$(eval END_TIME := $(shell date +%s))
	@$(eval DURATION := $(shell printf $$(($(END_TIME) - $(START_TIME)))))
	@$(eval ERRORS := $(shell if [ -f $(ERR_LOG) ]; then grep -c "error:" $(ERR_LOG); else printf 0; fi))
	@printf "\n%s\n" "--------------------------------------------------"
	@if [ $(ERRORS) -eq 0 ]; then \
		printf "$(GREEN)✅ COMPILATION TERMINÉE !$(RESET)\n"; \
	else \
		printf "$(RED)❌ COMPILATION TERMINÉE AVEC DES ERREURS$(RESET)\n"; \
	fi
	@printf "Temps écoulé : $(DURATION) secondes\n"
	@printf "  Nombre d'erreurs : $(ERRORS)\n"
	@printf "%s\n" "--------------------------------------------------"
	@rm -f $(ERR_LOG)

clean:
	$(RM) $(OBJS_DIR)
	@printf "$(PURPLE) Objects cleaned!$(DEF_COLOR)\n"

fclean: clean
		$(RM) $(NAME)
		$(RM) .temp_err
		@printf "$(PURPLE) $(NAME) deleted!$(DEF_COLOR)\n"

re: fclean all

.PHONY : all clean fclean re debug
