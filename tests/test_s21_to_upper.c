#include <check.h>

#include "../s21_string.h"

START_TEST(s21_upper_1) {
  const char *input = "Hello World!";
  char *result = s21_to_upper(input);
  ck_assert_str_eq(result, "HELLO WORLD!");
  free(result);
}
END_TEST

START_TEST(s21_upper_2) {
  const char *input = "all lower";
  char *result = s21_to_upper(input);
  ck_assert_str_eq(result, "ALL LOWER");
  free(result);
}
END_TEST

START_TEST(s21_upper_3) {
  const char *input = "Already Upper";
  char *result = s21_to_upper(input);
  ck_assert_str_eq(result, "ALREADY UPPER");
  free(result);
}
END_TEST

START_TEST(s21_upper_4) {
  const char *input = "";
  char *result = s21_to_upper(input);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

Suite *s21_to_upper_suite(void) {
  Suite *s = suite_create("S21 To Upper Test Suite");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, s21_upper_1);
  tcase_add_test(tc, s21_upper_2);
  tcase_add_test(tc, s21_upper_3);
  tcase_add_test(tc, s21_upper_4);

  suite_add_tcase(s, tc);

  return s;
}
