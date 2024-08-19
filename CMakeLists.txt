cmake_minimum_required(VERSION 3.8)

set(${This} minishell_tester)
# List of languages supported by this project (C & C++).
project(${This} C CXX)
# Set Language Versions
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)	# Useful when linking libraries to executables

# Add minishell executable
set(MINISHELL_EXEC "../minishell")
add_custom_target(run_yo
	COMMAND ${MINISHELL_EXEC}
)
add_library(${This}_lib STATIC ${MINISHELL_EXEC})

# Set the path to bash executable
find_program(BASH_EXECUTABLE bash)

# Ensure bash is found
if(NOT BASH_EXECUTABLE)
    message(FATAL_ERROR "Bash not found!")
endif()

# Pass the path to bash to the test executable
target_compile_definitions(${This} PRIVATE BASH_PATH="${BASH_EXECUTABLE}")

# # Link GoogleTest libraries
add_subdirectory(googletest)
enable_testing()
add_subdirectory(tests)

add_test(
	NAME Minishell_exec_test
    COMMAND ls
)
