cmake_minimum_required(VERSION 3.1...3.12)
project(CppConsole
	DESCRIPTION
		"A C++ library for input and output to the console"
	LANGUAGES
		CXX
)
set(CMAKE_MODULE_PATH
	${CMAKE_MODULE_PATH}
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
	src/console/console.cpp
	src/console/console.h
)

add_library(CppConsole ${SOURCES})

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

option(CppConsoleTest "ConsoleTest project is added" OFF)

if (CppConsoleTest)
	set(SOURCES_TEST
		srcTest/main.cpp
	)	
	add_executable(CppConsoleTest ${SOURCES_TEST})
	
	target_include_directories(CppConsoleTest
		PRIVATE
			${CMAKE_CURRENT_SOURCE_DIR}/srcTest
	)
	
	target_link_libraries(CppConsoleTest CppConsole)
endif ()
