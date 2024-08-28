# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/29 20:35:29 by passunca          #+#    #+#              #
#    Updated: 2024/08/17 11:40:34 by passunca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                  MAKE CONFIG                                 #
#==============================================================================#

MAKE	= make -C
SHELL	:= bash --rcfile ~/.bashrc

# Default test values
IN_PATH		?= $(SRC_PATH)
ARG			=

#==============================================================================#
#                                     NAMES                                    #
#==============================================================================#

NAME 			= minishell
TESTER			= minishell_tester

### Message Vars
_SUCCESS 		= [$(GRN)SUCCESS$(D)]
_INFO 			= [$(BLU)INFO$(D)]
_NORM 			= [$(MAG)Norminette$(D)]
_NORM_SUCCESS 	= $(GRN)=== OK:$(D)
_NORM_INFO 		= $(BLU)File no:$(D)
_NORM_ERR 		= $(RED)=== KO:$(D)
_SEP 			= =====================

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

SRC_PATH		= src
INC_PATH		= inc
LIBS_PATH		= lib
BUILD_PATH		= .build
TEMP_PATH		= .temp

FILES			= 000_main.c
FILES			+= 010_init.c
FILES			+= 100_termios.c
FILES			+= 200_tokenizer.c
FILES			+= 210_tk_list.c
FILES			+= 220_tk_expander.c
FILES			+= 230_tk_expander_init.c
FILES			+= 240_tk_expander_var.c
FILES			+= 250_tk_expander_utils.c
FILES			+= 260_tk_rm_blank.c
FILES			+= 300_parser.c
FILES			+= 310_readline.c
FILES			+= 400_signal.c
FILES			+= 500_env_get.c
FILES			+= 510_env_set.c
FILES			+= 520_append_var.c
FILES			+= 530_last_cmd.c
FILES			+= 600_execute.c
FILES			+= 610_exec_check.c
FILES			+= 620_exec_one.c
FILES			+= 630_exec_pipeline.c
FILES			+= 640_exec_child.c
FILES			+= 650_exec_cmd.c
FILES			+= 660_execve.c
FILES			+= 670_pipes.c
FILES			+= 680_redir.c
FILES			+= 700_exit.c
FILES			+= 710_pwd.c
FILES			+= 720_cd.c
FILES			+= 730_env.c
FILES			+= 740_clear.c
FILES			+= 750_echo.c
FILES			+= 760_export.c
FILES			+= 761_export_status.c
FILES			+= 770_unset.c
FILES			+= 780_path.c
FILES			+= 781_path_resolver.c
FILES			+= 782_path_utils.c
FILES			+= 800_error.c
FILES			+= 810_error2.c
FILES			+= 900_free.c

SRC		= $(addprefix $(SRC_PATH)/, $(FILES))
OBJS	= $(SRC:$(SRC_PATH)/%.c=$(BUILD_PATH)/%.o)

LIBFT_PATH	= $(LIBS_PATH)/libft
LIBFT_ARC	= $(LIBFT_PATH)/libft.a

TESTER_PATH		= $(LIBS_PATH)/minishell_tester
GOOGLETEST_PATH	= tests/googletest
BOOST_PATH		= tests/boost/
BOOST			= boost_1_86_0

#==============================================================================#
#                              COMPILER & FLAGS                                #
#==============================================================================#

CC			= cc

CFLAGS		= -Wall -Wextra -Werror
DFLAGS		= -g
RFLAGS		= -lreadline
INC			= -I $(INC_PATH)

BUILD 		?= all
ASAN_FLAGS	= -fsanitize=address

#==============================================================================#
#                                COMMANDS                                      #
#==============================================================================#

### Core Utils
RM		= rm -rf
AR		= ar rcs
MKDIR_P	= mkdir -p

### Valgrind
VAL_ARGS 	= --suppressions=readline.supp
VAL_LEAK	= --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --trace-children=yes
VGDB_ARGS	= --vgdb-error=0 $(VAL_LEAK) $(VAL_ARGS)

#==============================================================================#
#                                  RULES                                       #
#==============================================================================#

##@ minishell Compilation Rules 🏗

