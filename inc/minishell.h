/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfragoso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:11:31 by passunca          #+#    #+#             */
/*   Updated: 2024/08/09 11:44:32 by gfragoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* @defgroup 	minishell	minishell header
* @{
*
* @brief		Header file for minishell.c
* @version		1.0
***/

#ifndef MINISHELL_H
# define MINISHELL_H

//=============================================================================/
//								Library Headers                                /
//=============================================================================/

# include <errno.h> // Get errno
# include <fcntl.h> // stat struct
# include <signal.h> // signal()
# include <stdlib.h> // exit, free, malloc
# include <termios.h> // termios interface
# include <unistd.h> // STDIN_FILENO STDOUT_FILENO
# include <readline/readline.h> // readline
# include <readline/history.h> // shell history
# include <sys/wait.h> // wait()
# include <sys/stat.h> // stat()
# include "../lib/libft/libft/libft.h" // libft library
# include "../lib/libft/ft_printf/ft_printf.h" // ft_printf
# include "../lib/libft/ft_fprintf/ft_fprintf.h" // ft_fprintf

//=============================================================================/
//									Defines									   /
//=============================================================================/

//	Error messages
# define INIT_ERR		"Init Error\n"
# define ENV_INIT_ERR	"Env Init Error\n"
# define ENV_NULL_ERR	"Null Env Error\n"
# define ENV_VAR_ERR	"Null Env Error\n"
# define TKNZR_ERR		"Tokenizer Error\n"
# define MALLOC_ERR		"Malloc Error\n"
# define TERMIOS_ERR	"Termios Error\n"
# define FORK_ERR		"Fork error\n"
# define QUOTE_ERR		"No matching quote error\n"
# define PIPE_ERR		"Pipe error\n"
# define PID_ERR		"PID error\n"
# define DIR_ERR		"Directory/File error\n"
# define CMD_ERR		"Command not found\n"
# define REDIR_ERR		"Redirection error\n"
# define ARG_ERR		"Invalid arguments\n"
# define SYNTAX_ERR		"Syntax error\n"

/// Constants
# define CHARSET "?%*+,.-/#:@~ \t"
# define N_HANDLE "&;(){}*\\"
# define QUOTE_SET "\'\""
# define SPC_QUOTES " \t\'\""
# define BLANKS " \t\v\r\n\f"

/// Semantics
# define VI 0
# define NO_ENV -1
# define NO_VAR -1
# define NO_TOKEN 0
# define NO_PATH 0
# define NO_CMDS 0
# define NO_PIPE 0
# define PID_FAIL -1
# define EXECVE_ERR -1
# define IGNORE_SIGQUIT	-1

/// Signals
# define CMD_NOT_FOUND	127
# define EXIT_SIGINT	130
# define EXIT_SIGQUIT	131

/// Data Types shorthands
typedef struct termios	t_term;
typedef struct stat		t_stat;

/// @brief		Global variable to store exit code.
/// @details	Indicates a received signal.
///				- Gets errno, ...
extern int				g_exit;

//=============================================================================/
//									Enums	                                   /
//=============================================================================/

typedef enum e_exit
{
	SUCCESS,
	FAILURE
}	t_exit;

typedef enum e_token_type
{
	TK_IN,
	TK_OUT,
	TK_CMD,
	TK_NULL,
	TK_BLANK,
	TK_PIPE,
	TK_OR,
	TK_AND,
	TK_WILD,
}	t_token_type;

typedef enum e_cmd_type
{
	CMD_EXEC,
	CMD_ECHO,
	CMD_CD,
	CMD_PWD,
	CMD_EXPORT,
	CMD_UNSET,
	CMD_ENV,
	CMD_CLEAR,
	CMD_EXIT,
	CMD_HELP,
	CMD_PATH,
}	t_cmd_type;

//=============================================================================/
//                               Structures                                    /
//=============================================================================/

/// @struct			Token
/// @brief			Structure to build linked list of tokens
///	@param type		Token type (see e_token_type)
///	@param name		Token string
///	@param len		Token length
///	@param to_del		Flag to delete token
///	@param next		Next token
///				...
typedef struct s_token
{
	t_token_type	type;
	char			*name;
	int				len;
	int				to_del;
	struct s_token	*next;
}	t_token;

