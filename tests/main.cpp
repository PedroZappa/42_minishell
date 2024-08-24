#include "tester.hpp"

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	std::cout << "Boost version: " << BOOST_LIB_VERSION << std::endl;

	return RUN_ALL_TESTS();
}

// Test test case
TEST(TesterTests, BasicFunctionality) {
    Tester shell_test;
    std::string cmd = "echo 'Hello, Whirl!'";

    shell_test.minishell_path = "./minishell";  // Adjust path if necessary

    shell_test.ProcessTest(cmd);
}
