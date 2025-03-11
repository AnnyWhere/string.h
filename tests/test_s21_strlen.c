#include <check.h>

#include "../s21_string.h"

// Общая функция для сравнения результатов
#define test_strlen(str) ck_assert_int_eq(s21_strlen(str), strlen(str))

START_TEST(strlen_1) {
  char str[] = "Hello, world!";
  test_strlen(str);
}
END_TEST

START_TEST(strlen_2) {
  char str[] = "21313-04=3stuvwxyz21524--5=432 ";
  test_strlen(str);
}
END_TEST

START_TEST(strlen_3) {
  char str[] = "Hello, world!";
  test_strlen(str);
}
END_TEST

START_TEST(strlen_4) {
  char str[] = "\0";
  test_strlen(str);
}
END_TEST

START_TEST(strlen_5) {
  char str[] = "today a good day. may be";
  test_strlen(str);
}
END_TEST

START_TEST(strlen_6) {
  char str[] = "";
  test_strlen(str);
}
END_TEST

START_TEST(strlen_7) {
  char str[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
  test_strlen(str);
}
END_TEST

Suite *s21_strlen_suite(void) {
  Suite *s = suite_create("S21 Strlen Test Suite");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, strlen_1);
  tcase_add_test(tc, strlen_2);
  tcase_add_test(tc, strlen_3);
  tcase_add_test(tc, strlen_4);
  tcase_add_test(tc, strlen_5);
  tcase_add_test(tc, strlen_6);
  tcase_add_test(tc, strlen_7);

  suite_add_tcase(s, tc);

  return s;
}
