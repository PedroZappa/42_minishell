#include "tester.hpp"

int g_invalid_reads = 0;
int g_leaks = 0;
int g_fd = 0;

void runTest(Tester& shell_test, const std::string& cmd) {
    std::pair<std::string, int> bash_output = shell_test.get_bash_output(cmd);
    std::pair<std::string, int> minishell_output = shell_test.get_minishell_output(bash_output.first, cmd);
    std::pair<std::string, int> valgrind_output = shell_test.get_valgrind(shell_test.minishell_path, cmd);

    std::cout << YEL << cmd << NC << std::endl;
    EXPECT_EQ(bash_output.first, minishell_output.first);
    EXPECT_EQ(bash_output.second, minishell_output.second);

    if (!valgrind_output.first.empty()) {
        std::string invalid_read = "Invalid read of size";
        std::string malloc_err = ": malloc (in";
        // std::string fd_err = "Open file descriptor";

		if (valgrind_output.first.find(invalid_read) != std::string::npos) {
			std::cout << valgrind_output.first << std::endl;
			g_invalid_reads++;
		}
		if (valgrind_output.first.find(malloc_err) != std::string::npos) {
			std::cout << valgrind_output.first << std::endl;
			g_leaks++;
		}
        // size_t pos = 0;
        // while ((pos = valgrind_output.first.find(fd_err, pos)) != std::string::npos) {
        //     g_fd++;
        //     pos += fd_err.length(); // Move past the current match
        // }
        //
        // if (g_fd > 0) {
        //     std::cout << valgrind_output.first << std::endl;
        // }
    }
}

void leakReport() {
	std::cout << "Invalid reads: " << g_invalid_reads << std::endl;
	std::cout << "Leaks: " << (g_leaks - g_invalid_reads) << std::endl;
	std::cout << "Total fd: " << g_leaks << std::endl;
	g_invalid_reads = 0;
	g_leaks = 0;
	g_fd = 0;
}

// Test test case
TEST(TesterTest, BasicFunctionality) {
    Tester shell_test;
    std::string cmd = "echo 'Hello, Whirl!'";
    // std::string cmd = "ls -al";
    // std::string cmd = "echo \"'$USER'\"";

    runTest(shell_test, cmd);
	leakReport();
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
	leakReport();
}

TEST(Parser, Advanced) {
    Tester shell_test;
    std::vector<std::string> commands = {
        "echo '$'",
		"echo ''",
		"echo '''",
		"echo ''''",
		"echo \"'$USER'\"",
		"echo '\"$USER\"'",
        "echo \"<< EOF\"",
        "echo ''''42''",
        "echo $USER '>> file.txt' \"|\"",
        "echo '42 $USER' \">\" file.txt",
        "echo 'echo $v >> file.txt'",
        "echo ' \"\" ' '42'",
        "echo '<< | | >>'42",
        "echo \"42\"'$'\"42\"",
        "echo a'b'c'd'e'f'g'h'i'j'k'l'm'n'o'p'q'r's't'",
        "echo \" \"'$USER\"'\"42 \" ''\"  | << -1\"",
        "echo \"$USER\"'$USER'$USER",
        "echo '$USER \"$HOME\"'",
        "echo \"$USER 42\" '\"$USER\"'",
        "echo ''\"\"'\"'\"'\"",
    };

    for (const auto& cmd : commands) {
        runTest(shell_test, cmd);
    }
	leakReport();
}

// Expander Tests
TEST(Expander, Basic) {
    Tester shell_test;
    std::vector<std::string> commands = {
        "echo ~",
        "echo ~/",
        "echo $",
        "echo \"$\"",
        "echo $USER",
        "echo $USER \"$HOME\"",
        "echo $USER$USER",
        "echo $USER'$USER'",
        "echo '$USER'$USER"
    };

    for (const auto& cmd : commands) {
        runTest(shell_test, cmd);
    }
	leakReport();
}

// Test Executing Commands
TEST(Commands, Basic) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"/bin/ls -l",
		"ls -al",
		"ls -a -l",
		"touch a b c",
		"rm a b c",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
}

TEST(Commands, InDoubleQuotes_Basic) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"\"ls\"",
		"\"\"ls\"\"",
		"\"\"\"ls\"\"\"",
		"\"\"\"\"ls\"\"\"\"",
		"\"ls -l\"",
		"\"\"ls -l\"\"",
		"\"\"\"ls -l\"\"\"",
		"\"\"\"\"ls -l\"\"\"\"",
		"ls\" -l\"",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
}

TEST(Commands, InDoubleQuotes_Advanced) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"ls > \"a\"z",
		"ls | \"a\"z",
		"ls > \"$USER\"",
		"ls | \"$USER\"",
		"ls > \'$USER\'",
		"ls | \'$USER\'",
		"echo ls\"\'$USER\'\"",
		"echo ls\"\"\'$USER\'\"\"z",
		"echo ls\'\'\"$USER\"\'\'",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
}

TEST(Commands, InSingleQuotes) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"\'ls\'",
		"\'\'ls\'\'",
		"\'\'\'ls\'\'\'",
		"\'\'\'\'ls\'\'\'\'",
		"\'ls -l\'",
		"\'\'ls -l\'\'",
		"\'\'\'ls -l\'\'\'",
		"\'\'\'\'ls -l\'\'\'\'",
		"l\'s\'",
		"c$VAR Makefile (export VAR=at)"
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
}

TEST(Commands, WithPipes) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"ls | wc |",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
}

TEST(Commands, WithRedirection) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"ls <",
		"ls >",
		"ls < > a",
		"| ls",
		"echo $VOID_VAR",
		"echo $",
		"cat Makefile | grep vgdb",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
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
        "echo \"$USER\"$USER\'$USER\'",
		"echo $\'USER\'",
		"echo $666HOME",
		"z.txt",
		"~~minishell",
		"l  s",
    };

    for (const auto& cmd : commands) {
        runTest(shell_test, cmd);
    }
	leakReport();
}

// Tests cd
TEST(Builtins, cd) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"cd",
		"cd ~",
		"cd /",
		"cd /home",
		"cd -",
		"cd ..",
		"cd \"\""
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
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
	leakReport();
}


TEST(Redirection, Basic) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"echo 42 > 42",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
}

TEST(Pipes, Basic) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"env | grep USER",
		"cat .vgdbinit | grep info",
		"nocmd | ls",
		"ls | nocmd",
		"nonocmd | nocmd",
		"cat | cat | ls",
		"ls | grep a | grep k | grep e",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
}
