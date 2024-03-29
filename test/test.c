#include <check.h>
#include <examplelib.h>
#include <stdio.h>

START_TEST(examplelib_test) {
    ck_assert_int_eq(2 + 2, 4);
}
END_TEST

Suite *examplelib_suite(void) {
    Suite *suite;
    suite = suite_create("examplelib");

    TCase *tc_core = tcase_create("core");
    tcase_add_test(tc_core, examplelib_test);
    suite_add_tcase(suite, tc_core);

    return suite;
}

int main(void) {
    Suite *suite = examplelib_suite();
    SRunner *suite_runner = srunner_create(suite);

    srunner_run_all(suite_runner, TEST_PRINT_MODE);
    int number_failed = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);

    return (number_failed == 0) ? 0 : 1;
}