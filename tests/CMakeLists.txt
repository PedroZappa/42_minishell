cmake_minimum_required(VERSION 3.30)

set(${This} minishell_tester)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Werror")

# BUILD SOURCES
set(Sources
	Tester.cpp
	Tester.hpp
	Tests.cpp
)

# BUILD EXECUTABLE
add_executable(${This} ${Sources})
# LINK LIBRARIES
target_link_libraries(${This}
	minishell_lib
	gtest_main
)

add_test(Test
	NAME ${This}
	COMMAND ${This}
)
