cmake_minimum_required(VERSION 3.14)
project(CppConsole_Example
	DESCRIPTION
		"A example of using the Console library"
	LANGUAGES
		CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CppConsole_Example
	src/main.cpp
)
	
target_link_libraries(CppConsole_Example
	PRIVATE
		CppConsole
)
