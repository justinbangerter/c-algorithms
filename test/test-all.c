#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "./test-linked-list.c"


int main(void) {
    int llist_result = cmocka_run_group_tests(llist_tests, NULL, NULL);
    if (llist_result != 0) { return llist_result; }
    return 0;
}