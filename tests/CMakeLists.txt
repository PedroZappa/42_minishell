cmake_minimum_required(VERSION 3.30)
project(minishell_tester)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE_TMP "${CMAKE_BUILD_TYPE}")
set(CMAKE_BUILD_TYPE "Release")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Include googletest
add_subdirectory(googletest)
include_directories(googletest/googletest/include)
include_directories(googletest/googlemock/include)

# Find & include Boost libraries
find_package(Boost 1.65 REQUIRED COMPONENTS filesystem system)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE_TMP})

add_executable(minishell_tester 
	main.cpp
	tester.cpp
	tester.hpp
	tests.cpp
)

target_link_libraries(minishell_tester
	gtest
	gtest_main
)

# Enable testing
enable_testing()
