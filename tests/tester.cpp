#include "tester.hpp"

void Tester::ProcessTest(const std::string& minishell_cmd) {
    std::string bash_output = get_bash_output(minishell_cmd);
    std::string minishell_output = get_minishell_output(bash_output, minishell_cmd);

    if (bash_output != minishell_output) {
        std::cerr << "Outputs differ!" << std::endl;
    } else {
        std::cout << "Outputs match!" << std::endl;
    }
}

std::string Tester::get_bash_output(const std::string& cmd) {
    std::string output;
	boost::process::ipstream pipe_stream;
    boost::process::child c(cmd, boost::process::std_out > pipe_stream, boost::process::std_err > boost::process::null, boost::process::shell);
    std::string line;

    while (pipe_stream && std::getline(pipe_stream, line)) {
        output += line + "\n";
    }

    c.wait();
    return output;
}

std::string Tester::get_minishell_output(const std::string& bash_output, const std::string& cmd) {
    std::string output;
	boost::process::ipstream pipe_stream;
    boost::process::opstream in_stream;
    boost::process::child c(minishell_cmd_, boost::process::std_in < in_stream, boost::process::std_out > pipe_stream, boost::process::std_err > boost::process::null);

    in_stream << cmd << std::endl;
    in_stream.pipe().close();

    std::string line;
    while (pipe_stream && std::getline(pipe_stream, line)) {
        output += line + "\n";
        if (output.size() >= bash_output.size()) {
            break;
        }
    }

    c.wait();
    return output;
}