all: deps $(BUILD_PATH) $(NAME)	## Compile

$(NAME): $(BUILD_PATH) $(LIBFT_ARC) $(OBJS)			## Compile
	@echo "$(YEL)Compiling $(MAG)$(NAME)$(YEL) mandatory version$(D)"
	$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) $(INC) $(LIBFT_ARC) $(RFLAGS) -o $(NAME)
	@echo "[$(_SUCCESS) compiling $(MAG)$(NAME)$(D) $(YEL)🖔$(D)]"
	make norm

asan: CFLAGS += $(ASAN_FLAGS)
asan: $(BUILD_PATH) $(LIBFT_ARC) $(OBJS)   ## Compile with Address Sanitizer
	@echo "$(YEL)Compiling $(MAG)$(NAME)$(YEL) with Address Sanitizer$(D)"
	$(CC) $(CFLAGS) $(OBJS) $(INC) $(LIBFT_ARC) $(RFLAGS) -o $(NAME)
	@echo "[$(_SUCCESS) compiling $(MAG)$(NAME)$(D) with Address Sanitizer $(YEL)🖔$(D)]"

deps:		## Download/Update deps
	@if test ! -d "$(LIBFT_PATH)"; then make get_libft; \
		else echo "$(YEL)[libft]$(D) folder found 🖔"; fi
	@echo " $(RED)$(D) [$(GRN)Nothing to be done!$(D)]"

-include $(BUILD_PATH)/%.d

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	@echo -n "$(MAG)█$(D)"
	$(CC) $(CFLAGS) $(DFLAGS) -MMD -MP -c $< -o $@

$(BUILD_PATH):
	$(MKDIR_P) $(BUILD_PATH)
	@echo "* $(YEL)Creating $(CYA)$(BUILD_PATH)$(YEL) folder:$(D) $(_SUCCESS)"

$(TEMP_PATH):
	$(MKDIR_P) $(TEMP_PATH)
	@echo "* $(YEL)Creating $(CYA)$(TEMP_PATH)$(YEL) folder:$(D) $(_SUCCESS)"

$(LIBFT_ARC):
	$(MAKE) $(LIBFT_PATH) extra

get_libft:
	@echo "* $(CYA)Getting Libft submodule$(D)]"
	@if test ! -d "$(LIBFT_PATH)"; then \
		git clone git@github.com:PedroZappa/42_libft.git $(LIBFT_PATH); \
		echo "* $(GRN)Libft submodule download$(D): $(_SUCCESS)"; \
	else \
		echo "* $(GRN)Libft submodule already exists 🖔"; \
	echo " $(RED)$(D) [$(GRN)Nothing to be done!$(D)]"; \
	fi

##@ Norm Rules

norm:
	@make --no-print-directory norm_path IN_PATH=$(SRC_PATH)
	@make --no-print-directory norm_path IN_PATH=$(INC_PATH)

norm_path: $(TEMP_PATH)		## Run norminette test on source files
	@echo "$(CYA)$(_SEP)$(D)"
	@printf "${_NORM}: $(YEL)$(IN_PATH)$(D)\n"
	@ls $(IN_PATH) | wc -l > $(TEMP_PATH)/norm_ls.txt
	@printf "$(_NORM_INFO) $$(cat $(TEMP_PATH)/norm_ls.txt)\n"
	@printf "$(_NORM_SUCCESS) "
	@norminette $(IN_PATH) | grep -wc "OK" > $(TEMP_PATH)/norm.txt; \
	if [ $$? -eq 1 ]; then \
		echo "0" > $(TEMP_PATH)/norm.txt; \
	fi
	@printf "$$(cat $(TEMP_PATH)/norm.txt)\n"
	@if ! diff -q $(TEMP_PATH)/norm_ls.txt $(TEMP_PATH)/norm.txt > /dev/null; then \
		printf "$(_NORM_ERR) "; \
		norminette $(IN_PATH) | grep -v "OK" > $(TEMP_PATH)/norm_err.txt; \
		cat $(TEMP_PATH)/norm_err.txt | grep -wc "Error:" > $(TEMP_PATH)/norm_errn.txt; \
		printf "$$(cat $(TEMP_PATH)/norm_errn.txt)\n"; \
		printf "$$(cat $(TEMP_PATH)/norm_err.txt)\n"; \
	else \
		printf "[$(YEL)Everything is OK$(D)]\n"; \
	fi
	@echo "$(CYA)$(_SEP)$(D)"

