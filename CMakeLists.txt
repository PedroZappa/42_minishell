cmake_minimum_required(VERSION 3.30)
# Set Language Versions
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)	# Useful when linking libraries to executables

# List of languages supported by this project (C & C++).
project(minishell C CXX)

# Add minishell executable
set(MINISHELL_EXEC "../minishell")
add_custom_target(run_yo
	COMMAND ${MINISHELL_EXEC}
)
add_library(${This}_lib STATIC ${MINISHELL_EXEC})

# # Link GoogleTest libraries
add_subdirectory(googletest)
enable_testing()
add_test(
	NAME Minishell_exec_test
    COMMAND ls
)
