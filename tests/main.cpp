#include <gtest/gtest.h>
#include "tester.hpp"

std::string Tester::exec(const char* cmd) {
	std::array<char, 128> buffer;
	std::string result;

	

	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}
	while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
		result += buffer.data();
	}
	return result;
}

