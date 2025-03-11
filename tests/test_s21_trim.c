#include <check.h>

#include "../s21_string.h"

START_TEST(s21_trim_1) {
  const char *src = "   Hello World!   ";
  const char *trim_chars = " ";

  char *result = s21_trim(src, trim_chars);

  ck_assert_str_eq(result, "Hello World!");

  free(result);
}
END_TEST

START_TEST(s21_trim_2) {
  const char *src = "***Hello***";
  const char *trim_chars = "*";

  char *result = s21_trim(src, trim_chars);

  ck_assert_str_eq(result, "Hello");

  free(result);
}
END_TEST

START_TEST(s21_trim_3) {
  const char *src = "";
  const char *trim_chars = "*";

  char *result = s21_trim(src, trim_chars);

  ck_assert_str_eq(result, "");

  free(result);
}
END_TEST

START_TEST(s21_trim_4) {
  const char *src = "NoTrim";
  const char *trim_chars = "*";

  char *result = s21_trim(src, trim_chars);

  ck_assert_str_eq(result, "NoTrim");

  free(result);
}
END_TEST

START_TEST(s21_trim_5) {
  const char *src = "***Hello***";
  const char *trim_chars = "*";

  char *result = s21_trim(src, trim_chars);

  ck_assert_str_eq(result, "Hello");

  free(result);
}
END_TEST

START_TEST(s21_trim_6) {
  const char *src = "Hello World!";
  const char *trim_chars = "*";

  char *result = s21_trim(src, trim_chars);

  ck_assert_str_eq(result, "Hello World!");

  free(result);
}
END_TEST

Suite *s21_trim_suite(void) {
  Suite *s = suite_create("S21 Trim Test Suite");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, s21_trim_1);
  tcase_add_test(tc, s21_trim_2);
  tcase_add_test(tc, s21_trim_3);
  tcase_add_test(tc, s21_trim_4);
  tcase_add_test(tc, s21_trim_5);
  tcase_add_test(tc, s21_trim_6);

  suite_add_tcase(s, tc);

  return s;
}
