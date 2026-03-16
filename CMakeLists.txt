cmake_minimum_required(VERSION 3.30)
project(SRR_Interpreter)

set(CMAKE_CXX_STANDARD 26)

add_executable(SRR_Interpreter main.cpp
        Token.cpp
        Token.h
        Lexer.cpp
        Lexer.h
        Parser.cpp
        Parser.h
        AST-Nodes.h
)
