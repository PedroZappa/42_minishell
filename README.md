# 42_minishell
42 Project : minishell

# Resources

## Articles
- [minishell | 42 Docs](https://harm-smits.github.io/42docs/projects/minishell)
- [Minishell: Building a mini-bash (a @42 project)](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218)

## Tools
- [PlantUML](https://plantuml.com/class-diagram)
- [Linux Toolbox](https://cdn.ttgtmedia.com/searchEnterpriseLinux/downloads/Linux_Toolbox.pdf)


### GoogleTest
- [GoogleTest Repo](https://github.com/google/googletest)
- [GoogleTest User's Guide](https://google.github.io/googletest/)
- [Assertions Reference](https://google.github.io/googletest/reference/assertions.html)

# Docs
## General
- [Writing your own shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
- [Shell Command Language](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)

## Termios
- [A Brief Introduction to Termios](https://blog.nelhage.com/2009/12/a-brief-introduction-to-termios/)
- [A Brief Introduction to Termios: termios(3) and stty](https://blog.nelhage.com/2009/12/a-brief-introduction-to-termios-termios3-and-stty/)

## Readline
- [The GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html)
- [Programming with GNU Readline](https://web.mit.edu/gnu/doc/html/rlman_2.html)

## GCC cleanup __attribute__
- [Using the __cleanup__ variable attribute in GCC](https://echorand.me/site/notes/articles/c_cleanup/cleanup_attribute_c.html)
# Heredoc

- [Bash Heredoc](https://linuxize.com/post/bash-heredoc/)

# Tests
## General
```sh
# TODO:
ls << EOF # Send Ctrl+C inside heredoc then exit provokes a leak
EOF
Ctrl+C

exit << a	# Leaks
a

ls <	# Error Message Output differ
ls >	# Error Message Output differ

env | ls	# Segfault
ls | env	# Segfault

cat < a.txt > b.txt		# Should print error message, shouldn't create any files
```

- ✅ Fix signals (ctrl + d com texto nao sair) 
- Indireitar os pipes
  -- Resolver 2 forks escreverem ao mesmo tempo
- Redirects
- Misc fixes
