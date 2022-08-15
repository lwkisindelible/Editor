cmake_minimum_required(VERSION 3.22)
project(editor_test2)

set(CMAKE_CXX_STANDARD 14)

add_executable(editor_test2 main.cpp test/scanner.cpp test/scanner.h Parser.cpp Parser.h common.cpp common.h test/Symtable.cpp test/Symtable.h Object.cpp Object.h lexical.cpp lexical.h main.h)

set(CMAKE_EXE_LINKER_FLAGS"-static")
add_executable(main main.cpp)