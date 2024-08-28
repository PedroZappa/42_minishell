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
# Tests

# Tests
## General
```sh
cat ""
cd /lib/ && pwd

# TODO:
../
$PWD
```
## Built-ins 
### [[echo]]
```sh
echo
echo -n yo
echo --n yo
echo -nn yo
echo '-n' yo
echo '-n ' yo
echo '-n  ' yo
echo 'yo $USER'
echo '$USER'$USER
echo '$USER'"$USER"
echo '$USER'"$USER"$USER
echo "Yo"
echo "$USER"
echo "yo $USER"
echo "-n" yo
echo "-n " yo
echo "-n  " yo
echo zedro is $USER
echo "yo $USER"
echo "yo $USER "
echo "$USER"'$USER'
echo "$USER"'$USER'$USER
echo $USER$USER
echo "$USER"$USER'$USER'

# TODO:
```

### [[cd]]
```sh
cd ~
cd -
cd ""

# TODO:
cd /		# see ft_readline (space for ft_calloc)
cd ~ && cd ..
```

# Notes

TO Verify

Token Priority

Redirect -> Pipe -> Command
