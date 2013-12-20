#!/usr/bin/python
import os, sys

os.chdir(sys.path[0])
os.system("gcc -Wall -I../src -o ../bin/test.bin ../src/*.c example.c")

