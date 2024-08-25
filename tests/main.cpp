#include "tester.hpp"

std::map<int, std::string> ListTestSuites();

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	std::cout << "Boost version: " << BOOST_LIB_VERSION << std::endl;
	
	std::map<int, std::string> test_suites = ListTestSuites();

    std::cout << "\nSelect test suites to run (e.g., 1 2): ";
    std::string input;
    std::getline(std::cin, input);
    
    std::set<std::string> selected_suites;
    std::stringstream ss(input);
    int choice;

    while (ss >> choice) {
        if (test_suites.find(choice) != test_suites.end()) {
            selected_suites.insert(test_suites[choice]);
        } else {
            std::cout << "Invalid selection '" << choice << "'. Skipping...\n";
        }
    }

    if (selected_suites.empty()) {
        std::cout << "No valid test suites selected. Exiting..." << std::endl;
        return 0;
    }

    // Filter the tests to only run the selected suites
    ::testing::GTEST_FLAG(filter) = "";
    for (const auto& suite : selected_suites) {
        ::testing::GTEST_FLAG(filter) += suite + ".*:";
    }

    ::testing::GTEST_FLAG(filter).pop_back();  // Remove trailing ':'

    std::cout << "Running selected tests...\n";
	return RUN_ALL_TESTS();
}

std::map<int, std::string> ListTestSuites() {
    std::map<int, std::string> test_suites;
    int count = 1;
    ::testing::UnitTest& unit_test = *::testing::UnitTest::GetInstance();
    
    for (int i = 0; i < unit_test.total_test_suite_count(); ++i) {
        const ::testing::TestSuite* test_suite = unit_test.GetTestSuite(i);
        test_suites[count] = test_suite->name();
        std::cout << count << ". " << test_suite->name() << std::endl;
        count++;
    }

    return test_suites;
}
