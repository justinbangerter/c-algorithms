#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "linked-list.h"

/// Fixtures ///

static Node* fixture_int_list() {
    return Push((void*) 1, Push((void*) 2, EmptyList()));
}

/// Tests ///

static void create_empty_list(void **state) {
    Node* list = EmptyList();

    assert_null(list->val);

    FreeList(list);
}

static void create_string_nodes(void **state) {
    Node* head = Push("head", Push("tail", EmptyList()));

    assert_string_equal(head->val, "head");
    assert_string_equal(head->tail->val, "tail");

    FreeList(head);
}

static void create_int_nodes(void **state) {
    Node* head = fixture_int_list();

    assert_int_equal(head->val, 1);
    assert_int_equal(head->tail->val, 2);

    FreeList(head);
}

static void access_value_out_of_stack(void **state) {
    // list must be created in another function
    Node* head = fixture_int_list();

    assert_int_equal(head->val, 1);
    assert_int_equal(head->tail->val, 2);

    FreeList(head);
}

static void pop_node(void **state) {
    Node* head = fixture_int_list();
    Node* tail = Pop(head);

    assert_int_equal(head->val, 1);
    assert_null(head->tail);
    FreeList(head);

    assert_int_equal(tail->val, 2);
    FreeList(tail);
}

static void get_size(void **state) {
    Node* head = EmptyList();
    assert_int_equal(SizeOf(head), 0);
    head = Push((void*) 1, head);
    assert_int_equal(SizeOf(head), 1);

    FreeList(head);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(create_empty_list),
        cmocka_unit_test(create_string_nodes),
        cmocka_unit_test(create_int_nodes),
        cmocka_unit_test(access_value_out_of_stack),
        cmocka_unit_test(pop_node),
        cmocka_unit_test(get_size),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}