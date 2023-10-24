#!/bin/sh -e
gcc src/*.c test/*.c -o build/test -lcmocka -I. -z noexecstack
./build/test
