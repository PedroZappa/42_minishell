#include <gtest/gtest.h>
#include <boost/version.hpp>
#include "tester.hpp"

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

std::string Tester::exec(const char* cmd) {
	std::array<char, 128> buffer;
	std::string result;

	
	// std::cout << "Boost version: " << BOOST_LIB_VERSION << std::endl;

	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}
	while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
		result += buffer.data();
	}
	return result;
}

