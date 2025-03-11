#include <check.h>

#include "../s21_string.h"

// Общая функция для сравнения результатов
#define test_strpbrk(s1, s2) \
  ck_assert_ptr_eq(s21_strpbrk(s1, s2), strpbrk(s1, s2))

START_TEST(strpbrk_1) {
  char s1[] = "Hello, world!";
  char s2[] = "Hello, world!";
  test_strpbrk(s1, s2);
}
END_TEST

START_TEST(strpbrk_2) {
  char s1[] = "Hello, world!";
  char s2[] = "!";
  test_strpbrk(s1, s2);
}
END_TEST

START_TEST(strpbrk_3) {
  char s1[] = "";
  char s2[] = "He";
  test_strpbrk(s1, s2);
}
END_TEST

START_TEST(strpbrk_4) {
  char s1[] = "\0";
  char s2[] = "";
  test_strpbrk(s1, s2);
}
END_TEST

START_TEST(strpbrk_5) {
  char s1[] = "This is a test string.";
  char s2[] = "test";
  test_strpbrk(s1, s2);
}
END_TEST

Suite *s21_strpbrk_suite(void) {
  Suite *s = suite_create("S21 Strpbrk Test Suite");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, strpbrk_1);
  tcase_add_test(tc, strpbrk_2);
  tcase_add_test(tc, strpbrk_3);
  tcase_add_test(tc, strpbrk_4);
  tcase_add_test(tc, strpbrk_5);

  suite_add_tcase(s, tc);

  return s;
}