#
##
### GDB Settings 
##
#
set trace-commands on
set logging enabled on

# set print pretty on
# set print elements 2
set print array on

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

define init
	display sh
	display sh->home
	display *envp
end

define init_env
	display *env
	display env[n]
	display *new_env
	display n
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

#
##
### Go GDB Go! I Choose YOU! 
##
#
### 000_main.c
## main()
break main
run
main
fs cmd
rfr

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
