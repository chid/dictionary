#!/bin/sh
gcc -o cov_word words.c dictionary.c dictionary.h -g -Wall -fprofile-arcs -ftest-coverage
# ./cov_word $1 < tc3
./cov_word $1 < tc5
gcov dictionary.c
vi +/445 dictionary.c.gcov 
