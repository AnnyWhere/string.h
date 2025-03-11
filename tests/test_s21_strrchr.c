#include <check.h>

#include "../s21_string.h"

// Общая функция для сравнения результатов
#define test_strrchr(s, ch) ck_assert_ptr_eq(s21_strrchr(s, ch), strrchr(s, ch))

START_TEST(strrchr_beginning) {
  char s[] = "Hello, world!";
  int ch = 'H';
  test_strrchr(s, ch);
}
END_TEST

START_TEST(strrchr_middle) {
  char s[] = "Hello, world!";
  int ch = 'l';
  test_strrchr(s, ch);
}
END_TEST

START_TEST(strrchr_end) {
  char s[] = "Hello, world!";
  int ch = 'd';
  test_strrchr(s, ch);
}
END_TEST

START_TEST(strrchr_empty) {
  char s[] = "";
  int ch = 'x';
  test_strrchr(s, ch);
}
END_TEST

START_TEST(strrchr_single_char) {
  char s[] = "H";
  int ch = 'H';
  test_strrchr(s, ch);
}
END_TEST

START_TEST(strrchr_special_chars) {
  char s[] = "Hello,\nWorld!";
  int ch = '\n';
  test_strrchr(s, ch);
}
END_TEST

Suite *s21_strrchr_suite(void) {
  Suite *s = suite_create("S21 Strrchr Test Suite");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, strrchr_beginning);
  tcase_add_test(tc, strrchr_middle);
  tcase_add_test(tc, strrchr_end);
  tcase_add_test(tc, strrchr_empty);
  tcase_add_test(tc, strrchr_single_char);
  tcase_add_test(tc, strrchr_special_chars);

  suite_add_tcase(s, tc);

  return s;
}
