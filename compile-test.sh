#!/bin/sh -e
gcc src/*.c test/test-all.c -o build/test -lcmocka -I. -z noexecstack
./build/test
