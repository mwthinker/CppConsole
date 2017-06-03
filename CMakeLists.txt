cmake_minimum_required(VERSION 2.8)
project(CppConsole)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/)
if (NOT MSVC)
	set(CMAKE_CXX_FLAGS "-std=c++1y")
	option(Debug "Set projects to debug mode.")
	if (Debug)
		set(CMAKE_BUILD_TYPE "Debug" CACHE INTERNAL "Build type.")
		add_definitions(-D_DEBUG)
	else ()
		set(CMAKE_BUILD_TYPE "Release" CACHE INTERNAL "Build type.")
	endif ()
endif ()

# Source files.
set(SOURCES
	src/console/console.cpp
	src/console/console.h
)

set(SOURCES_TEST
	srcTest/console/main.cpp
)

option(ConsoleTest "ConsoleTest project is added" OFF)

if (NOT MSVC)
	find_package(Curses REQUIRED)
	include_directories(${CURSES_INCLUDE_DIR})
endif ()

add_library(Console ${SOURCES})

if (ConsoleTest)
	include_directories(src)
	add_executable(ConsoleTest ${SOURCES_TEST})

	if (MSVC)
		target_link_libraries(ConsoleTest Console)
	else ()
		target_link_libraries(ConsoleTest Console ${CURSES_LIBRARIES})
	endif ()
endif ()