/// @struct			Token operators
/// @brief			Helper structure to save token operators
/// @param tkn		Pointer to token string
/// @param type		Token operator (see e_token_type)
/// @param len		Token length
/// @note			Used in 200_tokenizer.c
typedef struct s_tk_ops
{
	char			*tkn;
	t_token_type	type;
	int				len;
}	t_tk_ops;

/// @struct			Redirection
/// @brief	   		Structure to save redirection data
/// @param name  	Redirection name
/// @param flag
/// Redirection status flag:
/// - -1: Ignores SIGQUIT
/// - 0: No redirection
/// - 1: Input redirection
/// @param heredoc	Pointer to Heredoc redirection node (see t_list)
typedef struct s_redir
{
	char	*name;
	int		flag;
	t_list	*heredoc;
}	t_redir;

/// @struct			Command
/// @brief			Structure to save command data
/// @param cmd   	Command string
/// @param argc  	Argument count
/// @param argv  	Argument vector
/// @param in	   	Input redirection data (see t_redir)
/// @param out   	Output redirection data (see t_redir)
typedef struct s_cmd
{
	char	*cmd;
	int		argc;
	char	**argv;
	t_redir	in;
	t_redir	out;
}	t_cmd;

/// @struct				Shell
/// @brief				Structure to save minishell data
/// @param termios		Pointer to termios interface (see t_term)
/// @param cmds  		Pointer to commands array (see t_cmd)
/// @param n_cmds		Number of commands
/// @param envp			Pointer to Environment Variables
/// @param envt			Pointer to Temporary Environment Variables
/// @param path			Pointer to PATH array
/// @param home			Pointer to HOME address
/// @param user			Pointer to USER name
/// @param heredoc		Pointer to HEREDOC
/// @param exit_status	Exit status
/// ...
typedef struct s_shell
{
	t_term	termios;
	t_cmd	*cmds;
	int		n_cmds;
	char	**envp;
	char	**envt;
	char	**path;
	char	*home;
	char	*user;
	char	*heredoc;
	int		exit_status;
}	t_shell;

//=============================================================================/
//							Function Prototypes                                /
//=============================================================================/
//=============================================================================/
//	000		Main  															   /
//=============================================================================/

/// @file	000_main.c
int			main(int argc, char **argv, char **envp);

/// @file	010_init.c
int			ft_init(t_shell *sh, char **envp);
void		ft_reset_redir(t_cmd *cmd, int n_cmds);

//=============================================================================/
//	100		Termios  														   /
//=============================================================================/

/// @file	100_termios.c
void		ft_get_termios(int fd, t_term *termios);
void		ft_set_termios(int fd, int opts, t_term *termios);

//=============================================================================/
//	200		Tokenizer  														   /
//=============================================================================/

/// @file	200_tokenizer.c
int			ft_tokenizer(t_shell *sh, char *line, t_token **tks);

/// @file	210_tk_list.c
t_token		*ft_tk_new(char *line, t_token_type type, int len);
void		ft_tk_add(t_token **tk_list, t_token *tks);
void		ft_tk_add_free(t_token **tk_list, t_token *tk, t_tk_ops *tk_op);
t_token		*ft_tk_last(t_token *tk);

/// @file	220_tk_expander.c
char		*ft_expander(t_shell *sh, char *str);
char		*ft_expand_dollar(char *tkn, int *i);
void		ft_expand_squote(char ***sub_tkns, char *tkn, int *i, int *curr_tk);
void		ft_expand_dquote(char ***sub_tkns, char *tkn, int *i, int *curr_tk);
void		ft_expand_other(char ***sub_tkns, char *tkn, int *i, int *curr_tk);

/// @file	230_tk_expander_check.c
char		**ft_expander_init(char *tkns);
// static void	ft_expand_check_dollar(char *tkn, int *i);
// static void	ft_expand_check_squote(char *tkn, int *i);
// static void	ft_expand_check_dquote(char *tkn, int *n_tkns, int *i);
// static void	ft_expand_check_other(char *tkn, int *i);

/// @file	240_tk_expander_var.c
char		*ft_expand_var(t_shell *sh, char ***sub_tkns);

/// @file	250_tk_expander_utils.c
int			ft_check_alpha(char c);
int			ft_check_alnum(char c);

/// @file	260_tk_rm_blanks.c
void		ft_rm_blank_tks(t_token **tk_list);

//=============================================================================/
//	300		Parser  														   /
//=============================================================================/

