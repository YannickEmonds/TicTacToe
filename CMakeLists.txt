cmake_minimum_required(VERSION 3.12)

project( TicTacToe )

add_executable( ${PROJECT_NAME} main.cpp board.cpp )
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
# The following line is a workaround for cmake v3.11.4. More recent versions
# support C++20 as CXX_STANDARD.
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)
