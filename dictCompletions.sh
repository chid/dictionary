#!/bin/sh
# This file tests the dictComlpetionsN
gcc -o cov_word words.c dictionary.c dictionary.h -g -Wall -fprofile-arcs -ftest-coverage
./cov_word d < tc6
./cov_word ap  < tc6
./cov_word ape  < tc6
./cov_word delta < tc6
gcov dictionary.c
vi +/138 dictionary.c.gcov 
