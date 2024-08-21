cmake_minimum_required(VERSION 3.8)

set(${This} minishell_builder)
# List of languages supported by this project (C & C++).
project(${This} C CXX)

# Set Compiler Flags for C
add_library(c_flags INTERFACE)
target_compile_features(c_flags INTERFACE c_std_11)
# Add Compiler warning flags
set(gcc_flags "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
target_compile_options(c_flags INTERFACE
  "$<${gcc_flags}:$<BUILD_INTERFACE:-Wall;-Wextra;-Werror>>"
)

# Import External Project
include(ExternalProject)
ExternalProject_Add(
    external_project
    SOURCE_DIR ${CMAKE_SOURCE_DIR}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE}
    INSTALL_COMMAND ""
    BUILD_IN_SOURCE 1
)

# ExternalProject_Get_property(minishell BINARY_DIR SOURCE_DIR)
# set(MINISHELL_BINARY "${BINARY_DIR}/minishell")

message("Source dir of minishell = ${SOURCE_DIR}")
message("Binary dir of minishell = ${MINISHELL_BINARY}")

## Link GoogleTest libraries
add_subdirectory(googletest)
enable_testing()
add_subdirectory(tests)

add_test(
	NAME exec_test
    COMMAND ls
)
