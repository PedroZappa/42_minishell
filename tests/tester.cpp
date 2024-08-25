#include "tester.hpp"

void Tester::Test(const std::string& minishell_cmd) {
    std::pair<std::string, int> bash_output = get_bash_output(minishell_cmd);
    std::pair<std::string, int> minishell_output = get_minishell_output(bash_output.first, minishell_cmd);
	std::pair<std::string, int> valgrind_output = get_valgrind(minishell_path, minishell_cmd);

	std::cout << YEL"Bash Output :\n" << NC << bash_output.first << std::endl;
	std::cout << YEL"Minishell Output :\n" << NC << minishell_output.first << std::endl;
	std::cout << YEL"Valgrind Exit Status :\n" << NC << valgrind_output.second << std::endl;

    if (bash_output != minishell_output) {
        std::cerr << RED"Outputs differ!" << NC << std::endl;
    } else {
        std::cout << GRN"Outputs match!" << NC << std::endl;
    }
}

std::pair<std::string, int> Tester::get_bash_output(const std::string& cmd) {
	Tester test_shell;
    std::string output;
    std::string line_read;
	boost::process::ipstream pipe_stream;
    boost::process::child c(cmd,
		boost::process::std_out > pipe_stream,
		boost::process::std_err > boost::process::null,
		boost::process::shell
	);

    while (pipe_stream && std::getline(pipe_stream, line_read))
        output += line_read;

    c.wait();
	test_shell.bash_exit_status = c.exit_code();
    return {output, test_shell.bash_exit_status};
}

std::pair<std::string, int> Tester::get_minishell_output(const std::string& bash_output, const std::string& cmd) {
	int exit_code = 0;
    std::string output;
    std::string line_read;
    boost::process::opstream in_stream;
	boost::process::ipstream pipe_stream;
    boost::process::child c(minishell_path,
		boost::process::std_in < in_stream,
		boost::process::std_out > pipe_stream,
		boost::process::std_err > boost::process::null,
        boost::process::shell
	);

	// Send cmd to minishell
    in_stream << cmd << std::endl;
    in_stream.pipe().close();

	int line_n = 0;
	while (pipe_stream && std::getline(pipe_stream, line_read))
	{
        if (line_n < 2) {
			line_n++;
        } else {
			if (line_read.empty() || line_read.find("@42:") != std::string::npos) {
				break;
			}
            output += line_read;
        }
    }
    c.wait();
	exit_code = c.exit_code();
	 // Remove trailing null character(s), if any
    while (!output.empty() && output.back() == '\0')
        output.pop_back();
    return {output, exit_code};
}

std::pair<std::string, int> Tester::get_valgrind(const std::string& minishell_path, const std::string& cmd) {
	Tester test_shell;
	boost::process::opstream in_stream;
	boost::process::ipstream out_stream;
	boost::process::ipstream err_stream;
    std::string output;
    std::string line_read;
    boost::process::child c("valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp " + minishell_path,
        boost::process::std_in < in_stream,
        boost::process::std_out > out_stream,
        boost::process::std_err > err_stream,
        boost::process::shell
    );

    // Send the command to minishell
    in_stream << cmd << std::endl;
    in_stream.pipe().close();

    // Read the output from minishell
    while (out_stream && std::getline(out_stream, line_read)) {
        output += line_read + "\n";
    }

    // Read Valgrind's error output (if any)
    std::string valgrind_output;
    while (err_stream && std::getline(err_stream, line_read)) {
        valgrind_output += line_read + "\n";
    }

    // Wait for the process to finish
    c.wait();
    test_shell.valgrind_exit_status = c.exit_code();


    // Return the output and exit code
    return {valgrind_output, test_shell.valgrind_exit_status};
}