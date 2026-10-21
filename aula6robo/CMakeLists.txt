cmake_minimum_required(VERSION 3.10)
project(MiniCompilador)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(aula6 aula6.cpp lexer.cpp parser.cpp symtable.cpp )


