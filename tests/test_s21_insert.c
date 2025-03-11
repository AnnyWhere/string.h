#include <check.h>

#include "../s21_string.h"

START_TEST(s21_insert_1) {
  const char *src = "Hello World!";
  const char *str = " Beautiful";

  char *result = s21_insert(src, str, 5);

  ck_assert_str_eq(result, "Hello Beautiful World!");

  free(result);
}
END_TEST

START_TEST(s21_insert_2) {
  const char *src = "Hello World!";
  const char *str = "Hi ";

  char *result = s21_insert(src, str, 0);

  ck_assert_str_eq(result, "Hi Hello World!");

  free(result);
}
END_TEST

START_TEST(s21_insert_3) {
  const char *src = "Hello World!";
  const char *str = "";

  char *result = s21_insert(src, str, 5);
  ck_assert_str_eq(result, "Hello World!");

  free(result);
}
END_TEST

START_TEST(s21_insert_4) {
  const char *src = "Hello World!";
  const char *str = "Test";

  char *result = s21_insert(src, str, 12);
  ck_assert_str_eq(result, "Hello World!Test");

  free(result);
}
END_TEST

START_TEST(s21_insert_5) {
  const char *src = NULL;
  const char *str = "Test";

  char *result = s21_insert(src, str, 0);
  ck_assert_ptr_eq(result, NULL);

  free(result);
}
END_TEST

START_TEST(s21_insert_6) {
  const char *src = "Hello World!";
  const char *str = "Test";

  char *result = s21_insert(src, str, 20);
  ck_assert_ptr_eq(result, NULL);

  free(result);
}
END_TEST

Suite *s21_insert_suite(void) {
  Suite *s = suite_create("S21 Insert Test Suite");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, s21_insert_1);
  tcase_add_test(tc, s21_insert_2);
  tcase_add_test(tc, s21_insert_3);
  tcase_add_test(tc, s21_insert_4);
  tcase_add_test(tc, s21_insert_5);
  tcase_add_test(tc, s21_insert_6);

  suite_add_tcase(s, tc);

  return s;
}
