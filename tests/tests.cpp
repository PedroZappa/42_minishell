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
	// Print the contents of the .temp/bash_failing_tests.txt and bash_passing_tests.txt file
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
		"echo \"\"",
        "echo '$'",
        "echo \"'$'\"",
        "echo \'\"'$'\"\'",
        "echo \"$\"",
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
		"echo ''''",
		"echo \"\"\"\"",
		"echo \"'$USER'\"",
		"echo '\"$USER\"'",
        "echo \"<< EOF\"",
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

// TEST(Parser, UnclosedQuotes) {
//     Tester shell_test;
//     std::vector<std::string> commands = {
// 		"echo '''",
// 		"echo \"\"\"",
//         "echo ''''42''",
//         "echo \"\"\"\"42\"\"",
//     };
//
//     for (const auto& cmd : commands) {
//         runTest(shell_test, cmd);
//     }
// 	leakReport();
// }

// Expander Tests
TEST(Expander, Basic) {
    Tester shell_test;
    std::vector<std::string> commands = {
		"$ZEDRO_VAR",
		// "ZEDRO_VAR",
        "echo ~",
        "echo ~/",
        "echo $",
        "echo \"$\"",
        "echo \'$\'",
        "echo $USER",
    };

    for (const auto& cmd : commands) {
        runTest(shell_test, cmd);
    }
	leakReport();
}

// TEST(Expander, Advanced) {
// 	Tester shell_test;
// 	std::vector<std::string> commands = {
//         "echo $USER$USER",
//         "echo $USER'$USER'",
//         "echo '$USER'$USER",
//         "echo $USER \"$HOME\"",
//         "echo \'$USER\'$USER",
//         "echo \'$USER\'\"$USER\"$USER\"$USER\"$USER\"$USER\"$USER\"$USER\"$USER\"$USER",
// 	};
//
// 	for (const auto& cmd : commands) {
// 		runTest(shell_test, cmd);
// 	}
// 	leakReport();
// }

// TEST(Expander, WithPipesRedirects) {
//     Tester shell_test;
//     std::vector<std::string> commands = {
// 		"cat < Makefile | grep NAME | grep $",
// 		"cat < Makefile | grep $novar NAME",
// 		"cat < a.txt | grep $USER",
//     };
//
//     for (const auto& cmd : commands) {
//         runTest(shell_test, cmd);
//     }
// 	leakReport();
// }

// TEST(Expander, WithHereDoc) {
//     Tester shell_test;
//     std::vector<std::string> commands = {
// 		"cat << $USER",
// 		"cat << a $USER",
// 		"cat << a '$USER'",
// 		"cat << a \"$USER\"",
// 		"cat << a $VOID_VAR",
//     };
//
//     for (const auto& cmd : commands) {
//         runTest(shell_test, cmd);
//     }
// 	leakReport();
// }

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
		// "\"ls -l\"",
		"\"\"ls -l\"\"",
		// "\"\"\"ls -l\"\"\"",
		"\"\"\"\"ls -l\"\"\"\"",
		// "ls\" -l\"",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
}

// TEST(Commands, InDoubleQuotes_Advanced) {
// 	Tester shell_test;
// 	std::vector<std::string> commands = {
// 		"ls > \"a\"z",
// 		"ls | \"a\"z",
// 		"ls > \"$USER\"",
// 		"ls | \"$USER\"",
// 		"ls > \'$USER\'",
// 		"ls | \'$USER\'",
// 		"echo ls\"\'$USER\'\"",
// 		"echo ls\"\"\'$USER\'\"\"z",
// 		"echo ls\'\'\"$USER\"\'\'",
// 	};
//
// 	for (const auto& cmd : commands) {
// 		runTest(shell_test, cmd);
// 	}
// 	leakReport();
// }

TEST(Commands, InSingleQuotes) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"\'ls\'",
		"\'\'ls\'\'",
		"\'\'\'ls\'\'\'",
		"\'\'\'\'ls\'\'\'\'",
		// "\'ls -l\'",
		"\'\'ls -l\'\'",
		// "\'\'\'ls -l\'\'\'",
		"\'\'\'\'ls -l\'\'\'\'",
		"l\'s\'",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
}

TEST(Commands, WithPipes) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"ls | wc -l",
		"ls | cat | wc -l",
		"ls | wc -l | cat",
		// "ls | wc |",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
}

