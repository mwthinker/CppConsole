cmake_minimum_required(VERSION 3.14)
# 3.14 support for Visual Studio 2019

set(VCPKG_ROOT $ENV{VCPKG_ROOT})
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
	set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
		CACHE STRING ""
	)
	message(STATUS "Uses VCPKG CMAKE_TOOLCHAIN_FILE")
endif()

project(CppConsole
	DESCRIPTION
		"A C++ library for input and output to the console"
	LANGUAGES
		CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(CppConsole
	src/console/console.cpp
	src/console/console.h
)

if (NOT MSVC)
	find_package(Curses REQUIRED)
endif ()

target_include_directories(CppConsole
	PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
	PRIVATE
		${CURSES_INCLUDE_DIR}
)
	
target_link_libraries(CppConsole
	PUBLIC
		${CURSES_LIBRARIES}
)

message(STATUS "CppConsole_Example is available to add: -DCppConsole_Example=1")
option(CppConsole_Example "Add CppConsole_Example project." OFF)
if (CppConsole_Example)
	add_subdirectory(CppConsole_Example)
endif (CppConsole_Example)
