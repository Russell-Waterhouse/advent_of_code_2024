
#!/bin/bash
set -e

# g++ -g aoc -c -std=c++23 -Wextra -Wall -Weffc++ -Werror -pedantic -pedantic-errors -Wconversion -Wsign-conversion -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align -Wunreachable-code -Winit-self -Wno-variadic-macros -Wno-parentheses -Wno-unused-function -Wno-unused-parameter -Wno-unused-variable -Wno-unused-value -Wno-unused-but-set-variable -Wno-unused-local-typedefs
g++ -g -o main main.cpp aoc_helper.cpp -std=c++23 -Wextra -Wall -Weffc++ -Werror -pedantic -pedantic-errors -Wconversion -Wsign-conversion -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align -Wunreachable-code -Winit-self -Wno-variadic-macros -Wno-parentheses -Wno-unused-function -Wno-unused-parameter -Wno-unused-variable -Wno-unused-value -Wno-unused-but-set-variable -Wno-unused-local-typedefs
