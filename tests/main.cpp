#include "tester.hpp"

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	std::cout << "Boost version: " << BOOST_LIB_VERSION << std::endl;

	// Instantiate the Tester object
    Tester shell_test;

    // Use the shell_test object to call the ProcessTest method with a sample command
    std::string command = "../minishell";  // Adjust the command or arguments as needed
	std::string cmd = "echo 'Hello, Whirl!'";
	// shell_test.ProcessTest(cmd);
	return RUN_ALL_TESTS();
}