/// @file	300_parser.c
int			ft_parser(t_shell *sh, char *line_buf);
/// static int	ft_check_syntax(t_token *tks);
/// static int	ft_count_cmds(t_token *tks);
/// static void	ft_count_args(t_shell *sh, t_token *tks);
/// static int	ft_parse_cmds(t_token *tks, t_cmd *cmds, int i, int j);

/// @file	310_readline.c
void		ft_readline(char **line_buf, t_shell *sh);

//=============================================================================/
//	400		Signal  														   /
//=============================================================================/

/// @file	400_signal.c
void		ft_sigset(void);
void		ft_fork_sigset(void);
void		ft_fork_sighandler(int sig);

//=============================================================================/
//	500		Env Setters/Getters												   /
//=============================================================================/

/// @file	500_env_get.c
char		**ft_init_env(char **env);
char		*ft_get_var(char *var, char **envp, char**envt);
// static char	*ft_extract_var(char *select, char **env);
int			ft_get_var_index(char *var, char **env);

/// @file	510_env_set.c
int			ft_set_var(char *var, char *val, char ***env);
int			ft_var_from_env(char *var, char **env);
char		**ft_env_del_var(char **env, char *to_del);
// static char	**ft_env_add_var(char **env, char *new_var);

/// @file	520_build_var.c
int			ft_append(t_shell *sh, int n, int i);
// static void	ft_append_var(t_shell *sh, int n, int i);

/// @file	530_last_cmd.c
void		ft_build_last_cmd(t_shell *sh, int n);
int			ft_update_last_cmd(t_shell *sh);

//=============================================================================/
//	600		Executer														   /
//=============================================================================/

/// @file	600_execute.c
int			ft_execute(t_shell *sh);
// static char	**ft_split_path(char **envp);
// static int	ft_path_from_env(char **envp);

/// @file	610_exec_check.c
int			ft_exec_check(char *cmd);

/// @file	620_exec_one.c
int			ft_exec_one(t_shell *sh);
int			ft_exec_fork(t_shell *sh);

/// @file	630_exec_pipeline.c
int			ft_exec_pipeline(t_shell *sh);

/// @file	640_exec_child.c
void		ft_exec_child(t_shell *sh, int *outpipe);

/// @file	650_exec_cmd.c
void		ft_exec_cmd(t_shell *sh, int id, int i);
int			ft_exec(t_shell *sh, int cmd, int n);

/// @file	660_execve.c
void		ft_execve(char **path, char **argv, char **envp);

//=============================================================================/
//	700		Builtins														   /
//=============================================================================/

/// @file	700_exit.c
int			ft_exit(t_shell *sh, int n);
/// static void	ft_kill(t_shell *sh, int sig);

/// @file	710_pwd.c
int			ft_pwd(t_shell *sh, int n);

/// @file	720_cd.c
int			ft_cd(t_shell *sh, int cmd_n);
// static int	ft_chdir(char ***env, char *path);

/// @file	730_env.c
int			ft_env(t_shell *sh, int n);

/// @file	740_clear.c
int			ft_clear(int n);

/// @file	750_echo.c
int			ft_echo(t_shell *sh, int n);

/// @file	760_export.c
int			ft_export(t_shell *sh, int n);
// static int	ft_export_status(t_shell *sh, int n);
// static char	**ft_sort_env(char **env, int n);

/// @file	761_export_status.c
int			ft_export_status(t_shell *sh, int n);

/// @file	770_unset.c
int			ft_unset(t_shell *sh, int n);

/// @file	780_path.c 
int			ft_path(t_shell *sh, int n);

//=============================================================================/
//	800		Errors & Info													   /
//=============================================================================/

/// @file	800_errors.c
int			ft_err(char *msg, int status);
int			ft_syntax_err(char *tkn, int err);
int			ft_flag_err(char *cmd, char *cmd_flag, int err);
int			ft_cmd_err(char *cmd, int err);
int			ft_bash_err(char *cmd, char *arg, int err);

//=============================================================================/
//	900		Free															   /
//=============================================================================/

/// @file	900_free.c
void		ft_free_sh(t_shell *sh);
int			ft_free_arr(char **arr);
int			ft_free_tks(t_token **tk);
int			ft_free_cmds(t_cmd *cmds, int n_cmds);
int			ft_free_nocmds(t_cmd *cmds, int n_cmds, t_token **tks);

#endif

/** @} */
