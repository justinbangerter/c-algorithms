#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/linked-list.h"

/// Fixtures ///

static LList* fixture_int_list() {
    return llist_push((void*) 1, llist_push((void*) 2, llist_create_list()));
}

/// Tests ///

static void create_empty_list(void **state) {
    LList* list = llist_create_list();

    assert_null(list->val);

    llist_free(list);
}

static void create_string_lists(void **state) {
    LList* head = llist_push("head", llist_push("next", llist_create_list()));

    assert_string_equal(head->val, "head");
    assert_string_equal(head->next->val, "next");

    llist_free(head);
}

static void create_int_lists(void **state) {
    LList* head = fixture_int_list();

    assert_int_equal(head->val, 1);
    assert_int_equal(head->next->val, 2);

    llist_free(head);
}

static void access_value_out_of_stack(void **state) {
    // list must be created in another function
    LList* head = fixture_int_list();

    assert_int_equal(head->val, 1);
    assert_int_equal(head->next->val, 2);

    llist_free(head);
}

static void pop_llist(void **state) {
    LList* head = fixture_int_list();
    LList* next = llist_pop(head);

    assert_int_equal(head->val, 1);
    assert_null(head->next);
    llist_free(head);

    assert_int_equal(next->val, 2);
    llist_free(next);
}

static void get_size(void **state) {
    LList* head = llist_create_list();
    assert_int_equal(llist_size(head), 0);
    head = llist_push((void*) 1, head);
    assert_int_equal(llist_size(head), 1);

    llist_free(head);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(create_empty_list),
        cmocka_unit_test(create_string_lists),
        cmocka_unit_test(create_int_lists),
        cmocka_unit_test(access_value_out_of_stack),
        cmocka_unit_test(pop_llist),
        cmocka_unit_test(get_size),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}