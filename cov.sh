#!/bin/sh
gcc -o cov_word words.c dictionary.c dictionary.h -g -Wall -fprofile-arcs -ftest-coverage
