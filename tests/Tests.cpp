#include <gtest/gtest.h>
#include <iostream>
#include <array>
#include <string>
#include <memory>

// BASH_PATH will be defined from CMakeLists.txt
#ifndef BASH_PATH
# define BASH_PATH "/bin/bash"
#endif

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
