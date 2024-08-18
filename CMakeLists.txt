cmake_minimum_required(VERSION 3.30)

# List of languages supported by this project (C & C++).
set(${This} minishell)
project(${This} C CXX)
# Set Language Versions
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)	# Useful when linking libraries to executables
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra -Werror")
set(CMAKE_C_COMPILE_OBJECT
    "<CMAKE_C_COMPILER> <DEFINES> <FLAGS> -O2 -o <OBJECT> <SOURCE>"
)
set(CMAKE_C_CREATE_STATIC_LIBRARY
    "<CMAKE_AR> rcs <TARGET> <OBJECTS>"
)

# Executable
set(SRC_PATH src)
set(LIBFT_PATH lib/libft)

# Include Directories
include_directories(${PROJECT_SOURCE_DIR}/inc)

# Sources
file(GLOB SOURCES "${SRC_PATH}/*.c")
add_library(${This}_lib STATIC ${SOURCES})

# Link GoogleTest libraries
add_subdirectory(googletest)
enable_testing()
add_test(NAME minishell_test COMMAND ${PROJECT_NAME})
