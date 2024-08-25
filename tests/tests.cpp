#include "tester.hpp"

// Test test case
TEST(TesterTest, BasicFunctionality) {
    Tester shell_test;
    std::string cmd = "echo 'Hello, Whirl!'";
    // std::string cmd = "ls -al";

    shell_test.Test(cmd);
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
        "echo $HOME",
        "echo $HOME$HOME",
        "echo $USER42",
        "echo $USER"
    };

    auto runTest = [&shell_test](const std::string& cmd) {
        std::string bash_output = shell_test.get_bash_output(cmd);
        std::string minishell_output = shell_test.get_minishell_output(bash_output, cmd);

		std::cout << YEL << cmd << NC << std::endl;
        EXPECT_EQ(bash_output, minishell_output);
    };

    for (const auto& cmd : commands) {
        runTest(cmd);
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

    auto runTest = [&shell_test](const std::string& cmd) {
        std::string bash_output = shell_test.get_bash_output(cmd);
        std::string minishell_output = shell_test.get_minishell_output(bash_output, cmd);

		std::cout << YEL << cmd << NC << std::endl;
        EXPECT_EQ(bash_output, minishell_output);
    };

    for (const auto& cmd : commands) {
        runTest(cmd);
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
		"echo '$USER'",
		"echo '$USER$USER'",
		"echo '$USER'$USER"
	};

	auto runTest = [&shell_test](const std::string& cmd) {
		std::string bash_output = shell_test.get_bash_output(cmd);
		std::string minishell_output = shell_test.get_minishell_output(bash_output, cmd);

		std::cout << YEL << cmd << NC << std::endl;
		EXPECT_EQ(bash_output, minishell_output);
	};

	for (const auto& cmd : commands) {
		runTest(cmd);
	}
}

// Builtin Tests
TEST(Builtins, Echo) {
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

    auto runTest = [&shell_test](const std::string& cmd) {
        // shell_test.Test(cmd);
		std::string bash_output = shell_test.get_bash_output(cmd);
		std::string minishell_output = shell_test.get_minishell_output(bash_output, cmd);

		std::cout << YEL << cmd << NC << std::endl;
		EXPECT_EQ(bash_output, minishell_output);
    };

    for (const auto& cmd : commands) {
        runTest(cmd);
    }
}

