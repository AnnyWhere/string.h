#include <check.h>

#include "../s21_string.h"

START_TEST(s21_lower_1) {
  const char *input = "Hello World!";
  char *result = s21_to_lower(input);
  ck_assert_str_eq(result, "hello world!");
  free(result);
}
END_TEST

START_TEST(s21_lower_2) {
  const char *input = "ALL CAPS";
  char *result = s21_to_lower(input);
  ck_assert_str_eq(result, "all caps");
  free(result);
}
END_TEST

START_TEST(s21_lower_3) {
  const char *input = "already lower";
  char *result = s21_to_lower(input);
  ck_assert_str_eq(result, "already lower");
  free(result);
}
END_TEST

START_TEST(s21_lower_4) {
  const char *input = "";
  char *result = s21_to_lower(input);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

Suite *s21_to_lower_suite(void) {
  Suite *s = suite_create("S21 To Lower Test Suite");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, s21_lower_1);
  tcase_add_test(tc, s21_lower_2);
  tcase_add_test(tc, s21_lower_3);
  tcase_add_test(tc, s21_lower_4);

  suite_add_tcase(s, tc);

  return s;
}
