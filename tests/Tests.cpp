#include <gtest/gtest.h>
#include <iostream>
#include <array>
#include <string>
#include <memory>

// BASH_PATH will be defined from CMakeLists.txt
#ifndef BASH_PATH
# define BASH_PATH "/bin/bash"
#endif

std::string run_command(const std::string& shell, const std::string& command) {
    std::array<char, 128> buffer;
    std::string result;
    
    // Prepare the full command to execute the shell with the provided command
    std::string full_command = shell + " -c \"" + command + "\"";
    
    std::shared_ptr<FILE> pipe(popen(full_command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    
    // Read the command output
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    return result;
}

TEST(MiniShellTest, CompareOutputs) {
    // Define the command to be tested
    std::string command = "echo Hello World";

    // Run the command with minishell
    std::string minishell_output = run_command("./minishell", command);

    // Run the command with bash
    std::string bash_output = run_command(BASH_PATH, command);

    // Compare outputs
    ASSERT_EQ(minishell_output, bash_output) << "Output mismatch between minishell and bash";
}
