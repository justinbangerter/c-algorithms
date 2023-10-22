#!/bin/sh -e
gcc src/*.c test/*.c -o build/test -lcmocka -I.
./build/test
