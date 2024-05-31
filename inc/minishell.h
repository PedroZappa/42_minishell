#ifndef MINISHELL_H
# define MINISHELL_H

//=============================================================================/
//								Librariy Headers                               /
//=============================================================================/

# include "../lib/libft/libft/libft.h"			// libft library
# include "../lib/libft/ft_printf/ft_printf.h" 	// ft_printf
//
//=============================================================================/
//							Variables & Definitions                            /
//=============================================================================/

// ANSI Escape codes
//Regular text
# define BLK "\e[0;30m"	// RGB(0, 0, 0)
# define RED "\e[0;31m"	// RGB(255, 0, 0)
# define GRN "\e[0;32m"	// RGB(0, 255, 0)
# define YEL "\e[0;33m"	// RGB(255, 255, 0)
# define BLU "\e[0;34m"	// RGB(0, 0, 255)
# define MAG "\e[0;35m"	// RGB(255, 0, 255)
# define CYN "\e[0;36m"	// RGB(0, 255, 255)
# define WHT "\e[0;37m"	// RGB(255, 255, 255)
# define NC "\e[0m"

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

//=============================================================================/
//                               Structures                                    /
//=============================================================================/

//=============================================================================/
//							Function Prototypes                                /
//=============================================================================/

#endif
