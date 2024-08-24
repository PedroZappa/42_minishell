#include <gtest/gtest.h>
#include <boost/version.hpp>
#include "tester.hpp"

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	std::cout << "Boost version: " << BOOST_LIB_VERSION << std::endl;

	return RUN_ALL_TESTS();
}
