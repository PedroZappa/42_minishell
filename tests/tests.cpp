#include "tester.hpp"

// Define a reusable runTest function
void runTest(Tester& shell_test, const std::string& cmd) {
    std::pair<std::string, int> bash_output = shell_test.get_bash_output(cmd);
    std::pair<std::string, int> minishell_output = shell_test.get_minishell_output(bash_output.first, cmd);
	// std::pair<std::string, int> valgrind_output = shell_test.get_valgrind(shell_test.minishell_path, cmd);

    std::cout << YEL << cmd << NC << std::endl;
    EXPECT_EQ(bash_output.first, minishell_output.first);
    EXPECT_EQ(bash_output.second, minishell_output.second);
}

// Test test case
TEST(TesterTest, BasicFunctionality) {
    Tester shell_test;
    // std::string cmd = "echo 'Hello, Whirl!'";
    // std::string cmd = "ls -al";
    std::string cmd = "echo \"'$USER'\"";

    runTest(shell_test, cmd);
	// shell_test.Test(cmd);
}

// Parser Tests
TEST(Parser, Basic) {
    Tester shell_test;
    std::vector<std::string> commands = {
        "echo",
        "echo hello world !",
        "echo 42test ' 21 '",
        "echo 42   42    '  '42",
        "echo '$?'",
        "echo '${$?}'",
        "echo '$USER'",
        "echo ''",
        "echo $",
        "echo '$'",
        "echo $USER",
        "echo '$USER'",
        "echo '$USER$USER'",
        "echo $HOME$HOME",
		"echo \"yo\"",
		"echo \"yo \"",
		"echo \"yo $USER\"",
    };

    for (const auto& cmd : commands) {
        runTest(shell_test, cmd);
    }
}

TEST(Parser, Advanced) {
    Tester shell_test;
    std::vector<std::string> commands = {
        "echo \"<< EOF\"",
        "echo $USER '>> file.txt' \"|\"",
        "echo '42 $USER' \">\" file.txt",
        "echo 'echo $v >> file.txt'",
        "echo ' \"\" ' '42'",
        "echo '<< | | >>'42",
        "echo ''''42''",
        "echo '$'",
        "echo \"42\"'$'\"42\"",
        "echo a'b'c'd'e'f'g'h'i'j'k'l'm'n'o'p'q'r's't'",
        "echo \" \"'$USER\"'\"42 \" ''\"  | << -1\"",
        "echo \"$USER\"'$USER'$USER",
        "echo '$USER \"$HOME\"'",
        "echo \"$USER 42\" '\"$USER\"'",
        "echo ''\"\"'\"'\"'\"",
        "echo \"new line.\\ntab.\\t backslash: \\\\\"",
    };

    for (const auto& cmd : commands) {
        runTest(shell_test, cmd);
    }
}

// Expander Tests
TEST(Expander, Basic) {
    Tester shell_test;
    std::vector<std::string> commands = {
        "echo ~",
        "echo ~/",
        "echo $",
        "echo $USER",
        "echo $USER \"$HOME\"",
        "echo $USER$USER",
        "echo $USER'$USER'",
        "echo '$USER'$USER"
    };

    for (const auto& cmd : commands) {
        runTest(shell_test, cmd);
    }
}

// Builtin Tests
TEST(Builtins, echo) {
    Tester shell_test;
    std::vector<std::string> commands = {
        "echo",
        "echo \'", 
        "echo -n2 -n hey",
        "echo -n yo",
        "echo -n -n -n -n",
        "echo --n yo",
        "echo -nn yo",
        "echo '-n' yo",
        "echo '-n ' yo",
        "echo '-n  ' yo",
        "echo 42' '42",
        "echo you are $USER",
        "echo $USER$USER",
        "echo $USER'$USER'",
        "echo \'yo $USER\'",
        "echo \'yo $USER  \'",
        "echo \'$USER\'$USER",
        "echo \'$USER\'\"$USER\"$USER\"$USER\"$USER\"$USER\"$USER\"$USER\"$USER\"$USER",
        "echo \"yo\"",
        "echo \"$USER\"",
        "echo \"yo $USER\"",
        "echo \"yo $USER  \"",
        "echo \"-n\" yo",
        "echo \"-n \" yo",
        "echo \"-n  \" yo",
        "echo \" -n  \" yo ",
        "echo \"yo $USER\"",
        "echo \"yo $USER\" ",
        "echo \"$USER\"\'$USER\'",
        "echo \"$USER\"\'$USER\'$USER",
        "echo \"$USER\"$USER\'$USER\'"
    };

    for (const auto& cmd : commands) {
        runTest(shell_test, cmd);
    }
}

// Tests cd
TEST(Builtins, cd) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"cd",
		"cd ~",
		"cd /",
		"cd /home",
		"cd /home/zedr0",
		"cd /home/zedr0/C0D3/42",
		"cd /home/zedr0/C0D3/42/Projects",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
}

TEST(Builtins, Exit) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"exit",
		"exit 42",
		"exit -42",
		"exit 42 42",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
}

TEST(ExitCodes, Basic) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"exit 0",
		"echo 42",
		"cat 42 > not_executable_file",
		"cat 42 > not_existing_file",
		"./not_executable_file",
		"not_existing_command",
		"< not_existing_file",
		"> not_existing_file",
		">> not_existing_file",
		"< not_existing_file > not_existing_file2",
		"< not_existing_file >> not_existing_file2",
		"| echo 1",
		"| echo 1 | echo 2",
		"ls not_existing_file",
		"ls not_existing_file | echo 42 | cat",
		"ls not_existing_file | cat > not_executable_file",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
}
