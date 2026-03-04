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
CFLAGS =  -O3 -Wall -Wextra -Werror -I includes
DFLAGS = -fsanitize=address -fsanitize=undefined -g -Wshadow -Wunused-function

#Dossiers
SRCS_DIR = srcs/
OBJS_DIR = objs/
HEADER_DIR = includes/

SRCS_PHILO = main.c 

ALL_SRCS = $(addprefix $(SRCS_DIR), $(SRCS_PHILO))

OBJS = $(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(ALL_SRCS))

HEADER = $(HEADER_DIR)philo.h

RM = rm -rf

all: header start_timer $(NAME) end_timer

header:
	@echo "$(YELLOW) Démarrage de la compilation de Philosophers...$(RESET)"

start_timer:
	$(eval START_TIME := $(shell date +%s))

debug: $(MLX_LIB) $(LIBFT_LIB) header start_timer $(OBJS) end_timer
	@$(CC) $(OBJS) $(LDFLAGS) $(DFLAGS) -o $(NAME)
	@echo "$(GREEN) Philosophers debug ready !$(DEF_COLOR)"


$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)
	@echo "\n\n$(GREEN) Philo is ready to be used !$(DEF_COLOR)"


# Variables pour la barre
TOTAL_FILES := $(words $(ALL_SRCS))
CURRENT_FILE := 0

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	@$(eval PERCENT=$(shell echo $$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES)))))
	@printf "\r$(CYAN)🛠️  Compiling Fract-ol... [%-20s] %d%%" \
		"$(shell printf '#%.0s' $$(seq 1 $$(($(PERCENT) / 5))))" $(PERCENT)
	@$(CC) $(CFLAGS) -c $< -o $@ 2> .temp_err || \
		(printf "\n$(PURPLE)❌ Erreur dans $< :$(RESET)\n" && cat .temp_err >> $(ERR_LOG) && cat .temp_err && rm -f .temp_err)


end_timer:
	@$(eval END_TIME := $(shell date +%s))
	@$(eval DURATION := $(shell echo $$(($(END_TIME) - $(START_TIME)))))
	@$(eval ERRORS := $(shell if [ -f $(ERR_LOG) ]; then grep -c "error:" $(ERR_LOG); else echo 0; fi))
	@echo "\n--------------------------------------------------"
	@if [ $(ERRORS) -eq 0 ]; then \
		echo "$(GREEN)✅ COMPILATION TERMINÉE !$(RESET)"; \
	else \
		echo "$(RED)❌ COMPILATION TERMINÉE AVEC DES ERREURS$(RESET)"; \
	fi
	@echo "Temps écoulé : $(DURATION) secondes"
	@echo "  Nombre d'erreurs : $(ERRORS)"
	@echo "--------------------------------------------------"
	@rm -f $(ERR_LOG)

clean:
	$(RM) $(OBJS_DIR)	
	@echo "$(PURPLE) Objects cleaned!$(DEF_COLOR)"

fclean: clean
		$(RM) $(NAME)
		@echo "$(PURPLE) $(NAME) deleted!$(DEF_COLOR)"

re: fclean all

.PHONY : all clean fclean re debug