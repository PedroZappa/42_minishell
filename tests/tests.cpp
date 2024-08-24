#include "tester.hpp"

// Test test case
TEST(TesterTests, BasicFunctionality) {
    Tester shell_test;
    // std::string cmd = "echo 'Hello, Whirl!\nyo'";
    std::string cmd = "ls -al";

    shell_test.Test(cmd);
}

std::vector<std::string> commands = {
    "echo",
    "echo ~",
    "echo ~/",
    "echo \'", 
    "echo -n2 -n hey",
    "echo \"new line.\\ntab.\\t backslash: \\\\\"",
    "echo -n yo",
    "echo -n -n -n -n",
    "echo --n yo",
    "echo -nn yo",
    "echo '-n' yo",
    "echo '-n ' yo",
    "echo '-n  ' yo",
    "echo you are $USER",
    "echo $USER$USER",
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
// Builtin Tests
// TEST(Builtins, Echo) {
//     Tester shell_test;
//
//     auto runTest = [&shell_test](const std::string& cmd) {
//         // shell_test.Test(cmd);
// 		std::string bash_output = shell_test.get_bash_output(cmd);
// 		std::string minishell_output = shell_test.get_minishell_output(bash_output, cmd);
// 		EXPECT_EQ(bash_output, minishell_output);
//     };
//
//     for (const auto& cmd : commands) {
//         runTest(cmd);
//     }
// }
