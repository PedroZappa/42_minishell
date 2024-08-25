#ifndef TESTER_HPP
# define TESTER_HPP

# include <cstdio>
# include <string>
# include <iostream>
# include <map>

# include <boost/process.hpp>
# include <boost/version.hpp>
# include <gtest/gtest.h>

# include "../lib/libft/libft/libft.h"

class Tester
{
	public: 
		// Variables
		int bash_exit_status;
		int minishell_exit_status;
		std::string args;
		std::string minishell_path = "./minishell";
		// Functions
		void Test(const std::string& minishell_cmd);
		std::pair<std::string, int> get_bash_output(const std::string& cmd);
		std::pair<std::string, int> get_minishell_output(const std::string& bash_output, const std::string& cmd);
};

#endif /* TESTER_HPP */
