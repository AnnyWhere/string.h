#include <check.h>

#include "../s21_string.h"

// Тесты для функции s21_strerror

START_TEST(s21_strerror_01) {
  ck_assert_str_eq(strerror(-10), s21_strerror(-10));
}
END_TEST

START_TEST(s21_strerror_02) {
  ck_assert_str_eq(strerror(1000), s21_strerror(1000));
}
END_TEST

START_TEST(s21_strerror_0) { ck_assert_str_eq(strerror(0), s21_strerror(0)); }
END_TEST

START_TEST(s21_strerror_1) { ck_assert_str_eq(strerror(1), s21_strerror(1)); }
END_TEST

START_TEST(s21_strerror_10) {
  ck_assert_str_eq(strerror(10), s21_strerror(10));
}
END_TEST

START_TEST(s21_strerror_106) {
  ck_assert_str_eq(strerror(106), s21_strerror(106));
}
END_TEST

START_TEST(s21_strerror_107) {
  ck_assert_str_eq(strerror(107), s21_strerror(107));
}
END_TEST

START_TEST(s21_strerror_108) {
  ck_assert_str_eq(strerror(108), s21_strerror(108));
}
END_TEST

Suite *s21_strerror_suite(void) {
  Suite *suite = suite_create("s21_strerror");
  TCase *tcase_core = tcase_create("Core");

  tcase_add_test(tcase_core, s21_strerror_01);
  tcase_add_test(tcase_core, s21_strerror_02);
  tcase_add_test(tcase_core, s21_strerror_0);
  tcase_add_test(tcase_core, s21_strerror_1);
  tcase_add_test(tcase_core, s21_strerror_10);
  tcase_add_test(tcase_core, s21_strerror_106);
  tcase_add_test(tcase_core, s21_strerror_107);
  tcase_add_test(tcase_core, s21_strerror_108);

  suite_add_tcase(suite, tcase_core);
  return suite;
}
