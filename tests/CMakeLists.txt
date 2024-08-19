cmake_minimum_required(VERSION 3.22)

set(${This} minishell_tester)
# Find and include GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Werror")

# BUILD SOURCES
set(Sources
	Tester.cpp
	Tester.hpp
	Tests.cpp
)

# Build the test executable
add_executable(${This} ${Sources})

# Link the test executable against GTest
target_link_libraries(minishell_tester
    GTest::gtest_main  # Link GoogleTest
)

# Add a test that uses the `minishell` executable
add_test(
	NAME CompareWithBashTest
	COMMAND minishell_tester
)

# Specify the path to the minishell binary built by your Makefile
set_tests_properties(CompareWithBashTest PROPERTIES 
	ENVIRONMENT "MINISHELL_BINARY=${CMAKE_SOURCE_DIR}/minishell"
)

# BUILD EXECUTABLE
add_executable(${This} ${Sources})

add_test(Test
	NAME ${This}
	COMMAND ${This}
)
