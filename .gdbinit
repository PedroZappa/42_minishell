#
##
### GDB Settings
##
#
set prompt (zdb) 
set editing on
# set verbose on
set tui border-kind acs
set tui active-border-mode bold-standout
set tui border-mode reverse
set trace-commands on
set logging enabled on
show follow-fork-mode
set follow-fork-mode child

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
define xx
	kill
	exit
end
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
	display tkn_str
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

define ft_add_tk_free
	display tk
end

define tk_last
	display tk
end

# 220_tk_expander.c
define expander
	display sh
	display tk_str
	display tk_str[i]
	display **sub_tkns
	display sub_tkns[curr_tk]
	display *sub_tkns@5
	display *ret
	display curr_tk
	display *curr_tk
	display i
end

define expand_dollar
	display tkn
	display *i
	display tkn[*i]
	display tkn_start
	display tkn_len
	display *ret
end

define expand_squote
	display sub_tkns
	display (*sub_tkns)[(*curr_tk)]
	display tkn
	display tkn[*i]
	display *i
	display curr_tk
	display tkn_start
	display tkn_len
end

define expand_dquote
	display sub_tkns
	display **sub_tkns@5
	display tkn
	display tkn[*i]
	display *i
	display start
	displa *curr_tk
end

define expand_other
	display sub_tkns
	display (*sub_tkns)[(*curr_tk)]
	display tkn
	display *i
	display tkn[*i]
	display tkn_start
	display tkn_len
end

# 230_tk_expander_init.c
define expander_init
	display tkn_str
	display tkn_str[i]
	display sub_tkns
	display *sub_tkns@n_tkns
	display **sub_tkns
	display n_tkns
	display i
end

define expand_check_dollar
	display tkn
	display tkn[*i]
	display *i
end

define expand_check_dquote
	display tkn
	display tkn[*i]
	display *n_tkns
	display *i
	display dollar
end

define expand_check_other
	display tkn
	display tkn[*i]
	display *i
end

### 240_tk_expander_var.c
define expand_var
	display **sub_tkns@5
	display sub_tkns
	display *sub_tkns
	display **sub_tkns
	display ret
	display curr
	display i
	display (*sub_tkns)[i]
end

define fill_var
	display tkn
	display tkn[i]
	display var
	display i
end

define unquote
	display tkn
	display ret
	display len
	display tkn[0]
	display tkn[(len -1)]
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
	display *cmds->argv@cmds->argc
	display cmds[i].argv[j]
end

define expand_check_dollar
	display tkn
	display tkn[*i]
	display *i
end

### 300_parser.c
define parser
	display *sh
	display line_buf
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
	display var
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

### 520_build_var.c
define build_var
	display *sh
	display n
	display i
	display *sh->cmds[n].argv@sh->cmds[n].argc
	display sh->cmds[n].argv[i]
end

define append_var
	display *sh
	display *sh->cmds[n].argv@sh->cmds[n].argc
	display sh->cmds[n].argv[i]
	display n
	display i
	display key
	display new_val
	display old_val
	display plus_pos
	display key_len
end

# 600_execute.c
define execute
	display *sh
	display *sh->path
end

define split_path
	display *envp
	display *path
	display to_split
	display i
end

define path_from_env
	display *envp
	display envp[i]
	display i
end

define exec_one
	display *sh
	display cmd
end

define exec_fork
	display *sh
	display pid
end

define exec
	display *shset editing on
	display *cmd
	display n
end

### 620_exec_one.c
define update_last_cmd
	display *sh
	display i
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

### 710_pwd.c
define pwd
	display *pwd
	display i
	display sh->cmds[n].argv[0]
	display sh->cmds[n].argv[i]
end

### 720_cd.c
define ft_cd
	display *sh
	display cmd_n
end

define chdir
	display pwd
	display *path
	display chdir_ret
end

### 730_env.c
define env
	display *sh
	display n
	display i
	display *sh->cmds[n].argv@sh->cmds[n].argc
	display sh->cmds[n].argv[i]
	display sh->envp[i]
end

### 750_echo.c 
define ft_echo
	display *sh
	display n
	display i
	display *sh->cmds[n].argv@sh->cmds[n].argc
	display sh->cmds[n].argv[i]
end

define rm_squotes
	display arg
	display	unquoted
	display len
end

### 760_export.c
define export
	display *sh
	display n
	display *sh->cmds[n].argv@sh->cmds[n].argc
	display sh->cmds[n].argv[i]
end

define isvalid_var
	display var
	display var[i]
	display i
end

define update_var
	display *sh
	display n
	display i
	display key_len
	display key
	display value
end

define export_var
	display *sh
	display n
	display i
	display key
	display value
	display j
end

### 761_export_status.c
define export_status
	display *sh
	display n
	display **sorted
	display *sorted[i]
	display *equal
	display *(equal + 1)
	display n
end

define sort_env
	display **env
	display n
	display ret
	display var_len
	display next_len
	display i
	display j
	display env[n]
	display env[n + 1]
	display env[i]
	display env[j]
end

### 900_free.c
define free
	display *sh
	display status
end

define free_tks
	display **t k
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
