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
	display *envp
end

define init_env
	display *env
	display *new_env
	display n
end

#
##
### Go GDB Go! I Choose YOU! 
##
#
# main()
# break main
# run
# main
# fs cmd
# rfr

# ft_init()
# break ft_init
# run
# init
# fs cmd
# rfr

# ft_init()
break ft_init_env
break 82
run
init_env
fs cmd
rfr
