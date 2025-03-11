
#include <check.h>

#include "../s21_string.h"

#define test_strtok(s1, s3)                       \
  do {                                            \
    char s1_copy[256];                            \
    strcpy(s1_copy, s1);                          \
    char *result_s1 = s21_strtok(s1_copy, s3);    \
    char s2_copy[256];                            \
    strcpy(s2_copy, s1);                          \
    char *result_s2 = strtok(s2_copy, s3);        \
    if (result_s1 == NULL && result_s2 == NULL) { \
      ck_assert_ptr_eq(result_s1, result_s2);     \
    } else {                                      \
      ck_assert_str_eq(result_s1, result_s2);     \
    }                                             \
  } while (0)

START_TEST(strtok_1) {
  char s1[] = "Hello,-! world!";
  char s3[] = "!-";

  test_strtok(s1, s3);
  test_strtok(s1, s3);
  test_strtok(s1, s3);

  test_strtok(s1, s3);
}
END_TEST

START_TEST(strtok_2) {
  char s1[] = "";
  char s3[] = "";

  test_strtok(s1, s3);
}
END_TEST

START_TEST(strtok_3) {
  char s1[] = "Hello, world!";
  char s3[] = ",";

  test_strtok(s1, s3);
}
END_TEST

START_TEST(strtok_4) {
  char s1[] = "Hello, world!";
  char s3[] = " ";

  test_strtok(s1, s3);
}
END_TEST

START_TEST(strtok_5) {
  char s1[] = "Hello, world!";
  char s3[] = "o";

  test_strtok(s1, s3);
}
END_TEST

START_TEST(strtok_6) {
  char s1[] = "Hello, world!";
  char s3[] = "z";

  test_strtok(s1, s3);
}
END_TEST

START_TEST(strtok_7) {
  char s1[] = "hehehehehehehB";
  char s3[] = "B";

  test_strtok(s1, s3);
}
END_TEST

START_TEST(strtok_8) {
  char s1[] = "\nAhehehehehehehB";
  char s3[] = "A";

  test_strtok(s1, s3);
}
END_TEST

Suite *s21_strtok_suite(void) {
  Suite *s = suite_create("S21 Strtok Test Suite");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, strtok_1);
  tcase_add_test(tc, strtok_2);
  tcase_add_test(tc, strtok_3);
  tcase_add_test(tc, strtok_4);
  tcase_add_test(tc, strtok_5);
  tcase_add_test(tc, strtok_6);
  tcase_add_test(tc, strtok_7);
  tcase_add_test(tc, strtok_8);

  suite_add_tcase(s, tc);

  return s;
}
