#
##
### GDB Settings
##
#
set trace-commands on
set logging enabled on

set print pretty on
# set print elements 2
set print array on
#
skip -gfi *libreadline.so.8

#
##
### Custom Commands
##
#
### 000_main.c
define main
	display argc
	display *argv@argc
	display *envp
end

define sh_loop
	display *sh
	display line_buf
	display status
	p_cmds
end

### 010_init.c
define init
	display *sh
	display *envp
end

define init_env
	display *env
	display env[n]
	display *new_env
	display n
end

### 200_tokenizer.c
define tokenizer
	display *sh
	display *line
	display **tks
	display *tk
	display name
end

define get_tkns
	display line
	display **tks
	display tmp
	display tk
end

define get_tk
	display tk
	display tk[i]
	display ops[i]
	display ret
	display i
end

define p_tk
	print tk
	set $node = tk
	while ($node != 0)
		print *$node
		set $node = $node->next
	end
end

define p_tks
	print tks
	set $node = tks
	while ($node != 0)
		print *$node
		set $node = $node->next
	end
end

define p_cmds
	print *sh->cmds->argv@sh->cmds->argc
end

define print_string_array
  set $array = sh->cmds->argv
  set $count = 0
  while $array[$count]
    printf "%d: %s\n", $count, $array[$count]
    set $count = $count + 1
  end
end

# 210_tk_list.c
define tk_new
	display line
	display type
	display len
	display tk
	display *tk
end

define tk_add
	display *tk_list
	display tk
	display curr
	display *curr
end

define tk_last
	display tk
end

### 300_parser.c
define parser
	display *sh
	display *line_buf
	display *sh->cmds
end

define count_args
	display *sh
	display *tks
	display *prev
	display i
end

define parse_cmds
	display *tks
	display *cmds
	display *cmds->argv
	display cmds[i].argv[j]
	display i
	display j
end

### 310_readline.c
define get_prompt
	display prompt
	display pwd
	display trim
	display ret
	display sh->home
	display sh->user
end

define trim_cwd
	display ****sh
	display cwd
	display tmp
	display ret
end

define add_user_host
	display *****sh
	display sh->user
	display sh->host
	display prompt_len
	display user_len
	display ret

end

### 500_env.c
define get_var
	display *var
	display *envp
	display *envt
	display var2get
end

define extract_var
	display select
	display *envp
	display tmp
	display var
	display *var
	display len
end

# 600_execute.c
define execute
	display *sh
	display *sh->path
end

define exec_one
	display *sh
	display cmd
end

define exec
	display *sh
	display *cmd
	display n
end

# 700_exit.c
define exit
	display *sh
	display n
	display *sh->cmds[n]
end

define ft_kill
	display *sh
	display sig
end

### 720_cd.c
define cd
	display *sh
	display cmd_n
end

define chdir
	display *pwd
	display chdir_ret
end

### 900_free.c
define free
	display *sh
	display status
end

define free_tks
	display **tk
	display *tmp
	display tk->name
	display (*tk)->name
end

#
##
### Go GDB Go! I Choose YOU! 
##
#
### 000_main.c
## main()
# break main
# run
# main
# fs cmd
# rfr

## ft_init()
# break ft_init
# run
# init
# fs cmd
# rfr

## ft_init()
# break ft_init_env
# break 75
# run
# init_env
# fs cmd
# rfr

### 500_env.c
## ft_get_var()
# break ft_get_var
# run
# get_var
# fs cmd
# rfr

# ft_extract_var()
# break ft_extract_var
# run
# extract_var
# fs cmd
# rfr

### Info Stats
info break
info watch
