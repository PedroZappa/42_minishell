42 Project : minishell
<a name="readme-top"></a>
<div align="center">

# minishell

> Who thought treading on parallelism & concurrency land could be so philosophically deadly 🕱

<p>
    <img src="https://img.shields.io/badge/score-%20%2F%20099-success?style=for-the-badge" />
    <img src="https://img.shields.io/github/repo-size/PedroZappa/42_minishell?style=for-the-badge&logo=github">
    <img src="https://img.shields.io/github/languages/count/PedroZappa/42_minishell?style=for-the-badge&logo=" />
    <img src="https://img.shields.io/github/languages/top/PedroZappa/42_minishell?style=for-the-badge" />
    <img src="https://img.shields.io/github/last-commit/PedroZappa/42_minishell?style=for-the-badge" />
</p>

___

<h3>Table o'Contents</h3>

</div>

<!-- mtoc-start -->

* [About 📌](#about-)
* [Features](#features)
* [Usage 🏁](#usage-)
* [Tests & Debug 🧪](#tests--debug-)
* [References 📚](#references-)
  * [Shell/Bash](#shellbash)
  * [Termios](#termios)
  * [Readline](#readline)
  * [Heredoc](#heredoc)
* [License 📖](#license-)

<!-- mtoc-end -->

# About 📌

Minishell is a project that aims to create a simple UNIX command-line shell. This project introduces students to the world of shells by implementing a mini version of bash.

# Features
- Parse and execute basic shell commands;
- Search & launch the right executable from absolute or relative path;
- Command history;
- Handle built-in commands (`cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`);
- Support for pipes (`|`) and redirections (`<`, `>`, `>>`, `<<`);
- Environment variable 
    - export variables;
    - unset variables;
    - expand environment variables;
- Signal handling (`Ctrl-C`, `Ctrl-D`, `Ctrl-\\`);

___

# Usage 🏁

Clone the repository and cd into it:
```sh
git clone https://github.com/PedroZappa/42_minishell.git 42_minishell
```

Build the program:
```sh
make
```

Run the program:
```sh
./minishell
```

___

# Tests & Debug 🧪

Run the following command and look at the `Test Rules 🧪` & `Debug Rules ` to get a comprehensive list of all available test/debug commands:
```sh
make help
```

> [!Note]
> If you use `tmux` you are in for treat 😏
___
# References 📚

## Shell/Bash
- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [Writing your own shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
- [Shell Command Language](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
- [Exit Codes and Their Meanings - Discovery Cluster / Slurm - USC Advanced Research Computing](https://hpc-discourse.usc.edu/t/exit-codes-and-their-meanings/414/2)

## Termios
- [A Brief Introduction to Termios](https://blog.nelhage.com/2009/12/a-brief-introduction-to-termios/)
- [A Brief Introduction to Termios: termios(3) and stty](https://blog.nelhage.com/2009/12/a-brief-introduction-to-termios-termios3-and-stty/)

## Readline
- [The GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html)
- [Programming with GNU Readline](https://web.mit.edu/gnu/doc/html/rlman_2.html)

## Heredoc
- [Bash Heredoc](https://linuxize.com/post/bash-heredoc/)

# License 📖

This work is published under the terms of <a href="https://github.com/PedroZappa/42_minishell/blob/main/LICENSE">42 Unlicense</a>.

<p align="right">(<a href="#readme-top">get to top</a>)</p>

