#ifndef TESTER_HPP
# define TESTER_HPP

#include <cstdio>
#include <string>

#include <boost/process.hpp>
#include <boost/version.hpp>
#include <gtest/gtest.h>

#include "../lib/libft/libft/libft.h"

class Tester
{
	public: 
		// Variables
		int bash_exit_status;
		int minishell_exit_status;
		std::string args;
		std::string minishell_path = ".";
		// Functions
		std::string exec(const char* cmd);

		void ProcessTest(const std::string& minishell_cmd);
		std::string get_bash_output(const std::string& cmd);
		std::string get_minishell_output(const std::string& bash_output, const std::string& cmd);
		std::string get_minishell_output_pty(const std::string& bash_output, const std::string& cmd);
		std::string minishell_cmd_;
};

#endif /* TESTER_HPP */
