#!/bin/bash
clang++ -c main.cpp
clang++ -o main main.o

./main shapeInput.txt

cmp --silent results.txt shapeTest.txt && echo '###All Tests Passed###' || echo '###You Failed###'
