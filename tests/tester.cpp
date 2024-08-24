#include "tester.hpp"

void Tester::ProcessTest(const std::string& minishell_cmd) {
    std::string bash_output = get_bash_output(minishell_cmd);
    std::string minishell_output = get_minishell_output(bash_output, minishell_cmd);
	
	std::cout << YEL"Bash Output :\n" << NC << bash_output << std::endl;
	std::cout << YEL"Minishell Output :\n" << NC << minishell_output << std::endl;

    if (bash_output != minishell_output) {
        std::cerr << RED"Outputs differ!" << NC << std::endl;
    } else {
        std::cout << GRN"Outputs match!" << NC << std::endl;
    }
}

std::string Tester::get_bash_output(const std::string& cmd) {
    std::string output;
    std::string line_read;
	boost::process::ipstream pipe_stream;
    boost::process::child c(cmd,
		boost::process::std_out > pipe_stream,
		boost::process::std_err > boost::process::null,
		boost::process::shell
	);

    while (pipe_stream && std::getline(pipe_stream, line_read)) {
        output += (line_read + "\n");
    }

    c.wait();
    return output;
}

std::string Tester::get_minishell_output(const std::string& bash_output, const std::string& cmd) {
    std::string output;
    std::string line_read;
	boost::process::ipstream pipe_stream;
    boost::process::opstream in_stream;
    boost::process::child c(minishell_path,
		boost::process::std_in < in_stream,
		boost::process::std_out > pipe_stream,
		boost::process::std_err > boost::process::null
	);

	// Send cmd to minishell
    in_stream << cmd << std::endl;
    in_stream.pipe().close();

    while (pipe_stream && std::getline(pipe_stream, line_read)) {
        output += (line_read + "\n");
        if (output.size() >= bash_output.size()) {
            break;
        }
    }

    c.wait();
    return output;
}