TEST(Commands, WithRedirection) {
	Tester shell_test;
	std::vector<std::string> commands = {
		// "ls <",
		// "ls >",
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

// //
// BUILTINS
// //
TEST(Builtins_echo, basic) {
    Tester shell_test;
    std::vector<std::string> commands = {
        "echo",
        "echo ''",
        "echo \"\"",
        "echo \"yo\"",
        "echo 'yo'",
        "echo 42' '42",
        "echo 42\" \"42",
		"echo ~",
		"echo ~/",
		"echo ~/696969",
		"echo ~696969",
        // "echo -n yo",
        "echo -n -n -n -n",
        // "echo --n yo",
        "echo -n2 -n yo",
        "echo --nnnnnnnnnnnnnn",
        // "echo '-n' yo",
        "echo '-n ' yo",
        "echo '-n  ' yo",
        "echo \"n\" yo",
        "echo \"n \" yo",
        "echo \"n  \" yo",
    };

    for (const auto& cmd : commands) {
        runTest(shell_test, cmd);
    }
	leakReport();
}

TEST(Builtins_echo, advanced) {
    Tester shell_test;
    std::vector<std::string> commands = {
        "echo you are $USER",
        "echo $USER$USER",
        "echo $USER'$USER'",
        "echo \"Yo Whirl\"",
        "echo \"Yo\" dudes and dudettes!",
        "echo \'yo $USER\'",
        "echo \'yo $USER  \'",
        "echo \"$USER\"",
        "echo \"yo $USER\"",
        "echo \"yo $USER  \"",
        "echo \"yo $USER\"",
        "echo \"yo $USER\" ",
        "echo \"$USER\"\'$USER\'",
        "echo \"$USER\"\'$USER\'$USER",
        "echo \"$USER\"$USER\'$USER\'",
		// "echo $\'USER\'",
		"echo $666HOME",
    };

    for (const auto& cmd : commands) {
        runTest(shell_test, cmd);
    }
	leakReport();

}

TEST(Builtins_echo, withPipesRedirs) {
    Tester shell_test;
    std::vector<std::string> commands = {
		"echo \"ls > a.txt d 'a'\"",
		"echo \"ls > a.txt d \"a\"\"",
		"echo \"ls > '$USER' \"a\"\"",
		"echo '$HOME > ho | me.txt'",
		"echo | ls",
		"ls | echo",
		"nocmd | echo",
		// "echo | nocmd",
		"echo > a.txt",
		"echo whatever > a.txt",
		"echo < void_file",
		"echo << void_file",
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
TEST(Builtins_cd, basic) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"cd",
		"cd ~",
		"cd /",
		"cd /home",
		// "cd -",
		"cd ..",
		"cd \"\"",
		"cd src",
		// "cd void",
		// "cd a b",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
}

TEST(Builtins_cd, advanced) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"cd ../../../../../..",
		"cd | ls",
		"ls | cd",
		"cd | nocmd",
		"nocmd | cd",
		"cd -n | ls",		// invalid option -n
		"ls | cd -n",		// invalid option -n
		"cd a b | ls",		// invalid option and ls is executed
		"ls | cd a b",		// too many arguments
		"cd > a.txt",		// a.txt is created and cd is executed
		"cd < a.txt",		// cd is executed
		"cd < void_file",	// void_file does not exist
		"cd << a",			// Heredoc opens, written into then cd is executed
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
}

// ENV
TEST(Builtins_env, basic) {
	Tester shell_test;
	std::vector<std::string> commands = {
		// "env",
		"env -z",
		"env z",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
}

TEST(Builtins_env, withPipes) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"env | wc -l",
		"env | grep PATH",
		"env | grep VOID_VAR",
		"ls | env",
		// "env | ls",
		"nocmd | env",
		"env | nocmd",
		"env -z | ls",
		"ls | env -z",
		"env z | ls",
		"ls | env z",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
}

TEST(Builtins_env, env_withRedirection) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"env > a.txt",
		"env < a.txt",
		"env < void_file",
		"env << a",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
}

// PWD
TEST(Builtins_pwd, basic) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"pwd",
		// "pwd -n",
		"pwd z",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
}

TEST(Builtins_pwd, advanced) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"ls | pwd",
		"pwd | ls",
		"pwd > a.txt",
		"pwd < a.txt",
		"pwd < void_file",
		"pwd << a",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
}

