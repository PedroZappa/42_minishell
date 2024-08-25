#include "tester.hpp"

std::map<int, std::string> ListTestSuites();

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
	std::cout << "GoogleTest version: " << LINUX_VERSION_MAJOR << std::endl;
    std::cout << "Boost version: " << BOOST_LIB_VERSION;

	// Print Tester Header
	std::cout << GRN << R"(
 __  __ _      _    _        _ _ 
|  \/  (_)_ _ (_)__| |_  ___| | |
| |\/| | | ' \| (_-< ' \/ -_) | |
|_|__|_|_|_||_|_/__/_||_\___|_|_|
|_   _|__ __| |_ ___ _ _         
  | |/ -_|_-<  _/ -_) '_|        
  |_|\___/__/\__\___|_|          
)" << NC << std::endl;
	std::cout << MAG"By: " << NC << "passunca & gfragoso" << std::endl;
    while (true) {
		// List test suites
		std::map<int, std::string> test_suites = ListTestSuites();

        std::cout << "\nSelect test suites to run (e.g., 1 2) or press Enter to exit: ";
        std::string input;
        std::getline(std::cin, input);

        if (input.empty() || input == "exit") {
            std::cout << "Exiting..." << std::endl;
            break;
        }

        std::set<std::string> selected_suites;
        std::stringstream ss(input);
        int choice;

        while (ss >> choice) {
            if (test_suites.find(choice) != test_suites.end()) {
                selected_suites.insert(test_suites[choice]);
            } else {
                std::cout << RED"Invalid selection '" << choice << "'. Please try again...\n" << NC;
            }
        }

        if (selected_suites.empty()) {
            std::cout << "No valid test suites selected. Please try again." << std::endl;
            continue;
        }

        // Filter the tests to only run the selected suites
        ::testing::GTEST_FLAG(filter) = "";
        for (const auto& suite : selected_suites) {
            ::testing::GTEST_FLAG(filter) += suite + ".*:";
        }

        ::testing::GTEST_FLAG(filter).pop_back();  // Remove trailing ':'

        std::cout << "Running selected tests...\n";
        RUN_ALL_TESTS();

		// Reset the filter
		::testing::GTEST_FLAG(filter) = "";
    }

    return 0;
}

std::map<int, std::string> ListTestSuites() {
    std::map<int, std::string> test_suites;
    int count = 1;
    ::testing::UnitTest& unit_test = *::testing::UnitTest::GetInstance();
    
	std::cout << std::endl;
    for (int i = 0; i < unit_test.total_test_suite_count(); ++i) {
        const ::testing::TestSuite* test_suite = unit_test.GetTestSuite(i);
        test_suites[count] = test_suite->name();
        std::cout << YEL << count << ". " << test_suite->name() << NC << std::endl;
		std::cout << "    " << test_suite->total_test_count() << " tests" << std::endl;
        count++;
    }

    return test_suites;
}
