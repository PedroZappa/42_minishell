cmake_minimum_required(VERSION 3.8)

set(${This} minishell_tester)
# Find and include GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# BUILD SOURCES
set(Sources
	Tester.cpp
	Tester.hpp
	Tests.cpp
)

# Add the test executable
add_executable(${This} ${Sources})

# Ensure minishell is built before running the tests
# add_dependencies(minishell_builder)

# Link the test executable against GTest
target_link_libraries(
    gtest_main  # Link GoogleTest
)

# Add a test that uses the `minishell` executable
add_test(test_yo
	NAME CompareWithBashTest
	COMMAND ${This}
)

# Specify the path to the minishell binary built by your Makefile
# set_tests_properties(CompareWithBashTest PROPERTIES 
# 	ENVIRONMENT "MINISHELL_BINARY=${MINISHELL_BINARY}"
# )

# IMPORT EXECUTABLE
set(Exec
	minishell
)