// EXPORT
TEST(Builtins_export, export) {
	Tester shell_test;
	std::vector<std::string> commands = {
		// "export",			// list formated list of environment variables
		"export -z",			// invalid option
		// "export | grep XDG",
		// "export | wc -l",
		"ls | export",
		"export | ls",
		"export -z | ls",
		"ls | export -z",
		"export > a.txt",
		"export < a.txt",
		"export < void_file",
		"export << a",
		"export ZEDRO=69 | ls",
		"ls | export ZEDRO=69",
		"export ZEDRO=69",
		"export ZEDRO=\"Here is | a value < no input\"",
		"export ZEDRO=\"This is | a < value < no input\"",
		"export ZEDRO=",
		"export ZEDRO=$USER",
		"export -x ZEDRO=z",
		"export a.42 | ls",
		"ls | export a.42",
		"export V/A/R=zedro",
		"export =zedro",
		"export ZED1 ZED2=zedro",
		"export =",
		"export 1ZEDRO=test",
		"export Z2EDRO=test",
		"export TEST=ZEDRO",
		"export $ZZZ=void",
		"export a_test b_test",
		"export z=42 z=69",
		"export a=42 z=69",
		"export \"VAR= 42\"",
		"export \"VAR =42\"",
		"export \"\"",
		"export TEST1=u\"withdouble\" TEST2 TEST3=wihoutquotes TEST4=\"with spaces and expand $USER\" TEST5=\"ok, but it has more\" TEST6= TEST7='with single $PATH' = TEST8 9TEST9 TEST10=\"\" TEST11=too=many=equals TEST.12=\" \" TEST13='withsingle' TEST14",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
}

TEST(Builtins_unset, unset) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"unset",
		"unset ''",
		"unset \"\"",
		"unset $USER",
		"unset PATH",
		"unset a f z",
		"unset -z",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
}

TEST(Builtins_unset, unsetWithPipesRedirection) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"unset | ls",
		"ls | unset",
		"unset -z | ls",
		"ls | unset -z",
		"unset > a.txt",
		"unset < a.txt",
		"unset < void_file",
		"unset << a",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
}

// TEST(Builtins, unsetWithAND) {
// 	Tester shell_test;
// 	std::vector<std::string> commands = {
// 		"export ZEDRO=42 && unset ZEDRO | ls",
// 		"export ZEDRO=42 && ls | unset ZEDRO",
// 		"export ZEDRO=42 && unset ZEDRO=69",
// 		"export ZEDRO=42 && unset ZEDRO=",
// 		"export ZEDRO=42 && unset 42",
// 		"export ZEDRO=42 && unset ZE/DRO",
// 		"export ZEDRO=42 && unset =",
// 		"export ZEDRO=42 && unset ZEDRO",
// 		"unset HOME && echo $HOME && cd $HOME",
// 	};
//
// 	for (const auto& cmd : commands) {
// 		runTest(shell_test, cmd);
// 	}
// 	leakReport();
// }

// EXIT
TEST(Builtins_exit, basic) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"exit",
		"exit 42",
		"exit -42",
		"exit 42 42",
		"exit z",
		"exit -z",
		"exit z 42",
		"exit 42 z",
		"exit /",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
}

TEST(Builtins_exit, advanced) {
	Tester shell_test;
	std::vector<std::string> commands = {
		// "exit 0 | exit 1",
		"sleep 2 | exit",
		"exit > a.txt",
		"exit < a.txt",
		"exit < void_file",
		"exit << a",
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
		"cat < a.txt > b.txt",
		"cat < a.txt < c.txt > b.txt >> d.txt",
		"cat < a.txt < c.txt",
		// "cat >> b.txt",
		// "cat << a",
		"echo yo > > file",
		"echo yo >>> file",
		"echo yo > a.txt >> b.txt",
		"echo yo >> a.txt > b.txt",
		"echo yo > $ZEDRO_VAR",
		"ls > a.txt -al",
		"> a.txt",
		"<< a > a.txt",
		"< void_file $NOVAR",
		"$VOID_VAR > b.txt",
		"$VOID_VAR ls",
		"ls > src",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
}

TEST(Redirection, WithPipes) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"cat < a.txt | sort < c.txt",
		"cat << a | sort",
		"cat << a | sort < a.txt",
		"cat << a | sort > a.txt",
		"cat << a | sort << b",
		"< a.txt cat | < b.txt cat",
		"ls | $ZEDRO_VAR",
		"ls | grep a | grep M > a.txt",
		"ls > a.txt | grep a | grep M",
		"ls | grep a > a.txt | grep M",
		"ls | grep a > a.txt | grep M > b.txt",
		"cat < Makefile | cat < README.md",
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
		// "cat | cat | ls",
		"ls | grep a | grep k | grep e",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
}

TEST(ExitCodes, Basic) {
	Tester shell_test;
	std::vector<std::string> commands = {
		"yo",
		"nocmd | nocmd",
		"$VOID_VAR",
		"cat < void_file",
		"nocmd < void_file",
		"expr $? + $?",
	};

	for (const auto& cmd : commands) {
		runTest(shell_test, cmd);
	}
	leakReport();
}
