/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:11:31 by passunca          #+#    #+#             */
/*   Updated: 2024/06/13 16:32:34 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//=============================================================================/
//								Librariy Headers                               /
//=============================================================================/

# include "../lib/libft/libft/libft.h"			// libft library
# include "../lib/libft/ft_printf/ft_printf.h" 	// ft_printf

//=============================================================================/
//									Defines									   /
//=============================================================================/

/// @define		Error messages
# define FORK_ERR "Fork error\n"
# define QUOTE_ERR "No matching quote error\n"
# define PIPE_ERR "Pipe error\n"
# define PID_ERR "PID error\n"
# define DIR_ERR "Directory/Fire error\n"
# define CMD_ERR "Command not found\n"
# define REDIR_ERR "Redirection error\n"
# define ARG_ERR "Invalid arguments\n"

/// @define		Constants
# define D_QUOTE '\"'
# define QUOTE '\''
# define STR_QUOTE "\'"
# define STR_D_QUOTE "\""
# define QUOTE_SET "\'\""
# define CHARSET "?%*+,.-/#:@~ \t"
# define N_HANDLE "&;(){}*\\"
# define SPC " \t"
# define SPC_QUOTES " \t\'\""

//=============================================================================/
//									Enums	                                   /
//=============================================================================/

/// @enum	Bool
typedef enum e_bool
{
	NO = 0,
	YES = 1
}	t_bool;

/// @enum	Exit status
typedef enum e_exit
{
	SUCCESS,
	FAILURE
}	t_exit;

/// @enum	Token types
typedef enum e_token_type
{
	TK_NAME,
	TK_NULL,
	TK_BLANK,
	TK_IN,
	TK_OUT,
	TK_PIPE,
	TK_OR,
	TK_AND,
}	t_token_type;

/// @enum	Command types
typedef enum e_cmd_type
{
	CMD_EXEC,
	CMD_ECHO,
	CMD_CD,
	CMD_PWD,
	CMD_EXPORT,
	CMD_UNSET,
	CMD_ENV,
	CMD_EXIT,
	CMD_HELP,
}	t_cmd_type;

//=============================================================================/
//                               Structures                                    /
//=============================================================================/

/// @struct		Token
/// @brief		Structure to build linked list of tokens
///	@var type	Token type
///	@var val	Token string
///	@var len	Token length
///	@var to_del	Flag to delete token
///	@var next	Next token
/// @desc		Redirection tokens: '<', '<<', '>', '>>'
///				...
typedef struct	s_token
{
	t_token_type	type;
	char			*val;
	int				len;
	int				to_del;
	struct s_token	*next;
}	t_token;

/// @struct			Redirection
/// @brief	   		Structure to save redirection data
/// @var name  		Redirection name
/// @var flag  		Redirection status flag
/// @var heredoc	Pointer to Heredoc redirection node
typedef struct	s_redir
{
	char	*name;
	int		flag;
	t_list	*heredoc;
}	t_redir;

/// @struct		Command
/// @brief		Structure to save command data
/// @var cmd	Command string
/// @var argc	Argument count
/// @var argv	Argument vector
/// @var in		Input redirection data
/// @var out	Output redirection data
typedef struct	s_cmd
{
	char	*cmd;
	int		argc;
	char	**argv;
	t_redir	*in;
	t_redir	*out;
}	t_cmd;

/// @struct				Shell
/// @brief				Structure to save minishell data
/// @var cmds  			Pointer to commands list
/// @var n_cmds			Number of commands
/// @var exit_status	Exit status
/// @var envp			Pointer to Environment Variables
/// @var envt			Pointer to Temporary Environment Variables
/// @var path			Pointer to PATH
/// @var home			Pointer to HOME
/// @var heredoc		Pointer to HEREDOC
/// ...
typedef struct	s_shell
{
	t_cmd		*cmds;
	int			n_cmds;
	int			exit_status;
	char		**envp;
	char		**envt;
	char		*path;
	char		*home;
	char		*heredoc;
}	t_shell;

//=============================================================================/
//							Function Prototypes                                /
//=============================================================================/
//=============================================================================/
//	00	Authentication														   /
//=============================================================================/

//=============================================================================/
//	01	Main																   /
//=============================================================================/

//=============================================================================/
//	02	Signals																   /
//=============================================================================/

//=============================================================================/
//	03	Parser																   /
//=============================================================================/

//=============================================================================/
//	04	Termios																   /
//=============================================================================/

//=============================================================================/
//	05	Tokens																   /
//=============================================================================/

//=============================================================================/
//	06	Env																	   /
//=============================================================================/

//=============================================================================/
//	07	Exec																   /
//=============================================================================/

//=============================================================================/
//	08	Builtins															   /
//=============================================================================/

//=============================================================================/
//	09	Free																   /
//=============================================================================/

#endif