check_ext_func: all		## Check for external functions
	@echo "[$(YEL)Checking for external functions$(D)]"
	@echo "$(YEL)$(_SEP)$(D)"
	@echo "$(CYA)Reading binary$(D): $(MAG)$(NAME)$(D)"
	nm ./$(NAME) | grep "U" | grep -v "__" | tee $(TEMP_PATH)/ext_func.txt
	@echo "$(YEL)$(_SEP)$(D)"

##@ Test Rules 🧪

sync_shell: $(BUILD)		## Test w/ syncshell
	tmux set-option remain-on-exit off
	@echo "[$(YEL)Testing with syncshell$(D)]"
	tmux split-window -h "bash"
	tmux setw synchronize-panes on
	clear && ./$(NAME)

sync_valgrind: $(BUILD)		## Test bash & minishell w/ valgrind
	tmux set-option remain-on-exit on
	@echo "[$(YEL)Testing with valgrind$(D)]"
	tmux split-window -h "valgrind $(VAL_ARGS) bash"
	tmux setw synchronize-panes on
	clear && valgrind $(VAL_ARGS) $(VAL_LEAK) ./$(NAME)

cmake: $(BUILD) get_googletest
	@cd tests/ && mkdir -p build/ && cd build/ && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .. && make
	@if test ! -f compile_commands.json; then \
		ln -s tests/build/compile_commands.json compile_commands.json; \
	fi

ctest: cmake			## Test w/ ctest
	@cd tests/build && ctest

tester: $(BUILD) cmake	## Test w/ googletest
	./tests/build/$(TESTER)

get_googletest: $(BUILD_PATH) $(BUILD)
	@echo "* $(CYA)Getting googletest$(D): $(_INFO)"
	@if test ! -d "$(GOOGLETEST_PATH)"; then \
		git clone git@github.com:google/googletest.git $(GOOGLETEST_PATH); \
		echo "* $(YEL)googletest download$(D): $(_SUCCESS)"; \
	else \
		echo "* $(YEL)googletest already exists 🖔"; \
	echo " $(RED)$(D) [$(GRN)Nothing to be done!$(D)]"; \
	fi

##@ Debug Rules 

gdb: all $(NAME) $(TEMP_PATH)			## Debug w/ gdb
	tmux split-window -h "gdb --tui --args ./$(NAME)"
	tmux resize-pane -L 5
	tmux split-window -v "btop"
	make get_log


vgdb: all $(NAME) $(TEMP_PATH)			## Debug w/ valgrind (memcheck) & gdb
	tmux split-window -h "valgrind $(VGDB_ARGS) --log-file=gdb.txt ./$(NAME) $(ARG)"
	make vgdb_cmd
	tmux split-window -v "gdb --tui -x $(TEMP_PATH)/gdb_commands.txt $(NAME)"
	tmux resize-pane -U 18
	tmux split-window -v "btop"
	make get_log

valgrind: all $(NAME) $(TEMP_PATH)			## Debug w/ valgrind (memcheck)
	tmux set-option remain-on-exit on
	tmux split-window -h "valgrind $(VAL_ARGS) $(VAL_LEAK) ./$(NAME) $(ARG)"

massif: all $(TEMP_PATH)		## Run Valgrind w/ Massif (gather profiling information)
	@TIMESTAMP=$(shell date +%Y%m%d%H%M%S); \
	if [ -f massif.out.* ]; then \
		mv -f massif.out.* $(TEMP_PATH)/massif.out.$$TIMESTAMP; \
	fi
	@echo " 🔎 [$(YEL)Massif Profiling$(D)]"
	valgrind --tool=massif --time-unit=B ./$(NAME) $(ARG)
	ms_print massif.out.*
# Learn more about massif and ms_print:
### https://valgrind.org/docs/manual/ms-manual.html

