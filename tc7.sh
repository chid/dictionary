#!/bin/sh
# This file tests the dictComlpetionsN
gcc -o cov_word words.c dictionary.c dictionary.h -g -Wall -fprofile-arcs -ftest-coverage
./cov_word cat < tc6
gcov dictionary.c
vi +/127 dictionary.c.gcov 
