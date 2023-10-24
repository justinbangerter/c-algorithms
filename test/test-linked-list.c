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
    head = llist_push(head, (void*) 3);
    head = llist_push(head, (void*) 2);
    head = llist_push(head, (void*) 1);
    return head;
}

static LList* fixture_string_list() {
    LList* head = NULL;
    head = llist_push(head, "last");
    head = llist_push(head, "next");
    head = llist_push(head, "first");
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
    head = llist_push(head, (void*) 1);
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

static void sort_one_item(void **state) {
    LList* head = NULL;
    head = llist_push(head, (void*) 9);

    LList* sorted = llist_sort(head, NULL);
    assert_int_equal(llist_get(sorted, 0)->val, 9);
    assert_int_equal(llist_size(sorted), 1);
}

int compare_ints (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

static void sort_two_items(void **state) {
    LList* head = NULL;
    head = llist_push(head, (void*) 1);
    head = llist_push(head, (void*) 3);

    int (*cmp) (const void*, const void*);
    cmp = &compare_ints;
    LList* sorted = llist_sort(head, cmp);
    assert_int_equal(llist_get(sorted, 0)->val, 1);
    assert_int_equal(llist_get(sorted, 1)->val, 3);
    assert_int_equal(llist_size(sorted), 2);
}

static void sort(void **state) {
    LList* head;
    LList* sorted;
    int original_size;
    int comparator (const void * a, const void * b) {
        return ( *(int*)a - *(int*)b );
    }

    head = NULL;
    head = llist_push(head, (void*) 9);
    head = llist_push(head, (void*) 2);
    head = llist_push(head, (void*) 3);
    head = llist_push(head, (void*) 3);
    head = llist_push(head, (void*) 8);
    head = llist_push(head, (void*) 2);
    head = llist_push(head, (void*) 4);
    original_size = llist_size(head);

    sorted = llist_sort(head, comparator);

    assert_int_equal(llist_size(sorted), original_size);
    assert_int_equal(llist_get(sorted, 0)->val, 2);
    assert_int_equal(llist_get(sorted, 1)->val, 2);
    assert_int_equal(llist_get(sorted, 2)->val, 3);
    assert_int_equal(llist_get(sorted, 3)->val, 3);
    assert_int_equal(llist_get(sorted, 4)->val, 4);
    assert_int_equal(llist_get(sorted, 5)->val, 8);
    assert_int_equal(llist_get(sorted, 6)->val, 9);

    llist_free(sorted);

    /* try again with a different list */

    head = NULL;
    head = llist_push(head, (void*) 1);
    head = llist_push(head, (void*) 2);
    head = llist_push(head, (void*) 3);
    original_size = llist_size(head);

    sorted = llist_sort(head, comparator);

    assert_int_equal(llist_size(sorted), original_size);
    assert_int_equal(llist_get(sorted, 0)->val, 1);
    assert_int_equal(llist_get(sorted, 1)->val, 2);
    assert_int_equal(llist_get(sorted, 2)->val, 3);

    llist_free(sorted);
}


static void split_after(void **state) {
    LList* head = NULL;
    head = llist_push(head, (void*) 3);
    head = llist_push(head, (void*) 2);
    head = llist_push(head, (void*) 1);

    assert_int_equal(llist_size(head), 3);

    LList* tail = llist_split_after(head, 1);

    assert_int_equal(llist_size(head), 2);
    assert_int_equal(llist_get(head, 0)->val, 1);
    assert_int_equal(llist_get(head, 1)->val, 2);

    assert_int_equal(llist_size(tail), 1);
    assert_int_equal(llist_get(tail, 0)->val, 3);
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
        cmocka_unit_test(sort_one_item),
        cmocka_unit_test(sort_two_items),
        //cmocka_unit_test(sort),
        cmocka_unit_test(split_after),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}