get_log:
	touch gdb.txt
	@if command -v lnav; then \
		lnav gdb.txt; \
	else \
		tail -f gdb.txt; \
	fi

vgdb_cmd: $(NAME) $(TEMP_PATH)
	@printf "target remote | vgdb --pid=" > $(TEMP_PATH)/gdb_commands.txt
	@printf "$(shell pgrep -f valgrind)" >> $(TEMP_PATH)/gdb_commands.txt
	@printf "\n" >> $(TEMP_PATH)/gdb_commands.txt
	@cat .vgdbinit >> $(TEMP_PATH)/gdb_commands.txt

##@ Clean-up Rules 󰃢

clean: 				## Remove object files
	@echo "*** $(YEL)Removing $(MAG)$(NAME)$(D) and deps $(YEL)object files$(D)"
	@if [ -d "$(BUILD_PATH)" ] || [ -d "$(TEMP_PATH)" ]; then \
		if [ -d "$(BUILD_PATH)" ]; then \
			$(RM) $(BUILD_PATH); \
			echo "* $(YEL)Removing $(CYA)$(BUILD_PATH)$(D) folder & files$(D): $(_SUCCESS)"; \
		fi; \
		if [ -d "$(TEMP_PATH)" ]; then \
			$(RM) $(TEMP_PATH); \
			echo "* $(YEL)Removing $(CYA)$(TEMP_PATH)$(D) folder & files:$(D) $(_SUCCESS)"; \
		fi; \
	else \
		echo " $(RED)$(D) [$(GRN)Nothing to clean!$(D)]"; \
	fi

fclean: clean			## Remove executable and .gdbinit
	@if [ -f "$(NAME)" ]; then \
		if [ -f "$(NAME)" ]; then \
			$(RM) $(NAME); \
			$(RM) compile_commands.json; \
			echo "* $(YEL)Removing $(CYA)$(NAME)$(D) file: $(_SUCCESS)"; \
		fi; \
	else \
		echo " $(RED)$(D) [$(GRN)Nothing to be fcleaned!$(D)]"; \
	fi

libclean: fclean	## Remove libs
	$(RM) $(LIBS_PATH)
	$(RM) $(GOOGLETEST_PATH)
	$(RM) $(BOOST_PATH)
	$(RM) tests/build
	$(RM) compile_commands.json
	@echo "* $(YEL)Removing lib folder & files!$(D) : $(_SUCCESS)"

re: fclean all	## Purge & Recompile

##@ Help 󰛵

help: 			## Display this help page
	@awk 'BEGIN {FS = ":.*##"; \
			printf "\n=> Usage:\n\tmake $(GRN)<target>$(D)\n"} \
		/^[a-zA-Z_0-9-]+:.*?##/ { \
			printf "\t$(GRN)%-18s$(D) %s\n", $$1, $$2 } \
		/^##@/ { \
			printf "\n=> %s\n", substr($$0, 5) } ' Makefile
## Tweaked from source:
### https://www.padok.fr/en/blog/beautiful-makefile-awk

.PHONY: bonus clean fclean re help

#==============================================================================#
#                                  UTILS                                       #
#==============================================================================#

# Colors
#
# Run the following command to get list of available colors
# bash -c 'for c in {0..255}; do tput setaf $c; tput setaf $c | cat -v; echo =$c; done'
#
B  		= $(shell tput bold)
BLA		= $(shell tput setaf 0)
RED		= $(shell tput setaf 1)
GRN		= $(shell tput setaf 2)
YEL		= $(shell tput setaf 3)
BLU		= $(shell tput setaf 4)
MAG		= $(shell tput setaf 5)
CYA		= $(shell tput setaf 6)
WHI		= $(shell tput setaf 7)
GRE		= $(shell tput setaf 8)
BRED 	= $(shell tput setaf 9)
BGRN	= $(shell tput setaf 10)
BYEL	= $(shell tput setaf 11)
BBLU	= $(shell tput setaf 12)
BMAG	= $(shell tput setaf 13)
BCYA	= $(shell tput setaf 14)
BWHI	= $(shell tput setaf 15)
D 		= $(shell tput sgr0)
BEL 	= $(shell tput bel)
CLR 	= $(shell tput el 1)

