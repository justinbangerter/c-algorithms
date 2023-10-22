#!/bin/sh -e
gcc *.c -o test -lcmocka -I.
./test
