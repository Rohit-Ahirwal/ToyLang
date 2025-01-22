cmake_minimum_required(VERSION 3.10)
project(ToyLang)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

include_directories(includes)

add_executable(ToyLang
    src/main.cpp
    src/lexer/lexer.cpp
    src/parser/parser.cpp
    src/evaluator/evaluator.cpp
    src/symbol/symbol.cpp
)
