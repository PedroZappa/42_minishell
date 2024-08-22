#ifndef TESTER_HPP
# define TESTER_HPP

#include <string>

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>


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

};

#endif /* TESTER_HPP */
