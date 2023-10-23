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
    LList* head = NULL;
    head = llist_push((void*) 3, head);
    head = llist_push((void*) 2, head);
    head = llist_push((void*) 1, head);
    return head;
}

static LList* fixture_string_list() {
    LList* head = NULL;
    head = llist_push("last", head);
    head = llist_push("next", head);
    head = llist_push("first", head);
    return head;
}

/// Tests ///

static void create_empty_node(void **state) {
    LList* head = llist_node(NULL);

    assert_null(head->val);
    assert_int_equal(llist_size(head), 1);

    llist_free(head);
}

static void create_node(void **state) {
    LList* head = llist_node((void*) 1);

    assert_int_equal(head->val, 1);
    assert_int_equal(llist_size(head), 1);

    llist_free(head);
}

static void create_string_lists(void **state) {
    LList* head = fixture_string_list();

    assert_string_equal(head->val, "first");
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
    assert_int_equal(llist_size(head), 3);
    LList* next;

    next = head->next;
    assert_int_equal(llist_pop(head), 1);
    head = next;
    assert_int_equal(llist_size(head), 2);

    next = head->next;
    assert_int_equal(llist_pop(head), 2);
    head = next;
    assert_int_equal(llist_size(head), 1);

    next = head->next;
    assert_int_equal(llist_pop(head), 3);
    head = next;
    assert_int_equal(llist_size(head), 0);

    llist_free(head);
}

static void get_size(void **state) {
    LList* head = llist_node(NULL);
    assert_int_equal(llist_size(head), 1);
    head = llist_push((void*) 1, head);
    assert_int_equal(llist_size(head), 2);

    llist_free(head);
}

static void get_by_index(void **state) {
    LList* head = fixture_int_list();
    assert_int_equal(llist_get(head, 0)->val, 1);
    assert_int_equal(llist_get(head, 1)->val, 2);
    assert_int_equal(llist_get(head, 2)->val, 3);
    assert_int_equal(llist_size(head), 3);
    llist_free(head);

    head = fixture_string_list();
    assert_string_equal(llist_get(head, 0)->val, "first");
    assert_string_equal(llist_get(head, 1)->val, "next");
    assert_string_equal(llist_get(head, 2)->val, "last");
    assert_int_equal(llist_size(head), 3);
    llist_free(head);
}

static void insert(void **state) {
    LList* head = fixture_int_list();
    assert_int_equal(llist_size(head), 3);
    assert_int_equal(llist_get(head, 0)->val, 1);
    assert_int_equal(llist_get(head, 1)->val, 2);
    assert_int_equal(llist_get(head, 2)->val, 3);

    LList* inserted = llist_insert_after(llist_get(head, 1), (void *) 100);
    assert_int_equal(llist_size(head), 4);
    assert_int_equal(llist_get(head, 0)->val, 1);
    assert_int_equal(llist_get(head, 1)->val, 2);
    assert_int_equal(llist_get(head, 2)->val, 100);
    assert_int_equal(llist_get(head, 3)->val, 3);

    llist_free(head);
}

static void insert_at_end(void **state) {
    LList* head = fixture_int_list();
    assert_int_equal(llist_size(head), 3);
    assert_int_equal(llist_get(head, 0)->val, 1);
    assert_int_equal(llist_get(head, 1)->val, 2);
    assert_int_equal(llist_get(head, 2)->val, 3);

    LList* inserted = llist_insert_after(
        llist_get(head, llist_size(head) - 1),
        (void *) 100
    );
    assert_int_equal(llist_size(head), 4);
    assert_int_equal(llist_get(head, 0)->val, 1);
    assert_int_equal(llist_get(head, 1)->val, 2);
    assert_int_equal(llist_get(head, 2)->val, 3);
    assert_int_equal(llist_get(head, 3)->val, 100);

    llist_free(head);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(create_empty_node),
        cmocka_unit_test(create_node),
        cmocka_unit_test(create_string_lists),
        cmocka_unit_test(create_int_lists),
        cmocka_unit_test(access_value_out_of_stack),
        cmocka_unit_test(pop_llist),
        cmocka_unit_test(get_size),
        cmocka_unit_test(get_by_index),
        cmocka_unit_test(insert),
        cmocka_unit_test(insert_at_end),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}