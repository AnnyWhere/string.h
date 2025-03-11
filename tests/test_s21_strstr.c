#include <check.h>

#include "../s21_string.h"

// Общая функция для сравнения результатов
#define test_strstr(s1, s2) ck_assert_ptr_eq(s21_strstr(s1, s2), strstr(s1, s2))

START_TEST(strstr_1) {
  char s1[] = "hello world";
  char s2[] = "world";
  test_strstr(s1, s2);
}
END_TEST

START_TEST(strstr_2) {
  char s1[] = "Hello, world!";
  char s2[] = "world!";
  test_strstr(s1, s2);
}
END_TEST

START_TEST(strstr_3) {
  char s1[] = "";
  char s2[] = "";
  test_strstr(s1, s2);
}
END_TEST

START_TEST(strstr_4) {
  char s1[] = "Hello, world!";
  char s2[] = "";
  test_strstr(s1, s2);
}
END_TEST

START_TEST(strstr_5) {
  char s1[] = "";
  char s2[] = "Hello, P!";
  test_strstr(s1, s2);
}
END_TEST

START_TEST(strstr_6) {
  char s1[] = "69917020";
  char s2[] = "0";
  test_strstr(s1, s2);
}
END_TEST

START_TEST(strstr_7) {
  char s1[] = "69917020";
  char s2[] = "\0";
  test_strstr(s1, s2);
}
END_TEST

Suite *s21_strstr_suite(void) {
  Suite *s = suite_create("S21 Strstr Test Suite");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, strstr_1);
  tcase_add_test(tc, strstr_2);
  tcase_add_test(tc, strstr_3);
  tcase_add_test(tc, strstr_4);
  tcase_add_test(tc, strstr_5);
  tcase_add_test(tc, strstr_6);
  tcase_add_test(tc, strstr_7);

  suite_add_tcase(s, tc);

  return s;
}