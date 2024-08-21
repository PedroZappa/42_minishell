cmake_minimum_required(VERSION 3.8)

set(${This} minishell_builder)
# List of languages supported by this project (C & C++).
project(${This} C CXX)

# Set Compiler Flags for C
add_library(c_flags INTERFACE)
target_compile_features(c_flags INTERFACE c_std_11)
# Add Compiler warning flags
set(gcc_flags "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(lnk_flags "$<LINK_LANGUAGE:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
target_compile_options(c_flags INTERFACE
  "$<${gcc_flags}:$<BUILD_INTERFACE:-Wall;-Wextra;-Werror>>"
  "$<${lnk_flags}:$<BUILD_INTERFACE:-lgtest;-lgmock;-pthread>>"
)

# Import External Project
include(ExternalProject)
ExternalProject_Add(minishell
    SOURCE_DIR ${CMAKE_SOURCE_DIR}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE}
    INSTALL_COMMAND ""
    BUILD_IN_SOURCE 1
)

# Create Target for minishell executable
add_custom_target(minishell_target
    DEPENDS ${CMAKE_SOURCE_DIR}
)

# Create Interface Library
add_library(external_lib INTERFACE)
add_dependencies(external_lib minishell_target)
target_link_libraries(external_lib INTERFACE ${CMAKE_SOURCE_DIR})

message("Source dir of minishell = ${SOURCE_DIR}")
message("Binary dir of minishell = ${MINISHELL_BINARY}")

## Link GoogleTest libraries
add_subdirectory(googletest)
enable_testing()
add_subdirectory(tests)

add_test(
	NAME exec_test
    COMMAND minishell
)
