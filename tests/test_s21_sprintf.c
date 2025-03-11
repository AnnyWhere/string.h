#include <check.h>
#include <stdio.h>
#include <string.h>

#include "../s21_string.h"

// тесты для спецификатора c
START_TEST(test_char_specifier) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "|%c|", 'A');
  sprintf(buffer2, "|%c|", 'A');
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "|%5c|", 'B');
  sprintf(buffer2, "|%5c|", 'B');
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST  // Базовые

START_TEST(test_char_specifier_basic) {
  char buffer1[100], buffer2[100];

  // Проверка управляющего символа
  s21_sprintf(buffer1, "|%c|", '\n');
  sprintf(buffer2, "|%c|", '\n');
  ck_assert_str_eq(buffer1, buffer2);

  // Проверка символа с кодом за пределами ASCII
  s21_sprintf(buffer1, "|%c|", 255);
  sprintf(buffer2, "|%c|", 255);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_char_specifier_width) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "|%5c|", 'B');
  sprintf(buffer2, "|%5c|", 'B');
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "|%-5c|", 'B');
  sprintf(buffer2, "|%-5c|", 'B');
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_char_specifier_null_char) {
  char buffer1[100], buffer2[100];

  // Проверка символа \0
  s21_sprintf(buffer1, "|%c|", '\0');
  sprintf(buffer2, "|%c|", '\0');
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST
// тесты для wc
START_TEST(test_wchar_basic) {
  char buffer1[100], buffer2[100];

  wchar_t wc = L'k';
  s21_sprintf(buffer1, "|%lc|", wc);
  sprintf(buffer2, "|%lc|", wc);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_wchar_width) {
  char buffer1[100], buffer2[100];

  wchar_t wc = L'Ж';
  s21_sprintf(buffer1, "|%5lc|", wc);
  sprintf(buffer2, "|%5lc|", wc);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "|%-5lc|", wc);
  sprintf(buffer2, "|%-5lc|", wc);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_wchar_too_big) {
  char buffer1[2048], buffer2[2048];

  wchar_t wc = 0x120000;  // символ за пределами допустимого диапазона Unicode
  wchar_t expected_wc =
      L'\uFFFD';  // символ замены для недопустимого, т.к. иначе неопределенное
                  // поведение оригинальной

  if (wc > 0x10FFFF) {
    wc = expected_wc;
  }

  s21_sprintf(buffer1, "|%lc|", wc);
  sprintf(buffer2, "|%lc|", wc);

  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_wchar_null) {
  char buffer1[100], buffer2[100];

  wchar_t wc = L'\0';
  s21_sprintf(buffer1, "|%lc|", wc);
  sprintf(buffer2, "|%lc|", wc);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// тесты для спецификатора s
START_TEST(test_str_specifier) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "|%s|", "Hello");
  sprintf(buffer2, "|%s|", "Hello");
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "|%10s|", "Hi");
  sprintf(buffer2, "|%10s|", "Hi");
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "|%.3s|", "Hello");
  sprintf(buffer2, "|%.3s|", "Hello");
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_s_null_pointer) {
  char str1[1024] = "";
  char str2[1024] = "";

  // Обрабатка NULL
  char *null_str = (char *)NULL;

  s21_sprintf(str1, "|%s|", null_str ? null_str : "(null)");
  sprintf(str2, "|%s|", null_str ? null_str : "(null)");

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s_empty_string) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "|%s|", "");
  sprintf(buffer2, "|%s|", "");
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_s_padding_with_minus_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "|%-10s|", "Test");
  sprintf(buffer2, "|%-10s|", "Test");
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_s_multiple_strings) {
  char buffer1[200], buffer2[200];

  s21_sprintf(buffer1, "|%s %s %s|", "Hello", "world", "again");
  sprintf(buffer2, "|%s %s %s|", "Hello", "world", "again");
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_s_precision_and_width) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "|%10.5s|", "Precision");
  sprintf(buffer2, "|%10.5s|", "Precision");
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_s_unicode_characters) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "|%s|", "Привет");
  sprintf(buffer2, "|%s|", "Привет");
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_s_special_characters) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "|%s|", "\n\t\0\\");
  sprintf(buffer2, "|%s|", "\n\t\0\\");
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// тесты для спецификатора d
START_TEST(test_int_specifier) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "|%d|", 42);
  sprintf(buffer2, "|%d|", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "|%5d|", 42);
  sprintf(buffer2, "|%5d|", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "|%+d|", 42);
  sprintf(buffer2, "|%+d|", 42);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_positive_number) {
  char buffer1[100];
  char buffer2[100];
  int value = 12345;
  s21_sprintf(buffer1, "%d", value);
  sprintf(buffer2, "%d", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_zero) {
  char buffer1[100];
  char buffer2[100];
  int value = 0;
  s21_sprintf(buffer1, "%d", value);
  sprintf(buffer2, "%d", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_int_max) {
  char buffer1[100];
  char buffer2[100];
  int value = 2147483647;
  s21_sprintf(buffer1, "%d", value);
  sprintf(buffer2, "%d", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_multiple_numbers) {
  char buffer1[100];
  char buffer2[100];
  int a = 123, b = -456, c = 789;
  s21_sprintf(buffer1, "%d %d %d", a, b, c);
  sprintf(buffer2, "%d %d %d", a, b, c);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_with_text) {
  char buffer1[100];
  char buffer2[100];
  int value = 42;
  s21_sprintf(buffer1, "The answer is %d.", value);
  sprintf(buffer2, "The answer is %d.", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_leading_zero) {
  char buffer1[100];
  char buffer2[100];
  int value = 42;
  s21_sprintf(buffer1, "%05d", value);
  sprintf(buffer2, "%05d", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_negative_with_leading_zero) {
  char buffer1[100];
  char buffer2[100];
  int value = -42;
  s21_sprintf(buffer1, "%05d", value);
  sprintf(buffer2, "%05d", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_large_field_width) {
  char buffer1[100];
  char buffer2[100];
  int value = 123;
  s21_sprintf(buffer1, "%20d", value);
  sprintf(buffer2, "%20d", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_small_field_width) {
  char buffer1[100];
  char buffer2[100];
  int value = 123;
  s21_sprintf(buffer1, "%2d", value);
  sprintf(buffer2, "%2d", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_invalid_format) {
  char buffer1[100];
  char buffer2[100];
  s21_sprintf(buffer1, "%d%d", 42, 43);
  sprintf(buffer2, "%d%d", 42, 43);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_width_d_star_positive) {
  char buffer1[100], buffer2[100];
  int width = 5;

  s21_sprintf(buffer1, "%*d", width, 123);
  sprintf(buffer2, "%*d", width, 123);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_width_d_star_negative) {
  char buffer1[100], buffer2[100];
  int width = -5;

  s21_sprintf(buffer1, "%*d", width, 123);
  sprintf(buffer2, "%*d", width, 123);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_width_d_star_zero) {
  char buffer1[100], buffer2[100];
  int width = 0;

  s21_sprintf(buffer1, "%*d", width, 123);
  sprintf(buffer2, "%*d", width, 123);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// тесты для hd
START_TEST(test_short_positive) {
  char buffer1[100], buffer2[100];
  short value = 32767;
  s21_sprintf(buffer1, "%hd", value);
  sprintf(buffer2, "%hd", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_short_zero) {
  char buffer1[100], buffer2[100];
  short value = 0;
  s21_sprintf(buffer1, "%hd", value);
  sprintf(buffer2, "%hd", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_short_with_leading_zeros) {
  char buffer1[100], buffer2[100];
  short value = 42;
  s21_sprintf(buffer1, "%05hd", value);
  sprintf(buffer2, "%05hd", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_short_negative_with_leading_zeros) {
  char buffer1[100], buffer2[100];
  short value = -42;
  s21_sprintf(buffer1, "%05hd", value);
  sprintf(buffer2, "%05hd", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_short_with_plus_flag) {
  char buffer1[100], buffer2[100];
  short value = 123;
  s21_sprintf(buffer1, "%+hd", value);
  sprintf(buffer2, "%+hd", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_short_with_space_flag) {
  char buffer1[100], buffer2[100];
  short value = 123;
  s21_sprintf(buffer1, "% hd", value);
  sprintf(buffer2, "% hd", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_short_with_large_field_width) {
  char buffer1[100], buffer2[100];
  short value = 321;
  s21_sprintf(buffer1, "%10hd", value);
  sprintf(buffer2, "%10hd", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_short_with_small_field_width) {
  char buffer1[100], buffer2[100];
  short value = 321;
  s21_sprintf(buffer1, "%2hd", value);
  sprintf(buffer2, "%2hd", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_short_with_precision) {
  char buffer1[100], buffer2[100];
  short value = 123;
  s21_sprintf(buffer1, "%.5hd", value);
  sprintf(buffer2, "%.5hd", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_short_with_precision_and_width) {
  char buffer1[100], buffer2[100];
  short value = 123;
  s21_sprintf(buffer1, "%10.5hd", value);
  sprintf(buffer2, "%10.5hd", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_short_with_minus_flag) {
  char buffer1[100], buffer2[100];
  short value = 123;
  s21_sprintf(buffer1, "%-10hd", value);
  sprintf(buffer2, "%-10hd", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_short_multiple_values) {
  char buffer1[100], buffer2[100];
  short a = 123, b = -456, c = 789;
  s21_sprintf(buffer1, "%hd %hd %hd", a, b, c);
  sprintf(buffer2, "%hd %hd %hd", a, b, c);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_short_edge_case_positive) {
  char buffer1[100], buffer2[100];
  short value = 1;
  s21_sprintf(buffer1, "%hd", value);
  sprintf(buffer2, "%hd", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// тесты для ld

START_TEST(test_long_positive) {
  char buffer1[100], buffer2[100];
  long value = 9223372036854775807L;
  s21_sprintf(buffer1, "%ld", value);
  sprintf(buffer2, "%ld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_long_zero) {
  char buffer1[100], buffer2[100];
  long value = 0;
  s21_sprintf(buffer1, "%ld", value);
  sprintf(buffer2, "%ld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_long_with_plus_flag) {
  char buffer1[100], buffer2[100];
  long value = 123456789L;
  s21_sprintf(buffer1, "%+ld", value);
  sprintf(buffer2, "%+ld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_long_with_space_flag) {
  char buffer1[100], buffer2[100];
  long value = 123456789L;
  s21_sprintf(buffer1, "% ld", value);
  sprintf(buffer2, "% ld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_long_with_leading_zeros) {
  char buffer1[100], buffer2[100];
  long value = 42L;
  s21_sprintf(buffer1, "%010ld", value);
  sprintf(buffer2, "%010ld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_long_negative_with_leading_zeros) {
  char buffer1[100], buffer2[100];
  long value = -42L;
  s21_sprintf(buffer1, "%010ld", value);
  sprintf(buffer2, "%010ld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_long_with_precision) {
  char buffer1[100], buffer2[100];
  long value = 123L;
  s21_sprintf(buffer1, "%.10ld", value);
  sprintf(buffer2, "%.10ld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_long_with_width_and_precision) {
  char buffer1[100], buffer2[100];
  long value = 123L;
  s21_sprintf(buffer1, "%15.10ld", value);
  sprintf(buffer2, "%15.10ld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_long_negative_with_width_and_precision) {
  char buffer1[100], buffer2[100];
  long value = -123L;
  s21_sprintf(buffer1, "%15.10ld", value);
  sprintf(buffer2, "%15.10ld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_long_with_minus_flag) {
  char buffer1[100], buffer2[100];
  long value = 123456789L;
  s21_sprintf(buffer1, "%-15ld", value);
  sprintf(buffer2, "%-15ld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_long_multiple_values) {
  char buffer1[200], buffer2[200];
  long a = 123L, b = -456L, c = 789L;
  s21_sprintf(buffer1, "%ld %ld %ld", a, b, c);
  sprintf(buffer2, "%ld %ld %ld", a, b, c);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_long_small_values) {
  char buffer1[100], buffer2[100];
  long value = 1L;
  s21_sprintf(buffer1, "%ld", value);
  sprintf(buffer2, "%ld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_long_large_width) {
  char buffer1[100], buffer2[100];
  long value = 321L;
  s21_sprintf(buffer1, "%20ld", value);
  sprintf(buffer2, "%20ld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_long_small_width) {
  char buffer1[100], buffer2[100];
  long value = 321L;
  s21_sprintf(buffer1, "%2ld", value);
  sprintf(buffer2, "%2ld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_long_zero_width_and_precision) {
  char buffer1[100], buffer2[100];
  long value = 0L;
  s21_sprintf(buffer1, "%10.5ld", value);
  sprintf(buffer2, "%10.5ld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_long_with_star_width) {
  char buffer1[100], buffer2[100];
  int width = 10;
  long value = 123456L;
  s21_sprintf(buffer1, "%*ld", width, value);
  sprintf(buffer2, "%*ld", width, value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_long_with_star_precision) {
  char buffer1[100], buffer2[100];
  int precision = 8;
  long value = 123456L;
  s21_sprintf(buffer1, "%.*ld", precision, value);
  sprintf(buffer2, "%.*ld", precision, value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// тесты для long long
START_TEST(test_lld_positive) {
  char buffer1[100], buffer2[100];
  long long value = 9223372036854775807LL;
  s21_sprintf(buffer1, "%lld", value);
  sprintf(buffer2, "%lld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lld_zero) {
  char buffer1[100], buffer2[100];
  long long value = 0;
  s21_sprintf(buffer1, "%lld", value);
  sprintf(buffer2, "%lld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lld_with_plus_flag) {
  char buffer1[100], buffer2[100];
  long long value = 123456789012345LL;
  s21_sprintf(buffer1, "%+lld", value);
  sprintf(buffer2, "%+lld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lld_with_space_flag) {
  char buffer1[100], buffer2[100];
  long long value = 123456789012345LL;
  s21_sprintf(buffer1, "% lld", value);
  sprintf(buffer2, "% lld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lld_with_leading_zeros) {
  char buffer1[100], buffer2[100];
  long long value = 42LL;
  s21_sprintf(buffer1, "%010lld", value);
  sprintf(buffer2, "%010lld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lld_negative_with_leading_zeros) {
  char buffer1[100], buffer2[100];
  long long value = -42LL;
  s21_sprintf(buffer1, "%010lld", value);
  sprintf(buffer2, "%010lld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lld_with_precision) {
  char buffer1[100], buffer2[100];
  long long value = 123LL;
  s21_sprintf(buffer1, "%.10lld", value);
  sprintf(buffer2, "%.10lld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lld_with_width_and_precision) {
  char buffer1[100], buffer2[100];
  long long value = 123LL;
  s21_sprintf(buffer1, "%20.10lld", value);
  sprintf(buffer2, "%20.10lld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lld_negative_with_width_and_precision) {
  char buffer1[100], buffer2[100];
  long long value = -123LL;
  s21_sprintf(buffer1, "%20.10lld", value);
  sprintf(buffer2, "%20.10lld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lld_with_minus_flag) {
  char buffer1[100], buffer2[100];
  long long value = 123456789012345LL;
  s21_sprintf(buffer1, "%-20lld", value);
  sprintf(buffer2, "%-20lld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lld_multiple_values) {
  char buffer1[200], buffer2[200];
  long long a = 123LL, b = -456LL, c = 789LL;
  s21_sprintf(buffer1, "%lld %lld %lld", a, b, c);
  sprintf(buffer2, "%lld %lld %lld", a, b, c);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lld_small_values) {
  char buffer1[100], buffer2[100];
  long long value = 1LL;
  s21_sprintf(buffer1, "%lld", value);
  sprintf(buffer2, "%lld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lld_large_width) {
  char buffer1[100], buffer2[100];
  long long value = 321LL;
  s21_sprintf(buffer1, "%30lld", value);
  sprintf(buffer2, "%30lld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lld_small_width) {
  char buffer1[100], buffer2[100];
  long long value = 321LL;
  s21_sprintf(buffer1, "%2lld", value);
  sprintf(buffer2, "%2lld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lld_zero_width_and_precision) {
  char buffer1[100], buffer2[100];
  long long value = 0LL;
  s21_sprintf(buffer1, "%10.5lld", value);
  sprintf(buffer2, "%10.5lld", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lld_with_star_width) {
  char buffer1[100], buffer2[100];
  int width = 10;
  long long value = 123456LL;
  s21_sprintf(buffer1, "%*lld", width, value);
  sprintf(buffer2, "%*lld", width, value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lld_with_star_precision) {
  char buffer1[100], buffer2[100];
  int precision = 8;
  long long value = 123456LL;
  s21_sprintf(buffer1, "%.*lld", precision, value);
  sprintf(buffer2, "%.*lld", precision, value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// тесты для f
START_TEST(test_f_basic_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%f", 0.0);
  sprintf(buffer2, "%f", 0.0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%f", 123.456);
  sprintf(buffer2, "%f", 123.456);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%f", -123.456);
  sprintf(buffer2, "%f", -123.456);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_f_edge_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%f", FLT_MIN);
  sprintf(buffer2, "%f", FLT_MIN);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%f", FLT_MAX);
  sprintf(buffer2, "%f", FLT_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%f", -FLT_MAX);
  sprintf(buffer2, "%f", -FLT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_f_with_flags) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%+f", 123.456);
  sprintf(buffer2, "%+f", 123.456);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "% f", 123.456);
  sprintf(buffer2, "% f", 123.456);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#f", 123.0);
  sprintf(buffer2, "%#f", 123.0);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_f_with_width_and_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%10.2f", 123.456);
  sprintf(buffer2, "%10.2f", 123.456);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10.2f", 123.456);
  sprintf(buffer2, "%-10.2f", 123.456);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.0f", 123.456);
  sprintf(buffer2, "%.0f", 123.456);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_f_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.0f", 123.456);
  sprintf(buffer2, "%.0f", 123.456);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.2f", 123.456);
  sprintf(buffer2, "%.2f", 123.456);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.10f", 123.456);
  sprintf(buffer2, "%.10f", 123.456);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_f_star_width_and_precision) {
  char buffer1[100], buffer2[100];
  int width = 10, precision = 3;

  s21_sprintf(buffer1, "%*.*f", width, precision, 123.456789);
  sprintf(buffer2, "%*.*f", width, precision, 123.456789);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_f_precision_zero) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.0f", 123.456);
  sprintf(buffer2, "%.0f", 123.456);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_f_rounding_edge_1) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.2f", 1.999);
  sprintf(buffer2, "%.2f", 1.999);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.0f", 0.5);
  sprintf(buffer2, "%.0f", 0.5);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_f_zero_and_negative_zero) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%f", 0.0);
  sprintf(buffer2, "%f", 0.0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%f", -0.0);
  sprintf(buffer2, "%f", -0.0);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_f_large_values_with_width) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%20.2f", 123456789.0);
  sprintf(buffer2, "%20.2f", 123456789.0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-20.2f", 123456789.0);
  sprintf(buffer2, "%-20.2f", 123456789.0);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_precision_f_star_positive) {
  char buffer1[100], buffer2[100];
  int precision = 2;

  s21_sprintf(buffer1, "%.*f", precision, 123.456);
  sprintf(buffer2, "%.*f", precision, 123.456);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_precision_f_star_negative) {
  char buffer1[100], buffer2[100];
  int precision = -1;

  s21_sprintf(buffer1, "%.*f", precision, 123.456);
  sprintf(buffer2, "%.*f", precision, 123.456);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_precision_f_star_zero) {
  char buffer1[100], buffer2[100];
  int precision = 0;

  s21_sprintf(buffer1, "%.*f", precision, 123.456);
  sprintf(buffer2, "%.*f", precision, 123.456);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_f_rounding_edge_2) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.0f", 0.6);
  sprintf(buffer2, "%.0f", 0.6);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.0f", -1.5);
  sprintf(buffer2, "%.0f", -1.5);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.0f", 0.4);
  sprintf(buffer2, "%.0f", 0.4);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.0f", -0.4);
  sprintf(buffer2, "%.0f", -0.4);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// тесты для lf
START_TEST(test_lf_positive_numbers) {
  char buffer1[128], buffer2[128];
  s21_sprintf(buffer1, "%lf", 12345.6789);
  sprintf(buffer2, "%lf", 12345.6789);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lf_negative_numbers) {
  char buffer1[128], buffer2[128];
  s21_sprintf(buffer1, "%lf", -12345.6789);
  sprintf(buffer2, "%lf", -12345.6789);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lf_with_precision) {
  char buffer1[128], buffer2[128];
  s21_sprintf(buffer1, "%.2lf", 12345.6789);
  sprintf(buffer2, "%.2lf", 12345.6789);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.0lf", 12345.6789);
  sprintf(buffer2, "%.0lf", 12345.6789);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lf_with_width) {
  char buffer1[128], buffer2[128];
  s21_sprintf(buffer1, "%10lf", 12345.6789);
  sprintf(buffer2, "%10lf", 12345.6789);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%20.5lf", 12345.6789);
  sprintf(buffer2, "%20.5lf", 12345.6789);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lf_with_zero_flag) {
  char buffer1[128], buffer2[128];
  s21_sprintf(buffer1, "%010.3lf", 12345.6789);
  sprintf(buffer2, "%010.3lf", 12345.6789);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%010.0lf", 12345.6789);
  sprintf(buffer2, "%010.0lf", 12345.6789);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lf_with_minus_flag) {
  char buffer1[128], buffer2[128];
  s21_sprintf(buffer1, "%-15lf", 12345.6789);
  sprintf(buffer2, "%-15lf", 12345.6789);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lf_with_plus_flag) {
  char buffer1[128], buffer2[128];
  s21_sprintf(buffer1, "%+lf", 12345.6789);
  sprintf(buffer2, "%+lf", 12345.6789);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%+lf", -12345.6789);
  sprintf(buffer2, "%+lf", -12345.6789);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lf_with_space_flag) {
  char buffer1[128], buffer2[128];
  s21_sprintf(buffer1, "% lf", 12345.6789);
  sprintf(buffer2, "% lf", 12345.6789);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "% lf", -12345.6789);
  sprintf(buffer2, "% lf", -12345.6789);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lf_special_values) {
  char buffer1[128], buffer2[128];
  s21_sprintf(buffer1, "%lf", INFINITY);
  sprintf(buffer2, "%lf", INFINITY);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lf", -INFINITY);
  sprintf(buffer2, "%lf", -INFINITY);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lf", NAN);
  sprintf(buffer2, "%lf", NAN);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lf_zero_value) {
  char buffer1[128], buffer2[128];
  s21_sprintf(buffer1, "%lf", 0.0);
  sprintf(buffer2, "%lf", 0.0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%+lf", 0.0);
  sprintf(buffer2, "%+lf", 0.0);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// тесты для u
START_TEST(test_unsigned_int_specifier) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "|%u|", 42);
  sprintf(buffer2, "|%u|", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "|%5u|", 42);
  sprintf(buffer2, "|%5u|", 42);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_u_basic_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%u", 0U);
  sprintf(buffer2, "%u", 0U);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%u", 42U);
  sprintf(buffer2, "%u", 42U);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%u", 123456789U);
  sprintf(buffer2, "%u", 123456789U);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%u", UINT_MAX);
  sprintf(buffer2, "%u", UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_u_with_width) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%10u", 42U);
  sprintf(buffer2, "%10u", 42U);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10u", 42U);
  sprintf(buffer2, "%-10u", 42U);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%010u", 42U);
  sprintf(buffer2, "%010u", 42U);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_u_with_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.5u", 42U);
  sprintf(buffer2, "%.5u", 42U);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.0u", 0U);
  sprintf(buffer2, "%.0u", 0U);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.10u", 123U);
  sprintf(buffer2, "%.10u", 123U);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_u_with_width_and_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%10.5u", 42U);
  sprintf(buffer2, "%10.5u", 42U);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10.5u", 42U);
  sprintf(buffer2, "%-10.5u", 42U);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%10.5u", 42U);
  sprintf(buffer2, "%10.5u", 42U);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_u_large_values) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%u", UINT_MAX);
  sprintf(buffer2, "%u", UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%20u", UINT_MAX);
  sprintf(buffer2, "%20u", UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.10u", UINT_MAX);
  sprintf(buffer2, "%.10u", UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%20.10u", UINT_MAX);
  sprintf(buffer2, "%20.10u", UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_u_edge_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%u", 0U);
  sprintf(buffer2, "%u", 0U);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%u", 1U);
  sprintf(buffer2, "%u", 1U);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%u", UINT_MAX);
  sprintf(buffer2, "%u", UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_u_with_flags) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%010u", 123U);
  sprintf(buffer2, "%010u", 123U);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10u", 123U);
  sprintf(buffer2, "%-10u", 123U);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_u_combined) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%10.5u", 0U);
  sprintf(buffer2, "%10.5u", 0U);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10.5u", 123U);
  sprintf(buffer2, "%-10.5u", 123U);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%10.5u", UINT_MAX);
  sprintf(buffer2, "%10.5u", UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// тесты для hu

START_TEST(test_hu_basic_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%hu", (unsigned short)0);
  sprintf(buffer2, "%hu", (unsigned short)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%hu", (unsigned short)42);
  sprintf(buffer2, "%hu", (unsigned short)42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%hu",
              (unsigned short)65535);  // Максимум для unsigned short
  sprintf(buffer2, "%hu", (unsigned short)65535);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hu_with_width) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%5hu", (unsigned short)42);
  sprintf(buffer2, "%5hu", (unsigned short)42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-5hu", (unsigned short)42);
  sprintf(buffer2, "%-5hu", (unsigned short)42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%05hu", (unsigned short)42);
  sprintf(buffer2, "%05hu", (unsigned short)42);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hu_with_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.5hu", (unsigned short)42);
  sprintf(buffer2, "%.5hu", (unsigned short)42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.0hu", (unsigned short)0);
  sprintf(buffer2, "%.0hu", (unsigned short)0);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем ""

  s21_sprintf(buffer1, "%.10hu", (unsigned short)123);
  sprintf(buffer2, "%.10hu", (unsigned short)123);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hu_with_width_and_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%10.5hu", (unsigned short)42);
  sprintf(buffer2, "%10.5hu", (unsigned short)42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10.5hu", (unsigned short)42);
  sprintf(buffer2, "%-10.5hu", (unsigned short)42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%10.5hu", (unsigned short)42);
  sprintf(buffer2, "%10.5hu", (unsigned short)42);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hu_edge_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%hu", (unsigned short)0);
  sprintf(buffer2, "%hu", (unsigned short)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%hu", (unsigned short)1);
  sprintf(buffer2, "%hu", (unsigned short)1);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%hu",
              (unsigned short)65535);  // Максимум для unsigned short
  sprintf(buffer2, "%hu", (unsigned short)65535);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hu_combined) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%10.5hu", (unsigned short)0);
  sprintf(buffer2, "%10.5hu", (unsigned short)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10.5hu", (unsigned short)123);
  sprintf(buffer2, "%-10.5hu", (unsigned short)123);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%10.5hu", (unsigned short)65535);
  sprintf(buffer2, "%10.5hu", (unsigned short)65535);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hu_large_values) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%hu", (unsigned short)65535);
  sprintf(buffer2, "%hu", (unsigned short)65535);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%20hu", (unsigned short)65535);
  sprintf(buffer2, "%20hu", (unsigned short)65535);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.10hu", (unsigned short)65535);
  sprintf(buffer2, "%.10hu", (unsigned short)65535);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%20.10hu", (unsigned short)65535);
  sprintf(buffer2, "%20.10hu", (unsigned short)65535);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hu_special_cases) {
  char buffer1[100], buffer2[100];

  // Особый случай: значение 0 и точность 0
  s21_sprintf(buffer1, "%.0hu", (unsigned short)0);
  sprintf(buffer2, "%.0hu", (unsigned short)0);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем ""

  // Обычный случай: значение 0 и ненулевая точность
  s21_sprintf(buffer1, "%.1hu", (unsigned short)0);
  sprintf(buffer2, "%.1hu", (unsigned short)0);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем "0"
}
END_TEST

START_TEST(test_hu_with_zero_flag_and_width) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%010hu", (unsigned short)123);
  sprintf(buffer2, "%010hu", (unsigned short)123);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%010hu", (unsigned short)65535);
  sprintf(buffer2, "%010hu", (unsigned short)65535);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hu_minimal_values) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%hu", (unsigned short)0);
  sprintf(buffer2, "%hu", (unsigned short)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%1hu", (unsigned short)0);
  sprintf(buffer2, "%1hu", (unsigned short)0);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hu_maximal_values) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%hu", (unsigned short)65535);
  sprintf(buffer2, "%hu", (unsigned short)65535);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%5hu", (unsigned short)65535);
  sprintf(buffer2, "%5hu", (unsigned short)65535);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.10hu", (unsigned short)65535);
  sprintf(buffer2, "%.10hu", (unsigned short)65535);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hu_combined_width_and_flags) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%05hu", (unsigned short)123);
  sprintf(buffer2, "%05hu", (unsigned short)123);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-5hu", (unsigned short)123);
  sprintf(buffer2, "%-5hu", (unsigned short)123);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%10hu", (unsigned short)123);
  sprintf(buffer2, "%10hu", (unsigned short)123);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hu_with_large_width) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%20hu", (unsigned short)12345);
  sprintf(buffer2, "%20hu", (unsigned short)12345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-20hu", (unsigned short)12345);
  sprintf(buffer2, "%-20hu", (unsigned short)12345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%020hu", (unsigned short)12345);
  sprintf(buffer2, "%020hu", (unsigned short)12345);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hu_precision_with_zero_value) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.0hu", (unsigned short)0);
  sprintf(buffer2, "%.0hu", (unsigned short)0);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем ""

  s21_sprintf(buffer1, "%.1hu", (unsigned short)0);
  sprintf(buffer2, "%.1hu", (unsigned short)0);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем "0"

  s21_sprintf(buffer1, "%.5hu", (unsigned short)0);
  sprintf(buffer2, "%.5hu", (unsigned short)0);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем "00000"
}
END_TEST

START_TEST(test_hu_with_precision_and_width) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%10.5hu", (unsigned short)123);
  sprintf(buffer2, "%10.5hu", (unsigned short)123);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10.5hu", (unsigned short)123);
  sprintf(buffer2, "%-10.5hu", (unsigned short)123);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%10.5hu", (unsigned short)123);
  sprintf(buffer2, "%10.5hu", (unsigned short)123);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hu_special_width_and_zero_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%010hu", (unsigned short)65535);
  sprintf(buffer2, "%010hu", (unsigned short)65535);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%010hu", (unsigned short)1);
  sprintf(buffer2, "%010hu", (unsigned short)1);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%010hu", (unsigned short)0);
  sprintf(buffer2, "%010hu", (unsigned short)0);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hu_large_combinations) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%20.10hu", (unsigned short)65535);
  sprintf(buffer2, "%20.10hu", (unsigned short)65535);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-20.10hu", (unsigned short)65535);
  sprintf(buffer2, "%-20.10hu", (unsigned short)65535);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%20.10hu", (unsigned short)65535);
  sprintf(buffer2, "%20.10hu", (unsigned short)65535);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hu_precision_edge_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.0hu", (unsigned short)1);
  sprintf(buffer2, "%.0hu", (unsigned short)1);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.1hu", (unsigned short)1);
  sprintf(buffer2, "%.1hu", (unsigned short)1);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.2hu", (unsigned short)1);
  sprintf(buffer2, "%.2hu", (unsigned short)1);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hu_edge_cases_with_flags) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%-5hu", (unsigned short)65535);
  sprintf(buffer2, "%-5hu", (unsigned short)65535);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%05hu", (unsigned short)65535);
  sprintf(buffer2, "%05hu", (unsigned short)65535);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%5hu", (unsigned short)65535);
  sprintf(buffer2, "%5hu", (unsigned short)65535);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// тесты для спец lu
START_TEST(test_lu_basic_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%lu", 0UL);
  sprintf(buffer2, "%lu", 0UL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lu", 123456UL);
  sprintf(buffer2, "%lu", 123456UL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lu", ULONG_MAX);
  sprintf(buffer2, "%lu", ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lu_with_width) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%10lu", 42UL);
  sprintf(buffer2, "%10lu", 42UL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10lu", 42UL);
  sprintf(buffer2, "%-10lu", 42UL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%010lu", 42UL);
  sprintf(buffer2, "%010lu", 42UL);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lu_with_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.5lu", 42UL);
  sprintf(buffer2, "%.5lu", 42UL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.0lu", 0UL);
  sprintf(buffer2, "%.0lu", 0UL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.10lu", 123UL);
  sprintf(buffer2, "%.10lu", 123UL);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lu_with_width_and_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%10.5lu", 42UL);
  sprintf(buffer2, "%10.5lu", 42UL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10.5lu", 42UL);
  sprintf(buffer2, "%-10.5lu", 42UL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%10.5lu", 42UL);
  sprintf(buffer2, "%10.5lu", 42UL);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lu_edge_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%lu", 0UL);
  sprintf(buffer2, "%lu", 0UL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lu", 1UL);
  sprintf(buffer2, "%lu", 1UL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lu", ULONG_MAX);
  sprintf(buffer2, "%lu", ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lu_combined) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%10.5lu", 0UL);
  sprintf(buffer2, "%10.5lu", 0UL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10.5lu", 123UL);
  sprintf(buffer2, "%-10.5lu", 123UL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%10.5lu", ULONG_MAX);
  sprintf(buffer2, "%10.5lu", ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lu_large_values) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%lu", ULONG_MAX);
  sprintf(buffer2, "%lu", ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%20lu", ULONG_MAX);
  sprintf(buffer2, "%20lu", ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.10lu", ULONG_MAX);
  sprintf(buffer2, "%.10lu", ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%20.10lu", ULONG_MAX);
  sprintf(buffer2, "%20.10lu", ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lu_special_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.0lu", 0UL);
  sprintf(buffer2, "%.0lu", 0UL);
  ck_assert_str_eq(buffer1, buffer2);  // должно быть ""

  s21_sprintf(buffer1, "%.1lu", 0UL);
  sprintf(buffer2, "%.1lu", 0UL);
  ck_assert_str_eq(buffer1, buffer2);  // должно быть "0"
}
END_TEST

START_TEST(test_lu_large_combinations) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%20.10lu", ULONG_MAX);
  sprintf(buffer2, "%20.10lu", ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-20.10lu", ULONG_MAX);
  sprintf(buffer2, "%-20.10lu", ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%20.10lu", ULONG_MAX);
  sprintf(buffer2, "%20.10lu", ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lu_invalid_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%lu", (unsigned long)(-1));
  sprintf(buffer2, "%lu", (unsigned long)(-1));
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lu_maximum_width) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%50lu", 123456789UL);
  sprintf(buffer2, "%50lu", 123456789UL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-50lu", 123456789UL);
  sprintf(buffer2, "%-50lu", 123456789UL);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// llu
START_TEST(test_llu_basic_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%llu", 0ULL);
  sprintf(buffer2, "%llu", 0ULL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llu", 42ULL);
  sprintf(buffer2, "%llu", 42ULL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llu", ULLONG_MAX);
  sprintf(buffer2, "%llu", ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llu_with_width) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%10llu", 42ULL);
  sprintf(buffer2, "%10llu", 42ULL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10llu", 42ULL);
  sprintf(buffer2, "%-10llu", 42ULL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%010llu", 42ULL);
  sprintf(buffer2, "%010llu", 42ULL);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llu_with_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.5llu", 42ULL);
  sprintf(buffer2, "%.5llu", 42ULL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.0llu", 0ULL);  // Без точности и значение 0
  sprintf(buffer2, "%.0llu", 0ULL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.10llu", 123ULL);
  sprintf(buffer2, "%.10llu", 123ULL);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llu_with_width_and_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%10.5llu", 42ULL);
  sprintf(buffer2, "%10.5llu", 42ULL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10.5llu", 42ULL);
  sprintf(buffer2, "%-10.5llu", 42ULL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%10.5llu", 42ULL);
  sprintf(buffer2, "%10.5llu", 42ULL);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llu_edge_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%llu", 0ULL);
  sprintf(buffer2, "%llu", 0ULL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llu", 1ULL);
  sprintf(buffer2, "%llu", 1ULL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llu", ULLONG_MAX);
  sprintf(buffer2, "%llu", ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llu_combined) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%10.5llu", 0ULL);
  sprintf(buffer2, "%10.5llu", 0ULL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10.5llu", 123ULL);
  sprintf(buffer2, "%-10.5llu", 123ULL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%10.5llu", ULLONG_MAX);
  sprintf(buffer2, "%10.5llu", ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llu_large_values) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%llu", ULLONG_MAX);
  sprintf(buffer2, "%llu", ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%20llu", ULLONG_MAX);
  sprintf(buffer2, "%20llu", ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.10llu", ULLONG_MAX);
  sprintf(buffer2, "%.10llu", ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%20.10llu", ULLONG_MAX);
  sprintf(buffer2, "%20.10llu", ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llu_special_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.0llu", 0ULL);
  sprintf(buffer2, "%.0llu", 0ULL);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем ""

  s21_sprintf(buffer1, "%.1llu", 0ULL);
  sprintf(buffer2, "%.1llu", 0ULL);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем "0"
}
END_TEST

START_TEST(test_llu_large_combinations) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%20.10llu", ULLONG_MAX);
  sprintf(buffer2, "%20.10llu", ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-20.10llu", ULLONG_MAX);
  sprintf(buffer2, "%-20.10llu", ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%20.10llu", ULLONG_MAX);
  sprintf(buffer2, "%20.10llu", ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llu_invalid_cases) {
  char buffer1[100], buffer2[100];

  // Попытка использовать отрицательное число (кастуем к unsigned long long)
  s21_sprintf(buffer1, "%llu", (unsigned long long)(-1));
  sprintf(buffer2, "%llu", (unsigned long long)(-1));
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llu_maximum_width) {
  char buffer1[500], buffer2[500];

  s21_sprintf(buffer1, "%100llu", 123456789ULL);
  sprintf(buffer2, "%100llu", 123456789ULL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-100llu", 123456789ULL);
  sprintf(buffer2, "%-100llu", 123456789ULL);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// тесты для спец g
START_TEST(test_g_specifier_basic) {
  char buffer1[100], buffer2[100];
  s21_sprintf(buffer1, "%.6g", 0.000123456);
  sprintf(buffer2, "%.6g", 0.000123456);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.6g", 123456.78);
  sprintf(buffer2, "%.6g", 123456.78);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_g_specifier_large_numbers) {
  char buffer1[100], buffer2[100];
  s21_sprintf(buffer1, "%.6g", 123456789.123);
  sprintf(buffer2, "%.6g", 123456789.123);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_g_specifier_precision) {
  char buffer1[100], buffer2[100];
  s21_sprintf(buffer1, "%.2g", 0.000123456);
  sprintf(buffer2, "%.2g", 0.000123456);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.2g", 123456.78);
  sprintf(buffer2, "%.2g", 123456.78);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_g_specifier_flags) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%+g", 123.45);
  sprintf(buffer2, "%+g", 123.45);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "% g", 123.45);
  sprintf(buffer2, "% g", 123.45);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_g_specifier_precision_and_zero_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%010.6g", 12345.6789);
  sprintf(buffer2, "%010.6g", 12345.6789);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%010.4g", 0.000123456);
  sprintf(buffer2, "%010.4g", 0.000123456);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%010.2g", 123456.78);
  sprintf(buffer2, "%010.2g", 123456.78);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%010.6g", -0.000123456);
  sprintf(buffer2, "%010.6g", -0.000123456);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%010.4g", -123456.78);
  sprintf(buffer2, "%010.4g", -123456.78);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_g_specifier_zero_flag_with_large_numbers) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%020.8g", 123456789.123);
  sprintf(buffer2, "%020.8g", 123456789.123);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%020.8g", -123456789.123);
  sprintf(buffer2, "%020.8g", -123456789.123);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_g_specifier_precision_zero_flag_small_numbers) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%08.3g", 0.000012345);
  sprintf(buffer2, "%08.3g", 0.000012345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%08.3g", -0.000012345);
  sprintf(buffer2, "%08.3g", -0.000012345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%08.2g", 0.000000123);
  sprintf(buffer2, "%08.2g", 0.000000123);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%08.2g", -0.000000123);
  sprintf(buffer2, "%08.2g", -0.000000123);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_g_specifier_precision_zero_flag_with_hash) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#010.6g", 12345.6789);
  sprintf(buffer2, "%#010.6g", 12345.6789);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#010.4g", 0.000123456);
  sprintf(buffer2, "%#010.4g", 0.000123456);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#010.6g", -12345.6789);
  sprintf(buffer2, "%#010.6g", -12345.6789);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#010.4g", -0.000123456);
  sprintf(buffer2, "%#010.4g", -0.000123456);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

////////
START_TEST(test_float_specifier) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "|%f|", 3.14159);
  sprintf(buffer2, "|%f|", 3.14159);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "|%.2f|", 3.14159);
  sprintf(buffer2, "|%.2f|", 3.14159);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_parse_flags) {
  struct format_info specs;
  const char *p1 = "+d";
  const char *p2 = "-d";
  const char *p3 = " d";

  s21_parse_flags(&p1, &specs);
  ck_assert_int_eq(specs.plus, 1);

  s21_parse_flags(&p2, &specs);
  ck_assert_int_eq(specs.minus, 1);

  s21_parse_flags(&p3, &specs);
  ck_assert_int_eq(specs.space, 1);
}
END_TEST

START_TEST(test_parse_length) {
  struct format_info specs;
  const char *p1 = "hd";
  const char *p2 = "ld";

  s21_parse_length(&p1, &specs);
  ck_assert_int_eq(specs.length, 'h');

  s21_parse_length(&p2, &specs);
  ck_assert_int_eq(specs.length, 'l');
}
END_TEST

START_TEST(test_process_number_format) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "|%hd|", (short)32767);
  sprintf(buffer2, "|%hd|", (short)32767);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "|%hu|", (unsigned short)65535);
  sprintf(buffer2, "|%hu|", (unsigned short)65535);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "|%ld|", 2147483647L);
  sprintf(buffer2, "|%ld|", 2147483647L);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "|%lu|", 4294967295UL);
  sprintf(buffer2, "|%lu|", 4294967295UL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "|%llu|", 18446744073709551615ULL);
  sprintf(buffer2, "|%llu|", 18446744073709551615ULL);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_process_string) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "|%.3s|", "Hello");
  sprintf(buffer2, "|%.3s|", "Hello");
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_apply_width_and_minus) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "|%10d|", 42);
  sprintf(buffer2, "|%10d|", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "|%-10d|", 42);
  sprintf(buffer2, "|%-10d|", 42);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_apply_plus_and_space) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "|%+d|", 42);
  sprintf(buffer2, "|%+d|", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "|% d|", 42);
  sprintf(buffer2, "|% d|", 42);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_int_to_str) {
  char buffer[100];

  s21_int_to_str(0, buffer);
  ck_assert_str_eq(buffer, "0");

  s21_int_to_str(-123, buffer);
  ck_assert_str_eq(buffer, "-123");
}
END_TEST

START_TEST(test_s21_sprintf_long_long) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%lld", 9223372036854775807LL);
  sprintf(buffer2, "%lld", 9223372036854775807LL);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%ld", 2147483647L);
  sprintf(buffer2, "%ld", 2147483647L);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// тесты для спец е

START_TEST(test_spec_e_positive) {
  char buffer1[100], buffer2[100];
  s21_sprintf(buffer1, "%e", 12345.6789);
  sprintf(buffer2, "%e", 12345.6789);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_e_negative) {
  char buffer1[100], buffer2[100];
  s21_sprintf(buffer1, "%e", -12345.6789);
  sprintf(buffer2, "%e", -12345.6789);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_e_zero) {
  char buffer1[100], buffer2[100];
  s21_sprintf(buffer1, "%e", 0.0);
  sprintf(buffer2, "%e", 0.0);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_e_small_number) {
  char buffer1[100], buffer2[100];
  s21_sprintf(buffer1, "%e", 0.00001234);
  sprintf(buffer2, "%e", 0.00001234);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_e_large_number) {
  char buffer1[100], buffer2[100];
  s21_sprintf(buffer1, "%e", 123456789.0);
  sprintf(buffer2, "%e", 123456789.0);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_e_precision) {
  char buffer1[100], buffer2[100];
  s21_sprintf(buffer1, "%.3e", 12345.6789);
  sprintf(buffer2, "%.3e", 12345.6789);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_e_uppercase) {
  char buffer1[100], buffer2[100];
  s21_sprintf(buffer1, "%E", 12345.6789);
  sprintf(buffer2, "%E", 12345.6789);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_e_negative_exponent) {
  char buffer1[100], buffer2[100];
  s21_sprintf(buffer1, "%e", 0.000000123);
  sprintf(buffer2, "%e", 0.000000123);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_e_with_flags) {
  char buffer1[100], buffer2[100];
  s21_sprintf(buffer1, "%+10.3e", 12345.6789);
  sprintf(buffer2, "%+10.3e", 12345.6789);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_e_with_space_flag) {
  char buffer1[100], buffer2[100];
  s21_sprintf(buffer1, "% e", -12345.6789);
  sprintf(buffer2, "% e", -12345.6789);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_e_hash) {
  char buffer1[100], buffer2[100];
  double value = 123.456;

  s21_sprintf(buffer1, "%#e", value);
  sprintf(buffer2, "%#e", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_e_hash_no_fraction) {
  char buffer1[100], buffer2[100];
  double value = 123.0;

  s21_sprintf(buffer1, "%#e", value);
  sprintf(buffer2, "%#e", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_e_hash_zero) {
  char buffer1[100], buffer2[100];
  double value = 0.0;

  s21_sprintf(buffer1, "%#e", value);
  sprintf(buffer2, "%#e", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST
// тесты для спец E
START_TEST(test_spec_E_positive_small) {
  char buffer1[100], buffer2[100];
  double value = 1.23e-10;
  s21_sprintf(buffer1, "%E", value);
  sprintf(buffer2, "%E", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_E_positive_large) {
  char buffer1[100], buffer2[100];
  double value = 1.23e+50;
  s21_sprintf(buffer1, "%E", value);
  sprintf(buffer2, "%E", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_E_negative_small) {
  char buffer1[100], buffer2[100];
  double value = -1.23e-10;
  s21_sprintf(buffer1, "%E", value);
  sprintf(buffer2, "%E", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_E_negative_large) {
  char buffer1[100], buffer2[100];
  double value = -1.23e+50;
  s21_sprintf(buffer1, "%E", value);
  sprintf(buffer2, "%E", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_E_zero) {
  char buffer1[100], buffer2[100];
  double value = 0.0;
  s21_sprintf(buffer1, "%E", value);
  sprintf(buffer2, "%E", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_E_inf) {
  char buffer1[100], buffer2[100];
  double value = INFINITY;
  s21_sprintf(buffer1, "%E", value);
  sprintf(buffer2, "%E", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_E_negative_inf) {
  char buffer1[100], buffer2[100];
  double value = -INFINITY;
  s21_sprintf(buffer1, "%E", value);
  sprintf(buffer2, "%E", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_E_nan) {
  char buffer1[100], buffer2[100];
  double value = NAN;
  s21_sprintf(buffer1, "%E", value);
  sprintf(buffer2, "%E", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_E_precision) {
  char buffer1[100], buffer2[100];
  double value = 1.23456789;
  s21_sprintf(buffer1, "%.5E", value);
  sprintf(buffer2, "%.5E", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_E_width) {
  char buffer1[100], buffer2[100];
  double value = 1.23e-10;
  s21_sprintf(buffer1, "%20E", value);
  sprintf(buffer2, "%20E", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_E_width_precision) {
  char buffer1[100], buffer2[100];
  double value = 1.23e+10;
  s21_sprintf(buffer1, "%20.10E", value);
  sprintf(buffer2, "%20.10E", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_E_hash) {
  char buffer1[100], buffer2[100];
  double value = 1.0;
  s21_sprintf(buffer1, "%#E", value);
  sprintf(buffer2, "%#E", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_E_zero_flag) {
  char buffer1[100], buffer2[100];
  double value = 1.23e-10;
  s21_sprintf(buffer1, "%010E", value);
  sprintf(buffer2, "%010E", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_E_negative_with_zero_flag) {
  char buffer1[100], buffer2[100];
  double value = -1.23e+10;
  s21_sprintf(buffer1, "%020E", value);
  sprintf(buffer2, "%020E", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_E_with_space_flag) {
  char buffer1[100], buffer2[100];
  double value = 1.23e+10;
  s21_sprintf(buffer1, "% E", value);
  sprintf(buffer2, "% E", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_E_with_plus_flag) {
  char buffer1[100], buffer2[100];
  double value = 1.23e+10;
  s21_sprintf(buffer1, "%+E", value);
  sprintf(buffer2, "%+E", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_E_edge_case_min) {
  char buffer1[100], buffer2[100];
  double value = __DBL_MIN__;
  s21_sprintf(buffer1, "%E", value);
  sprintf(buffer2, "%E", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_E_edge_case_max) {
  char buffer1[100], buffer2[100];
  double value = __DBL_MAX__;
  s21_sprintf(buffer1, "%E", value);
  sprintf(buffer2, "%E", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_E_with_special_width_and_precision) {
  char buffer1[100], buffer2[100];
  double value = 12345.6789;
  s21_sprintf(buffer1, "%+10.2E", value);
  sprintf(buffer2, "%+10.2E", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_E_negative_special_width_and_precision) {
  char buffer1[100], buffer2[100];
  double value = -12345.6789;
  s21_sprintf(buffer1, "%+10.2E", value);
  sprintf(buffer2, "%+10.2E", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_E_multiple_flags) {
  char buffer1[100], buffer2[100];
  double value = 1.23e+10;
  s21_sprintf(buffer1, "%-+20.5E", value);
  sprintf(buffer2, "%-+20.5E", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// тесты для спец Le
START_TEST(test_spec_Le_positive) {
  char buffer1[100], buffer2[100];
  long double value = 1.23456789e+10L;
  s21_sprintf(buffer1, "%Le", value);
  sprintf(buffer2, "%Le", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_Le_negative) {
  char buffer1[100], buffer2[100];
  long double value = -1.23456789e+10L;
  s21_sprintf(buffer1, "%Le", value);
  sprintf(buffer2, "%Le", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_Le_zero) {
  char buffer1[100], buffer2[100];
  long double value = 0.0L;
  s21_sprintf(buffer1, "%Le", value);
  sprintf(buffer2, "%Le", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_Le_positive_small) {
  char buffer1[100], buffer2[100];
  long double value = 1.23e-10L;
  s21_sprintf(buffer1, "%Le", value);
  sprintf(buffer2, "%Le", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_Le_positive_large) {
  char buffer1[100], buffer2[100];
  long double value = 1.23e+308L;  // Предел long double
  s21_sprintf(buffer1, "%Le", value);
  sprintf(buffer2, "%Le", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_Le_negative_small) {
  char buffer1[100], buffer2[100];
  long double value = -1.23e-10L;
  s21_sprintf(buffer1, "%Le", value);
  sprintf(buffer2, "%Le", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_Le_negative_large) {
  char buffer1[100], buffer2[100];
  long double value = -1.23e+308L;  // Предел long double
  s21_sprintf(buffer1, "%Le", value);
  sprintf(buffer2, "%Le", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_Le_nan) {
  char buffer1[100], buffer2[100];
  long double value = NAN;
  s21_sprintf(buffer1, "%Le", value);
  sprintf(buffer2, "%Le", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_Le_width) {
  char buffer1[100], buffer2[100];
  long double value = 1.23456789e+10L;
  s21_sprintf(buffer1, "%20Le", value);
  sprintf(buffer2, "%20Le", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_Le_precision) {
  char buffer1[100], buffer2[100];
  long double value = 1.23456789e+10L;
  s21_sprintf(buffer1, "%.5Le", value);
  sprintf(buffer2, "%.5Le", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_Le_width_and_precision) {
  char buffer1[100], buffer2[100];
  long double value = 1.23456789e+10L;
  s21_sprintf(buffer1, "%20.5Le", value);
  sprintf(buffer2, "%20.5Le", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_Le_zero_flag) {
  char buffer1[100], buffer2[100];
  long double value = 1.23456789e+10L;
  s21_sprintf(buffer1, "%020Le", value);
  sprintf(buffer2, "%020Le", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_Le_negative_zero_flag) {
  char buffer1[100], buffer2[100];
  long double value = -1.23456789e+10L;
  s21_sprintf(buffer1, "%020Le", value);
  sprintf(buffer2, "%020Le", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_Le_plus_flag) {
  char buffer1[100], buffer2[100];
  long double value = 1.23456789e+10L;
  s21_sprintf(buffer1, "%+Le", value);
  sprintf(buffer2, "%+Le", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_Le_space_flag) {
  char buffer1[100], buffer2[100];
  long double value = 1.23456789e+10L;
  s21_sprintf(buffer1, "% Le", value);
  sprintf(buffer2, "% Le", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// тесты для LE
START_TEST(test_spec_LE_positive) {
  char buffer1[100], buffer2[100];
  long double value = 1.23456789e+10L;
  s21_sprintf(buffer1, "%LE", value);
  sprintf(buffer2, "%LE", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_LE_negative) {
  char buffer1[100], buffer2[100];
  long double value = -1.23456789e+10L;
  s21_sprintf(buffer1, "%LE", value);
  sprintf(buffer2, "%LE", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_LE_zero) {
  char buffer1[100], buffer2[100];
  long double value = 0.0L;
  s21_sprintf(buffer1, "%LE", value);
  sprintf(buffer2, "%LE", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_LE_positive_small) {
  char buffer1[100], buffer2[100];
  long double value = 1.23e-10L;
  s21_sprintf(buffer1, "%LE", value);
  sprintf(buffer2, "%LE", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_LE_positive_large) {
  char buffer1[100], buffer2[100];
  long double value = 1.23e+308L;  // Предел long double
  s21_sprintf(buffer1, "%LE", value);
  sprintf(buffer2, "%LE", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_LE_negative_small) {
  char buffer1[100], buffer2[100];
  long double value = -1.23e-10L;
  s21_sprintf(buffer1, "%LE", value);
  sprintf(buffer2, "%LE", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_LE_negative_large) {
  char buffer1[100], buffer2[100];
  long double value = -1.23e+308L;  // Предел long double
  s21_sprintf(buffer1, "%LE", value);
  sprintf(buffer2, "%LE", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_LE_nan) {
  char buffer1[100], buffer2[100];
  long double value = NAN;
  s21_sprintf(buffer1, "%LE", value);
  sprintf(buffer2, "%LE", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_LE_width) {
  char buffer1[100], buffer2[100];
  long double value = 1.23456789e+10L;
  s21_sprintf(buffer1, "%20LE", value);
  sprintf(buffer2, "%20LE", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_LE_precision) {
  char buffer1[100], buffer2[100];
  long double value = 1.23456789e+10L;
  s21_sprintf(buffer1, "%.5LE", value);
  sprintf(buffer2, "%.5LE", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_LE_width_and_precision) {
  char buffer1[100], buffer2[100];
  long double value = 1.23456789e+10L;
  s21_sprintf(buffer1, "%20.5LE", value);
  sprintf(buffer2, "%20.5LE", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_LE_zero_flag) {
  char buffer1[100], buffer2[100];
  long double value = 1.23456789e+10L;
  s21_sprintf(buffer1, "%020LE", value);
  sprintf(buffer2, "%020LE", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_LE_negative_zero_flag) {
  char buffer1[100], buffer2[100];
  long double value = -1.23456789e+10L;
  s21_sprintf(buffer1, "%020LE", value);
  sprintf(buffer2, "%020LE", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_LE_plus_flag) {
  char buffer1[100], buffer2[100];
  long double value = 1.23456789e+10L;
  s21_sprintf(buffer1, "%+LE", value);
  sprintf(buffer2, "%+LE", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_LE_space_flag) {
  char buffer1[100], buffer2[100];
  long double value = 1.23456789e+10L;
  s21_sprintf(buffer1, "% LE", value);
  sprintf(buffer2, "% LE", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// тесты для спец f с флагом #

START_TEST(test_spec_f_hash) {
  char buffer1[100], buffer2[100];
  double value = 123.456;

  s21_sprintf(buffer1, "%#f", value);
  sprintf(buffer2, "%#f", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_f_hash_no_fraction) {
  char buffer1[100], buffer2[100];
  double value = 123.0;

  s21_sprintf(buffer1, "%#f", value);
  sprintf(buffer2, "%#f", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_f_hash_zero) {
  char buffer1[100], buffer2[100];
  double value = 0.0;

  s21_sprintf(buffer1, "%#f", value);
  sprintf(buffer2, "%#f", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// тесты флаг 0

START_TEST(test_spec_e_zero_flag) {
  char buffer1[100], buffer2[100];
  double value = 123.456;

  s21_sprintf(buffer1, "%010e", value);
  sprintf(buffer2, "%010e", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_spec_f_zero_flag) {
  char buffer1[100], buffer2[100];
  double value = 123.456;

  s21_sprintf(buffer1, "%010f", value);
  sprintf(buffer2, "%010f", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// тесты спецификаторов формата x и Х
START_TEST(test_x_lowercase) {
  char buffer1[100], buffer2[100];
  unsigned int value = 12345;

  s21_sprintf(buffer1, "%x", value);
  sprintf(buffer2, "%x", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_x_uppercase) {
  char buffer1[100], buffer2[100];
  unsigned int value = 12345;

  s21_sprintf(buffer1, "%X", value);
  sprintf(buffer2, "%X", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_x_with_hash) {
  char buffer1[100], buffer2[100];
  unsigned int value = 12345;

  s21_sprintf(buffer1, "%#x", value);
  sprintf(buffer2, "%#x", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_x_basic_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%x", 0);
  sprintf(buffer2, "%x", 0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%x", 42);
  sprintf(buffer2, "%x", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%x", 255);
  sprintf(buffer2, "%x", 255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%x", 1024);
  sprintf(buffer2, "%x", 1024);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%x", UINT_MAX);
  sprintf(buffer2, "%x", UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_x_with_width) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%10x", 42);
  sprintf(buffer2, "%10x", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10x", 42);
  sprintf(buffer2, "%-10x", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%5x", 255);
  sprintf(buffer2, "%5x", 255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%10x", UINT_MAX);
  sprintf(buffer2, "%10x", UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_x_with_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.5x", 42);
  sprintf(buffer2, "%.5x", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.0x", 0);
  sprintf(buffer2, "%.0x", 0);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем ""

  s21_sprintf(buffer1, "%.8x", 255);
  sprintf(buffer2, "%.8x", 255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.3x", 1024);
  sprintf(buffer2, "%.3x", 1024);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_x_width_and_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%10.5x", 42);
  sprintf(buffer2, "%10.5x", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10.5x", 42);
  sprintf(buffer2, "%-10.5x", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%10.5x", 42);
  sprintf(buffer2, "%10.5x", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%15.5x", UINT_MAX);
  sprintf(buffer2, "%15.5x", UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_x_hash_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#x", 0);
  sprintf(buffer2, "%#x", 0);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем "0"

  s21_sprintf(buffer1, "%#x", 42);
  sprintf(buffer2, "%#x", 42);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем "0x2a"

  s21_sprintf(buffer1, "%#x", UINT_MAX);
  sprintf(buffer2, "%#x", UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#5x", 42);
  sprintf(buffer2, "%#5x", 42);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_x_zero_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%010x", 42);
  sprintf(buffer2, "%010x", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%05x", 255);
  sprintf(buffer2, "%05x", 255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%010x", UINT_MAX);
  sprintf(buffer2, "%010x", UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_x_minus_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%-10x", 42);
  sprintf(buffer2, "%-10x", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-5x", 255);
  sprintf(buffer2, "%-5x", 255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-15x", UINT_MAX);
  sprintf(buffer2, "%-15x", UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_x_flag_combinations) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#010x", 42);
  sprintf(buffer2, "%#010x", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-#10x", 42);
  sprintf(buffer2, "%-#10x", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#5x", 255);
  sprintf(buffer2, "%#5x", 255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#15x", UINT_MAX);
  sprintf(buffer2, "%#15x", UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_x_edge_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%x", 1);
  sprintf(buffer2, "%x", 1);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%x", UINT_MAX);
  sprintf(buffer2, "%x", UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%x", 0x12345678);
  sprintf(buffer2, "%x", 0x12345678);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%x", 0xABCDEF);
  sprintf(buffer2, "%x", 0xABCDEF);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_x_precision_and_hash) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#.0x", 0);
  sprintf(buffer2, "%#.0x", 0);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем ""

  s21_sprintf(buffer1, "%#.8x", 42);
  sprintf(buffer2, "%#.8x", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#.5x", 255);
  sprintf(buffer2, "%#.5x", 255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#10.3x", 1024);
  sprintf(buffer2, "%#10.3x", 1024);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST
// спец Х
START_TEST(test_X_basic_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%X", 0);
  sprintf(buffer2, "%X", 0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%X", 42);
  sprintf(buffer2, "%X", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%X", 255);
  sprintf(buffer2, "%X", 255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%X", 1024);
  sprintf(buffer2, "%X", 1024);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%X", UINT_MAX);
  sprintf(buffer2, "%X", UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_X_with_width) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%10X", 42);
  sprintf(buffer2, "%10X", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10X", 42);
  sprintf(buffer2, "%-10X", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%5X", 255);
  sprintf(buffer2, "%5X", 255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%10X", UINT_MAX);
  sprintf(buffer2, "%10X", UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_X_with_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.5X", 42);
  sprintf(buffer2, "%.5X", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.0X", 0);
  sprintf(buffer2, "%.0X", 0);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем ""

  s21_sprintf(buffer1, "%.8X", 255);
  sprintf(buffer2, "%.8X", 255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.3X", 1024);
  sprintf(buffer2, "%.3X", 1024);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_X_width_and_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%10.5X", 42);
  sprintf(buffer2, "%10.5X", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10.5X", 42);
  sprintf(buffer2, "%-10.5X", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%010.5X", 42);
  sprintf(buffer2, "%10.5X", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%15.5X", UINT_MAX);
  sprintf(buffer2, "%15.5X", UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_X_hash_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#X", 0);
  sprintf(buffer2, "%#X", 0);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем "0"

  s21_sprintf(buffer1, "%#X", 42);
  sprintf(buffer2, "%#X", 42);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем "0X2A"

  s21_sprintf(buffer1, "%#X", UINT_MAX);
  sprintf(buffer2, "%#X", UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#5X", 42);
  sprintf(buffer2, "%#5X", 42);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_X_zero_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%010X", 42);
  sprintf(buffer2, "%010X", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%05X", 255);
  sprintf(buffer2, "%05X", 255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%010X", UINT_MAX);
  sprintf(buffer2, "%010X", UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_X_minus_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%-10X", 42);
  sprintf(buffer2, "%-10X", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-5X", 255);
  sprintf(buffer2, "%-5X", 255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-15X", UINT_MAX);
  sprintf(buffer2, "%-15X", UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_X_flag_combinations) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#010X", 42);
  sprintf(buffer2, "%#010X", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-#10X", 42);
  sprintf(buffer2, "%-#10X", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#5X", 255);
  sprintf(buffer2, "%#5X", 255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#15X", UINT_MAX);
  sprintf(buffer2, "%#15X", UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_X_edge_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%X", 1);
  sprintf(buffer2, "%X", 1);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%X", UINT_MAX);
  sprintf(buffer2, "%X", UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%X", 0x12345678);
  sprintf(buffer2, "%X", 0x12345678);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%X", 0xABCDEF);
  sprintf(buffer2, "%X", 0xABCDEF);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_X_precision_and_hash) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#.0X", 0);
  sprintf(buffer2, "%#.0X", 0);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем "0"

  s21_sprintf(buffer1, "%#.8X", 42);
  sprintf(buffer2, "%#.8X", 42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#.5X", 255);
  sprintf(buffer2, "%#.5X", 255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#10.3X", 1024);
  sprintf(buffer2, "%#10.3X", 1024);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// спец hx
START_TEST(test_hx_basic_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%hx", (unsigned short)0);
  sprintf(buffer2, "%hx", (unsigned short)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%hx", (unsigned short)42);
  sprintf(buffer2, "%hx", (unsigned short)42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%hx", (unsigned short)255);
  sprintf(buffer2, "%hx", (unsigned short)255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%hx", (unsigned short)1024);
  sprintf(buffer2, "%hx", (unsigned short)1024);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%hx", (unsigned short)USHRT_MAX);
  sprintf(buffer2, "%hx", (unsigned short)USHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hx_with_width) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%10hx", (unsigned short)42);
  sprintf(buffer2, "%10hx", (unsigned short)42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10hx", (unsigned short)42);
  sprintf(buffer2, "%-10hx", (unsigned short)42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%5hx", (unsigned short)255);
  sprintf(buffer2, "%5hx", (unsigned short)255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%10hx", (unsigned short)USHRT_MAX);
  sprintf(buffer2, "%10hx", (unsigned short)USHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hx_with_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.5hx", (unsigned short)42);
  sprintf(buffer2, "%.5hx", (unsigned short)42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.0hx", (unsigned short)0);
  sprintf(buffer2, "%.0hx", (unsigned short)0);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем ""

  s21_sprintf(buffer1, "%.8hx", (unsigned short)255);
  sprintf(buffer2, "%.8hx", (unsigned short)255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.3hx", (unsigned short)1024);
  sprintf(buffer2, "%.3hx", (unsigned short)1024);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hx_width_and_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%10.5hx", (unsigned short)42);
  sprintf(buffer2, "%10.5hx", (unsigned short)42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10.5hx", (unsigned short)42);
  sprintf(buffer2, "%-10.5hx", (unsigned short)42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%10.5hx", (unsigned short)42);
  sprintf(buffer2, "%10.5hx", (unsigned short)42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%15.5hx", (unsigned short)USHRT_MAX);
  sprintf(buffer2, "%15.5hx", (unsigned short)USHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hx_hash_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#hx", (unsigned short)0);
  sprintf(buffer2, "%#hx", (unsigned short)0);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем "0"

  s21_sprintf(buffer1, "%#hx", (unsigned short)42);
  sprintf(buffer2, "%#hx", (unsigned short)42);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем "0x2a"

  s21_sprintf(buffer1, "%#hx", (unsigned short)USHRT_MAX);
  sprintf(buffer2, "%#hx", (unsigned short)USHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#5hx", (unsigned short)42);
  sprintf(buffer2, "%#5hx", (unsigned short)42);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hx_zero_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%010hx", (unsigned short)42);
  sprintf(buffer2, "%010hx", (unsigned short)42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%05hx", (unsigned short)255);
  sprintf(buffer2, "%05hx", (unsigned short)255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%010hx", (unsigned short)USHRT_MAX);
  sprintf(buffer2, "%010hx", (unsigned short)USHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hx_minus_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%-10hx", (unsigned short)42);
  sprintf(buffer2, "%-10hx", (unsigned short)42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-5hx", (unsigned short)255);
  sprintf(buffer2, "%-5hx", (unsigned short)255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-15hx", (unsigned short)USHRT_MAX);
  sprintf(buffer2, "%-15hx", (unsigned short)USHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hx_flag_combinations) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#010hx", (unsigned short)42);
  sprintf(buffer2, "%#010hx", (unsigned short)42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-#10hx", (unsigned short)42);
  sprintf(buffer2, "%-#10hx", (unsigned short)42);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#5hx", (unsigned short)255);
  sprintf(buffer2, "%#5hx", (unsigned short)255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#15hx", (unsigned short)USHRT_MAX);
  sprintf(buffer2, "%#15hx", (unsigned short)USHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hx_edge_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%hx", (unsigned short)1);
  sprintf(buffer2, "%hx", (unsigned short)1);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%hx", (unsigned short)USHRT_MAX);
  sprintf(buffer2, "%hx", (unsigned short)USHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%hx", (unsigned short)0x1234);
  sprintf(buffer2, "%hx", (unsigned short)0x1234);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%hx", (unsigned short)0xABCD);
  sprintf(buffer2, "%hx", (unsigned short)0xABCD);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// спец hX
START_TEST(test_hX_basic_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%hX", (unsigned short)0);
  sprintf(buffer2, "%hX", (unsigned short)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%hX", (unsigned short)12);
  sprintf(buffer2, "%hX", (unsigned short)12);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%hX", (unsigned short)4096);
  sprintf(buffer2, "%hX", (unsigned short)4096);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%hX", (unsigned short)0xFFFF);
  sprintf(buffer2, "%hX", (unsigned short)0xFFFF);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%hX", (unsigned short)0xBEEF);
  sprintf(buffer2, "%hX", (unsigned short)0xBEEF);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hX_with_width) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%8hX", (unsigned short)12);
  sprintf(buffer2, "%8hX", (unsigned short)12);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-8hX", (unsigned short)4096);
  sprintf(buffer2, "%-8hX", (unsigned short)4096);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%5hX", (unsigned short)255);
  sprintf(buffer2, "%5hX", (unsigned short)255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%10hX", (unsigned short)USHRT_MAX);
  sprintf(buffer2, "%10hX", (unsigned short)USHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hX_with_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.4hX", (unsigned short)4096);
  sprintf(buffer2, "%.4hX", (unsigned short)4096);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.0hX", (unsigned short)0);
  sprintf(buffer2, "%.0hX", (unsigned short)0);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем ""

  s21_sprintf(buffer1, "%.7hX", (unsigned short)0xBEEF);
  sprintf(buffer2, "%.7hX", (unsigned short)0xBEEF);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.2hX", (unsigned short)255);
  sprintf(buffer2, "%.2hX", (unsigned short)255);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hX_width_and_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%8.5hX", (unsigned short)12);
  sprintf(buffer2, "%8.5hX", (unsigned short)12);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-8.5hX", (unsigned short)4096);
  sprintf(buffer2, "%-8.5hX", (unsigned short)4096);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%10.5hX", (unsigned short)255);
  sprintf(buffer2, "%10.5hX", (unsigned short)255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%12.3hX", (unsigned short)USHRT_MAX);
  sprintf(buffer2, "%12.3hX", (unsigned short)USHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hX_hash_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#hX", (unsigned short)0);
  sprintf(buffer2, "%#hX", (unsigned short)0);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем "0"

  s21_sprintf(buffer1, "%#hX", (unsigned short)12);
  sprintf(buffer2, "%#hX", (unsigned short)12);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем "0XC"

  s21_sprintf(buffer1, "%#hX", (unsigned short)USHRT_MAX);
  sprintf(buffer2, "%#hX", (unsigned short)USHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#8hX", (unsigned short)0xBEEF);
  sprintf(buffer2, "%#8hX", (unsigned short)0xBEEF);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hX_zero_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%08hX", (unsigned short)12);
  sprintf(buffer2, "%08hX", (unsigned short)12);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%05hX", (unsigned short)255);
  sprintf(buffer2, "%05hX", (unsigned short)255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%08hX", (unsigned short)USHRT_MAX);
  sprintf(buffer2, "%08hX", (unsigned short)USHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hX_minus_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%-10hX", (unsigned short)12);
  sprintf(buffer2, "%-10hX", (unsigned short)12);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-5hX", (unsigned short)255);
  sprintf(buffer2, "%-5hX", (unsigned short)255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-15hX", (unsigned short)USHRT_MAX);
  sprintf(buffer2, "%-15hX", (unsigned short)USHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hX_flag_combinations) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#08hX", (unsigned short)12);
  sprintf(buffer2, "%#08hX", (unsigned short)12);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-#10hX", (unsigned short)4096);
  sprintf(buffer2, "%-#10hX", (unsigned short)4096);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#5hX", (unsigned short)255);
  sprintf(buffer2, "%#5hX", (unsigned short)255);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#15hX", (unsigned short)USHRT_MAX);
  sprintf(buffer2, "%#15hX", (unsigned short)USHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_hX_edge_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%hX", (unsigned short)1);
  sprintf(buffer2, "%hX", (unsigned short)1);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%hX", (unsigned short)USHRT_MAX);
  sprintf(buffer2, "%hX", (unsigned short)USHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%hX", (unsigned short)0x1234);
  sprintf(buffer2, "%hX", (unsigned short)0x1234);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%hX", (unsigned short)0xFACE);
  sprintf(buffer2, "%hX", (unsigned short)0xFACE);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// спец lx
START_TEST(test_lx_basic_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%lx", (unsigned long)0);
  sprintf(buffer2, "%lx", (unsigned long)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lx", (unsigned long)54321);
  sprintf(buffer2, "%lx", (unsigned long)54321);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lx", (unsigned long)4294967295);  // 32-битное max
  sprintf(buffer2, "%lx", (unsigned long)4294967295);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lx", (unsigned long)1234567890);
  sprintf(buffer2, "%lx", (unsigned long)1234567890);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lx", (unsigned long)ULONG_MAX);  // Максимум для long
  sprintf(buffer2, "%lx", (unsigned long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lx_with_width) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%20lx", (unsigned long)54321);
  sprintf(buffer2, "%20lx", (unsigned long)54321);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-20lx", (unsigned long)4294967295);
  sprintf(buffer2, "%-20lx", (unsigned long)4294967295);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%10lx", (unsigned long)12345);
  sprintf(buffer2, "%10lx", (unsigned long)12345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%15lx", (unsigned long)ULONG_MAX);
  sprintf(buffer2, "%15lx", (unsigned long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lx_with_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.5lx", (unsigned long)54321);
  sprintf(buffer2, "%.5lx", (unsigned long)54321);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.0lx", (unsigned long)0);
  sprintf(buffer2, "%.0lx", (unsigned long)0);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем ""

  s21_sprintf(buffer1, "%.8lx", (unsigned long)4294967295);
  sprintf(buffer2, "%.8lx", (unsigned long)4294967295);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.3lx", (unsigned long)12345);
  sprintf(buffer2, "%.3lx", (unsigned long)12345);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lx_width_and_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%10.5lx", (unsigned long)54321);
  sprintf(buffer2, "%10.5lx", (unsigned long)54321);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10.5lx", (unsigned long)4294967295);
  sprintf(buffer2, "%-10.5lx", (unsigned long)4294967295);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%20.5lx", (unsigned long)12345);
  sprintf(buffer2, "%20.5lx", (unsigned long)12345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%25.8lx", (unsigned long)ULONG_MAX);
  sprintf(buffer2, "%25.8lx", (unsigned long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lx_hash_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#lx", (unsigned long)0);
  sprintf(buffer2, "%#lx", (unsigned long)0);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем "0"

  s21_sprintf(buffer1, "%#lx", (unsigned long)54321);
  sprintf(buffer2, "%#lx", (unsigned long)54321);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем "0xd431"

  s21_sprintf(buffer1, "%#lx", (unsigned long)ULONG_MAX);
  sprintf(buffer2, "%#lx", (unsigned long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#20lx", (unsigned long)4294967295);
  sprintf(buffer2, "%#20lx", (unsigned long)4294967295);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lx_zero_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%020lx", (unsigned long)54321);
  sprintf(buffer2, "%020lx", (unsigned long)54321);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%015lx", (unsigned long)4294967295);
  sprintf(buffer2, "%015lx", (unsigned long)4294967295);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%025lx", (unsigned long)ULONG_MAX);
  sprintf(buffer2, "%025lx", (unsigned long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lx_minus_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%-20lx", (unsigned long)54321);
  sprintf(buffer2, "%-20lx", (unsigned long)54321);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-15lx", (unsigned long)4294967295);
  sprintf(buffer2, "%-15lx", (unsigned long)4294967295);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-25lx", (unsigned long)ULONG_MAX);
  sprintf(buffer2, "%-25lx", (unsigned long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lx_flag_combinations) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#020lx", (unsigned long)54321);
  sprintf(buffer2, "%#020lx", (unsigned long)54321);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-#25lx", (unsigned long)4294967295);
  sprintf(buffer2, "%-#25lx", (unsigned long)4294967295);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#15lx", (unsigned long)ULONG_MAX);
  sprintf(buffer2, "%#15lx", (unsigned long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lx_edge_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%lx", (unsigned long)1);
  sprintf(buffer2, "%lx", (unsigned long)1);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lx", (unsigned long)ULONG_MAX);
  sprintf(buffer2, "%lx", (unsigned long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lx", (unsigned long)0xABCDEF123);
  sprintf(buffer2, "%lx", (unsigned long)0xABCDEF123);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lx", (unsigned long)0xDEADBEEF);
  sprintf(buffer2, "%lx", (unsigned long)0xDEADBEEF);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// lX
START_TEST(test_lX_basic_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%lX", (unsigned long)0);
  sprintf(buffer2, "%lX", (unsigned long)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lX", (unsigned long)0x1234ABCD);
  sprintf(buffer2, "%lX", (unsigned long)0x1234ABCD);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lX", (unsigned long)4294967295);
  sprintf(buffer2, "%lX", (unsigned long)4294967295);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lX", (unsigned long)ULONG_MAX);
  sprintf(buffer2, "%lX", (unsigned long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lX", (unsigned long)0xDEADBEEF);
  sprintf(buffer2, "%lX", (unsigned long)0xDEADBEEF);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lX_with_width) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%10lX", (unsigned long)0x1F4);
  sprintf(buffer2, "%10lX", (unsigned long)0x1F4);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-15lX", (unsigned long)0xABCDE);
  sprintf(buffer2, "%-15lX", (unsigned long)0xABCDE);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%5lX", (unsigned long)0x55AA55AA);
  sprintf(buffer2, "%5lX", (unsigned long)0x55AA55AA);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%25lX", (unsigned long)ULONG_MAX);
  sprintf(buffer2, "%25lX", (unsigned long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lX_with_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.5lX", (unsigned long)54321);
  sprintf(buffer2, "%.5lX", (unsigned long)54321);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.0lX", (unsigned long)0);
  sprintf(buffer2, "%.0lX", (unsigned long)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.8lX", (unsigned long)4294967295);
  sprintf(buffer2, "%.8lX", (unsigned long)4294967295);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.3lX", (unsigned long)12345);
  sprintf(buffer2, "%.3lX", (unsigned long)12345);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lX_width_and_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%10.5lX", (unsigned long)54321);
  sprintf(buffer2, "%10.5lX", (unsigned long)54321);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10.5lX", (unsigned long)4294967295);
  sprintf(buffer2, "%-10.5lX", (unsigned long)4294967295);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%20.5lX", (unsigned long)12345);
  sprintf(buffer2, "%20.5lX", (unsigned long)12345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%25.8lX", (unsigned long)ULONG_MAX);
  sprintf(buffer2, "%25.8lX", (unsigned long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lX_hash_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#lX", (unsigned long)0);
  sprintf(buffer2, "%#lX", (unsigned long)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#lX", (unsigned long)54321);
  sprintf(buffer2, "%#lX", (unsigned long)54321);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#lX", (unsigned long)ULONG_MAX);
  sprintf(buffer2, "%#lX", (unsigned long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#20lX", (unsigned long)4294967295);
  sprintf(buffer2, "%#20lX", (unsigned long)4294967295);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lX_zero_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%020lX", (unsigned long)54321);
  sprintf(buffer2, "%020lX", (unsigned long)54321);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%015lX", (unsigned long)4294967295);
  sprintf(buffer2, "%015lX", (unsigned long)4294967295);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%025lX", (unsigned long)ULONG_MAX);
  sprintf(buffer2, "%025lX", (unsigned long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lX_minus_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%-20lX", (unsigned long)54321);
  sprintf(buffer2, "%-20lX", (unsigned long)54321);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-15lX", (unsigned long)4294967295);
  sprintf(buffer2, "%-15lX", (unsigned long)4294967295);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-25lX", (unsigned long)ULONG_MAX);
  sprintf(buffer2, "%-25lX", (unsigned long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lX_flag_combinations) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#020lX", (unsigned long)54321);
  sprintf(buffer2, "%#020lX", (unsigned long)54321);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-#25lX", (unsigned long)4294967295);
  sprintf(buffer2, "%-#25lX", (unsigned long)4294967295);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#15lX", (unsigned long)ULONG_MAX);
  sprintf(buffer2, "%#15lX", (unsigned long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lX_edge_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%lX", (unsigned long)1);
  sprintf(buffer2, "%lX", (unsigned long)1);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lX", (unsigned long)ULONG_MAX);
  sprintf(buffer2, "%lX", (unsigned long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lX", (unsigned long)0xABCDEF123);
  sprintf(buffer2, "%lX", (unsigned long)0xABCDEF123);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lX", (unsigned long)0xDEADBEEF);
  sprintf(buffer2, "%lX", (unsigned long)0xDEADBEEF);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Lx
START_TEST(test_Lx_basic_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%llx", (unsigned long long)0);
  sprintf(buffer2, "%llx", (unsigned long long)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llx", (unsigned long long)0x1A2B3C4D5E);
  sprintf(buffer2, "%llx", (unsigned long long)0x1A2B3C4D5E);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llx", (unsigned long long)4294967296);  // 2^32
  sprintf(buffer2, "%llx", (unsigned long long)4294967296);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llx", (unsigned long long)ULONG_MAX);
  sprintf(buffer2, "%llx", (unsigned long long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llx", (unsigned long long)0xCAFEBABE);
  sprintf(buffer2, "%llx", (unsigned long long)0xCAFEBABE);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_Lx_with_width) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%9llx", (unsigned long long)0x12345);
  sprintf(buffer2, "%9llx", (unsigned long long)0x12345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-12llx", (unsigned long long)0x1C2D3E4F);
  sprintf(buffer2, "%-12llx", (unsigned long long)0x1C2D3E4F);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%6llx", (unsigned long long)0xABC123);
  sprintf(buffer2, "%6llx", (unsigned long long)0xABC123);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%18llx", (unsigned long long)ULONG_MAX);
  sprintf(buffer2, "%18llx", (unsigned long long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_Lx_with_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.7llx", (unsigned long long)54321);
  sprintf(buffer2, "%.7llx", (unsigned long long)54321);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.0llx", (unsigned long long)0);
  sprintf(buffer2, "%.0llx", (unsigned long long)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.10llx", (unsigned long long)0xBEEFCAFE);
  sprintf(buffer2, "%.10llx", (unsigned long long)0xBEEFCAFE);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.4llx", (unsigned long long)0x1A2B3C);
  sprintf(buffer2, "%.4llx", (unsigned long long)0x1A2B3C);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_Lx_width_and_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%11.6llx", (unsigned long long)0xFACEB00C);
  sprintf(buffer2, "%11.6llx", (unsigned long long)0xFACEB00C);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-14.8llx", (unsigned long long)0x12345678);
  sprintf(buffer2, "%-14.8llx", (unsigned long long)0x12345678);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%16.5llx", (unsigned long long)54321);
  sprintf(buffer2, "%16.5llx", (unsigned long long)54321);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%23.12llx", (unsigned long long)ULONG_MAX);
  sprintf(buffer2, "%23.12llx", (unsigned long long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_Lx_hash_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#llx", (unsigned long long)0);
  sprintf(buffer2, "%#llx", (unsigned long long)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#llx", (unsigned long long)0xCAFEBABE);
  sprintf(buffer2, "%#llx", (unsigned long long)0xCAFEBABE);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#llx", (unsigned long long)ULONG_MAX);
  sprintf(buffer2, "%#llx", (unsigned long long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#17llx", (unsigned long long)0xBADC0DE);
  sprintf(buffer2, "%#17llx", (unsigned long long)0xBADC0DE);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_Lx_zero_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%019llx", (unsigned long long)0xCAFEBABE);
  sprintf(buffer2, "%019llx", (unsigned long long)0xCAFEBABE);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%013llx", (unsigned long long)0xBEEF);
  sprintf(buffer2, "%013llx", (unsigned long long)0xBEEF);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%021llx", (unsigned long long)ULONG_MAX);
  sprintf(buffer2, "%021llx", (unsigned long long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_Lx_minus_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%-20llx", (unsigned long long)0xCAFEBABE);
  sprintf(buffer2, "%-20llx", (unsigned long long)0xCAFEBABE);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-15llx", (unsigned long long)0xABCDEF);
  sprintf(buffer2, "%-15llx", (unsigned long long)0xABCDEF);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-25llx", (unsigned long long)ULONG_MAX);
  sprintf(buffer2, "%-25llx", (unsigned long long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_Lx_flag_combinations) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#020llx", (unsigned long long)0xFACEB00C);
  sprintf(buffer2, "%#020llx", (unsigned long long)0xFACEB00C);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-#24llx", (unsigned long long)0xBADF00D);
  sprintf(buffer2, "%-#24llx", (unsigned long long)0xBADF00D);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#18llx", (unsigned long long)ULONG_MAX);
  sprintf(buffer2, "%#18llx", (unsigned long long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_Lx_edge_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%llx", (unsigned long long)1);
  sprintf(buffer2, "%llx", (unsigned long long)1);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llx", (unsigned long long)ULONG_MAX);
  sprintf(buffer2, "%llx", (unsigned long long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llx", (unsigned long long)0xDEADBEEF);
  sprintf(buffer2, "%llx", (unsigned long long)0xDEADBEEF);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llx", (unsigned long long)0xBADCAFE);
  sprintf(buffer2, "%llx", (unsigned long long)0xBADCAFE);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST
// llX
START_TEST(test_llX_basic_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%llX", (unsigned long long)0);
  sprintf(buffer2, "%llX", (unsigned long long)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llX", (unsigned long long)0x123456789ABCDEF);
  sprintf(buffer2, "%llX", (unsigned long long)0x123456789ABCDEF);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llX", (unsigned long long)4294967296);  // 2^32
  sprintf(buffer2, "%llX", (unsigned long long)4294967296);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llX", (unsigned long long)ULLONG_MAX);
  sprintf(buffer2, "%llX", (unsigned long long)ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llX", (unsigned long long)0xDEADCAFEBABEFACE);
  sprintf(buffer2, "%llX", (unsigned long long)0xDEADCAFEBABEFACE);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llX_with_width) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%13llX", (unsigned long long)0x12345);
  sprintf(buffer2, "%13llX", (unsigned long long)0x12345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-17llX", (unsigned long long)0x1234ABCD);
  sprintf(buffer2, "%-17llX", (unsigned long long)0x1234ABCD);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%9llX", (unsigned long long)0x5555AAAAFFFF);
  sprintf(buffer2, "%9llX", (unsigned long long)0x5555AAAAFFFF);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%21llX", (unsigned long long)ULLONG_MAX);
  sprintf(buffer2, "%21llX", (unsigned long long)ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llX_with_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.8llX", (unsigned long long)0x12345);
  sprintf(buffer2, "%.8llX", (unsigned long long)0x12345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.0llX", (unsigned long long)0);
  sprintf(buffer2, "%.0llX", (unsigned long long)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.12llX", (unsigned long long)0xABCDEF123456);
  sprintf(buffer2, "%.12llX", (unsigned long long)0xABCDEF123456);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.5llX", (unsigned long long)0x1A2B3C4D);
  sprintf(buffer2, "%.5llX", (unsigned long long)0x1A2B3C4D);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llX_width_and_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%14.7llX", (unsigned long long)0xFACEB00C);
  sprintf(buffer2, "%14.7llX", (unsigned long long)0xFACEB00C);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-18.10llX", (unsigned long long)0xDEADC0DE);
  sprintf(buffer2, "%-18.10llX", (unsigned long long)0xDEADC0DE);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%23.8llX", (unsigned long long)54321);
  sprintf(buffer2, "%23.8llX", (unsigned long long)54321);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%30.16llX", (unsigned long long)ULLONG_MAX);
  sprintf(buffer2, "%30.16llX", (unsigned long long)ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llX_hash_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#llX", (unsigned long long)0);
  sprintf(buffer2, "%#llX", (unsigned long long)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#llX", (unsigned long long)0xCAFEBABE);
  sprintf(buffer2, "%#llX", (unsigned long long)0xCAFEBABE);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#llX", (unsigned long long)ULLONG_MAX);
  sprintf(buffer2, "%#llX", (unsigned long long)ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#19llX", (unsigned long long)0xDEADBEEF);
  sprintf(buffer2, "%#19llX", (unsigned long long)0xDEADBEEF);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llX_zero_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%021llX", (unsigned long long)0xCAFEBABE);
  sprintf(buffer2, "%021llX", (unsigned long long)0xCAFEBABE);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%017llX", (unsigned long long)0xBEEF);
  sprintf(buffer2, "%017llX", (unsigned long long)0xBEEF);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%027llX", (unsigned long long)ULLONG_MAX);
  sprintf(buffer2, "%027llX", (unsigned long long)ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llX_minus_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%-24llX", (unsigned long long)0xCAFEBABE);
  sprintf(buffer2, "%-24llX", (unsigned long long)0xCAFEBABE);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-19llX", (unsigned long long)0xABCDE);
  sprintf(buffer2, "%-19llX", (unsigned long long)0xABCDE);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-29llX", (unsigned long long)ULLONG_MAX);
  sprintf(buffer2, "%-29llX", (unsigned long long)ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llX_flag_combinations) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#021llX", (unsigned long long)0xFACEB00C);
  sprintf(buffer2, "%#021llX", (unsigned long long)0xFACEB00C);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-#26llX", (unsigned long long)0xDEADC0DE);
  sprintf(buffer2, "%-#26llX", (unsigned long long)0xDEADC0DE);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#20llX", (unsigned long long)ULLONG_MAX);
  sprintf(buffer2, "%#20llX", (unsigned long long)ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llX_edge_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%llX", (unsigned long long)1);
  sprintf(buffer2, "%llX", (unsigned long long)1);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llX", (unsigned long long)ULLONG_MAX);
  sprintf(buffer2, "%llX", (unsigned long long)ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llX", (unsigned long long)0xDEADBEEF12345678);
  sprintf(buffer2, "%llX", (unsigned long long)0xDEADBEEF12345678);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llX", (unsigned long long)0xBADC0FFEE);
  sprintf(buffer2, "%llX", (unsigned long long)0xBADC0FFEE);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// о формат
START_TEST(test_o_basic) {
  char buffer1[100], buffer2[100];
  unsigned int value = 123;

  s21_sprintf(buffer1, "%o", value);
  sprintf(buffer2, "%o", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_o_with_hash) {
  char buffer1[100], buffer2[100];
  unsigned int value = 123;

  s21_sprintf(buffer1, "%#o", value);
  sprintf(buffer2, "%#o", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_o_with_precision_1) {
  char buffer1[100], buffer2[100];
  unsigned int value = 123;

  s21_sprintf(buffer1, "%.5o", value);
  sprintf(buffer2, "%.5o", value);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_o_basic_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%o", (unsigned int)0);
  sprintf(buffer2, "%o", (unsigned int)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%o", (unsigned int)12345);
  sprintf(buffer2, "%o", (unsigned int)12345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%o", (unsigned int)UINT_MAX);
  sprintf(buffer2, "%o", (unsigned int)UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%o", (unsigned int)0754);
  sprintf(buffer2, "%o", (unsigned int)0754);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%o", (unsigned int)0xABCDEF);
  sprintf(buffer2, "%o", (unsigned int)0xABCDEF);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_o_with_width) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%8o", (unsigned int)012345);
  sprintf(buffer2, "%8o", (unsigned int)012345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10o", (unsigned int)0754);
  sprintf(buffer2, "%-10o", (unsigned int)0754);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%5o", (unsigned int)055555);
  sprintf(buffer2, "%5o", (unsigned int)055555);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%12o", (unsigned int)UINT_MAX);
  sprintf(buffer2, "%12o", (unsigned int)UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_o_with_precision_2) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.5o", (unsigned int)012345);
  sprintf(buffer2, "%.5o", (unsigned int)012345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.0o", (unsigned int)0);
  sprintf(buffer2, "%.0o", (unsigned int)0);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем ""

  s21_sprintf(buffer1, "%.8o", (unsigned int)0754);
  sprintf(buffer2, "%.8o", (unsigned int)0754);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.3o", (unsigned int)055555);
  sprintf(buffer2, "%.3o", (unsigned int)055555);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_o_width_and_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%10.5o", (unsigned int)012345);
  sprintf(buffer2, "%10.5o", (unsigned int)012345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10.8o", (unsigned int)0754);
  sprintf(buffer2, "%-10.8o", (unsigned int)0754);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%20.3o", (unsigned int)055555);
  sprintf(buffer2, "%20.3o", (unsigned int)055555);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%25.12o", (unsigned int)UINT_MAX);
  sprintf(buffer2, "%25.12o", (unsigned int)UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_o_hash_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#o", (unsigned int)0);
  sprintf(buffer2, "%#o", (unsigned int)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#o", (unsigned int)012345);
  sprintf(buffer2, "%#o", (unsigned int)012345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#o", (unsigned int)UINT_MAX);
  sprintf(buffer2, "%#o", (unsigned int)UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#12o", (unsigned int)0754);
  sprintf(buffer2, "%#12o", (unsigned int)0754);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_o_zero_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%012o", (unsigned int)012345);
  sprintf(buffer2, "%012o", (unsigned int)012345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%08o", (unsigned int)0754);
  sprintf(buffer2, "%08o", (unsigned int)0754);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%018o", (unsigned int)UINT_MAX);
  sprintf(buffer2, "%018o", (unsigned int)UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_o_minus_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%-12o", (unsigned int)012345);
  sprintf(buffer2, "%-12o", (unsigned int)012345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10o", (unsigned int)0754);
  sprintf(buffer2, "%-10o", (unsigned int)0754);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-18o", (unsigned int)UINT_MAX);
  sprintf(buffer2, "%-18o", (unsigned int)UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_o_flag_combinations) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#012o", (unsigned int)012345);
  sprintf(buffer2, "%#012o", (unsigned int)012345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-#15o", (unsigned int)0754);
  sprintf(buffer2, "%-#15o", (unsigned int)0754);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#18o", (unsigned int)UINT_MAX);
  sprintf(buffer2, "%#18o", (unsigned int)UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_o_edge_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%o", (unsigned int)1);
  sprintf(buffer2, "%o", (unsigned int)1);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%o", (unsigned int)UINT_MAX);
  sprintf(buffer2, "%o", (unsigned int)UINT_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%o", (unsigned int)0xABCD);
  sprintf(buffer2, "%o", (unsigned int)0xABCD);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%o", (unsigned int)0754321);
  sprintf(buffer2, "%o", (unsigned int)0754321);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// ho spec
START_TEST(test_ho_basic_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%ho", (unsigned short)0);
  sprintf(buffer2, "%ho", (unsigned short)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%ho", (unsigned short)12345);
  sprintf(buffer2, "%ho", (unsigned short)12345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%ho", (unsigned short)USHRT_MAX);
  sprintf(buffer2, "%ho", (unsigned short)USHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%ho", (unsigned short)0754);
  sprintf(buffer2, "%ho", (unsigned short)0754);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%ho", (unsigned short)0xABCD);
  sprintf(buffer2, "%ho", (unsigned short)0xABCD);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_ho_with_width) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%8ho", (unsigned short)012345);
  sprintf(buffer2, "%8ho", (unsigned short)012345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10ho", (unsigned short)0754);
  sprintf(buffer2, "%-10ho", (unsigned short)0754);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%5ho", (unsigned short)05555);
  sprintf(buffer2, "%5ho", (unsigned short)05555);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%12ho", (unsigned short)USHRT_MAX);
  sprintf(buffer2, "%12ho", (unsigned short)USHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_ho_with_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.5ho", (unsigned short)012345);
  sprintf(buffer2, "%.5ho", (unsigned short)012345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.0ho", (unsigned short)0);
  sprintf(buffer2, "%.0ho", (unsigned short)0);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем ""

  s21_sprintf(buffer1, "%.8ho", (unsigned short)0754);
  sprintf(buffer2, "%.8ho", (unsigned short)0754);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.3ho", (unsigned short)05555);
  sprintf(buffer2, "%.3ho", (unsigned short)05555);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_ho_width_and_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%10.5ho", (unsigned short)012345);
  sprintf(buffer2, "%10.5ho", (unsigned short)012345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10.8ho", (unsigned short)0754);
  sprintf(buffer2, "%-10.8ho", (unsigned short)0754);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%20.3ho", (unsigned short)05555);
  sprintf(buffer2, "%20.3ho", (unsigned short)05555);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%25.12ho", (unsigned short)USHRT_MAX);
  sprintf(buffer2, "%25.12ho", (unsigned short)USHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_ho_hash_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#ho", (unsigned short)0);
  sprintf(buffer2, "%#ho", (unsigned short)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#ho", (unsigned short)012345);
  sprintf(buffer2, "%#ho", (unsigned short)012345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#ho", (unsigned short)USHRT_MAX);
  sprintf(buffer2, "%#ho", (unsigned short)USHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#12ho", (unsigned short)0754);
  sprintf(buffer2, "%#12ho", (unsigned short)0754);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_ho_zero_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%012ho", (unsigned short)012345);
  sprintf(buffer2, "%012ho", (unsigned short)012345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%08ho", (unsigned short)0754);
  sprintf(buffer2, "%08ho", (unsigned short)0754);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%018ho", (unsigned short)USHRT_MAX);
  sprintf(buffer2, "%018ho", (unsigned short)USHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_ho_minus_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%-12ho", (unsigned short)012345);
  sprintf(buffer2, "%-12ho", (unsigned short)012345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10ho", (unsigned short)0754);
  sprintf(buffer2, "%-10ho", (unsigned short)0754);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-18ho", (unsigned short)USHRT_MAX);
  sprintf(buffer2, "%-18ho", (unsigned short)USHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_ho_flag_combinations) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#012ho", (unsigned short)012345);
  sprintf(buffer2, "%#012ho", (unsigned short)012345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-#15ho", (unsigned short)0754);
  sprintf(buffer2, "%-#15ho", (unsigned short)0754);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#18ho", (unsigned short)USHRT_MAX);
  sprintf(buffer2, "%#18ho", (unsigned short)USHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_ho_edge_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%ho", (unsigned short)1);
  sprintf(buffer2, "%ho", (unsigned short)1);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%ho", (unsigned short)USHRT_MAX);
  sprintf(buffer2, "%ho", (unsigned short)USHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%ho", (unsigned short)0xABCD);
  sprintf(buffer2, "%ho", (unsigned short)0xABCD);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%ho", (unsigned short)0754321);
  sprintf(buffer2, "%ho", (unsigned short)0754321);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// lo спец
START_TEST(test_lo_basic_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%lo", (unsigned long)0);
  sprintf(buffer2, "%lo", (unsigned long)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lo", (unsigned long)123456789);
  sprintf(buffer2, "%lo", (unsigned long)123456789);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lo", (unsigned long)4294967295);  // 32-битный максимум
  sprintf(buffer2, "%lo", (unsigned long)4294967295);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lo",
              (unsigned long)ULONG_MAX);  // Максимальное значение
  sprintf(buffer2, "%lo", (unsigned long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lo", (unsigned long)0xCAFEBABE);
  sprintf(buffer2, "%lo", (unsigned long)0xCAFEBABE);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lo",
              (unsigned long)0777777777777777777);  // Octal максимум
  sprintf(buffer2, "%lo", (unsigned long)0777777777777777777);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lo_with_width) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%15lo", (unsigned long)123456789);
  sprintf(buffer2, "%15lo", (unsigned long)123456789);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-18lo", (unsigned long)4294967295);
  sprintf(buffer2, "%-18lo", (unsigned long)4294967295);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%9lo", (unsigned long)0xDEADBEEF);
  sprintf(buffer2, "%9lo", (unsigned long)0xDEADBEEF);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%25lo", (unsigned long)ULONG_MAX);
  sprintf(buffer2, "%25lo", (unsigned long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%10lo", (unsigned long)0777);
  sprintf(buffer2, "%10lo", (unsigned long)0777);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lo_with_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.5lo", (unsigned long)123456789);
  sprintf(buffer2, "%.5lo", (unsigned long)123456789);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.0lo", (unsigned long)0);
  sprintf(buffer2, "%.0lo", (unsigned long)0);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем ""

  s21_sprintf(buffer1, "%.10lo", (unsigned long)4294967295);
  sprintf(buffer2, "%.10lo", (unsigned long)4294967295);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.4lo", (unsigned long)0xDEADCAFEBABE);
  sprintf(buffer2, "%.4lo", (unsigned long)0xDEADCAFEBABE);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.8lo", (unsigned long)077777777);
  sprintf(buffer2, "%.8lo", (unsigned long)077777777);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lo_width_and_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%20.8lo", (unsigned long)123456789);
  sprintf(buffer2, "%20.8lo", (unsigned long)123456789);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-25.12lo", (unsigned long)4294967295);
  sprintf(buffer2, "%-25.12lo", (unsigned long)4294967295);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%30.15lo", (unsigned long)0777);
  sprintf(buffer2, "%30.15lo", (unsigned long)0777);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%27.10lo", (unsigned long)ULONG_MAX);
  sprintf(buffer2, "%27.10lo", (unsigned long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lo_hash_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#lo", (unsigned long)0);
  sprintf(buffer2, "%#lo", (unsigned long)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#lo", (unsigned long)123456789);
  sprintf(buffer2, "%#lo", (unsigned long)123456789);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#lo", (unsigned long)4294967295);
  sprintf(buffer2, "%#lo", (unsigned long)4294967295);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#25lo", (unsigned long)ULONG_MAX);
  sprintf(buffer2, "%#25lo", (unsigned long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#12lo", (unsigned long)077777777);
  sprintf(buffer2, "%#12lo", (unsigned long)077777777);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lo_zero_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%012lo", (unsigned long)123456789);
  sprintf(buffer2, "%012lo", (unsigned long)123456789);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%08lo", (unsigned long)0xDEADBEEF);
  sprintf(buffer2, "%08lo", (unsigned long)0xDEADBEEF);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%022lo", (unsigned long)0777);
  sprintf(buffer2, "%022lo", (unsigned long)0777);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%030lo", (unsigned long)ULONG_MAX);
  sprintf(buffer2, "%030lo", (unsigned long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lo_minus_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%-18lo", (unsigned long)123456789);
  sprintf(buffer2, "%-18lo", (unsigned long)123456789);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-12lo", (unsigned long)0xCAFEBABE);
  sprintf(buffer2, "%-12lo", (unsigned long)0xCAFEBABE);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-30lo", (unsigned long)ULONG_MAX);
  sprintf(buffer2, "%-30lo", (unsigned long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lo_flag_combinations) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#018lo", (unsigned long)123456789);
  sprintf(buffer2, "%#018lo", (unsigned long)123456789);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-#24lo", (unsigned long)0xBADC0DE);
  sprintf(buffer2, "%-#24lo", (unsigned long)0xBADC0DE);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#30lo", (unsigned long)ULONG_MAX);
  sprintf(buffer2, "%#30lo", (unsigned long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_lo_edge_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%lo", (unsigned long)1);
  sprintf(buffer2, "%lo", (unsigned long)1);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lo", (unsigned long)ULONG_MAX);
  sprintf(buffer2, "%lo", (unsigned long)ULONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lo", (unsigned long)0xABCDEF);
  sprintf(buffer2, "%lo", (unsigned long)0xABCDEF);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%lo", (unsigned long)0777777);
  sprintf(buffer2, "%lo", (unsigned long)0777777);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// llo
START_TEST(test_llo_basic_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%llo", (unsigned long long)0);
  sprintf(buffer2, "%llo", (unsigned long long)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llo", (unsigned long long)1234567890123456789);
  sprintf(buffer2, "%llo", (unsigned long long)1234567890123456789);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llo",
              (unsigned long long)9223372036854775807);  // Max signed 64-bit
  sprintf(buffer2, "%llo", (unsigned long long)9223372036854775807);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llo", (unsigned long long)ULLONG_MAX);
  sprintf(buffer2, "%llo", (unsigned long long)ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llo", (unsigned long long)0123456701234567);
  sprintf(buffer2, "%llo", (unsigned long long)0123456701234567);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llo", (unsigned long long)0xFFFFFFFFFFFFFFF);
  sprintf(buffer2, "%llo", (unsigned long long)0xFFFFFFFFFFFFFFF);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llo_with_width) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%20llo", (unsigned long long)123456789012345);
  sprintf(buffer2, "%20llo", (unsigned long long)123456789012345);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-25llo", (unsigned long long)0123456701234567);
  sprintf(buffer2, "%-25llo", (unsigned long long)0123456701234567);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%15llo", (unsigned long long)077777777777777777);
  sprintf(buffer2, "%15llo", (unsigned long long)077777777777777777);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%30llo", (unsigned long long)ULLONG_MAX);
  sprintf(buffer2, "%30llo", (unsigned long long)ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%10llo", (unsigned long long)0777);
  sprintf(buffer2, "%10llo", (unsigned long long)0777);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llo_with_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.5llo", (unsigned long long)0123456701234567);
  sprintf(buffer2, "%.5llo", (unsigned long long)0123456701234567);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.0llo", (unsigned long long)0);
  sprintf(buffer2, "%.0llo", (unsigned long long)0);
  ck_assert_str_eq(buffer1, buffer2);  // Ожидаем ""

  s21_sprintf(buffer1, "%.12llo", (unsigned long long)0777777777777);
  sprintf(buffer2, "%.12llo", (unsigned long long)0777777777777);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.8llo", (unsigned long long)0777);
  sprintf(buffer2, "%.8llo", (unsigned long long)0777);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%.15llo", (unsigned long long)ULLONG_MAX);
  sprintf(buffer2, "%.15llo", (unsigned long long)ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llo_width_and_precision) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%20.8llo", (unsigned long long)1234567890123456789);
  sprintf(buffer2, "%20.8llo", (unsigned long long)1234567890123456789);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-25.12llo", (unsigned long long)0777777777777);
  sprintf(buffer2, "%-25.12llo", (unsigned long long)0777777777777);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%30.10llo", (unsigned long long)0777);
  sprintf(buffer2, "%30.10llo", (unsigned long long)0777);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%27.15llo", (unsigned long long)ULLONG_MAX);
  sprintf(buffer2, "%27.15llo", (unsigned long long)ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llo_hash_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#llo", (unsigned long long)0);
  sprintf(buffer2, "%#llo", (unsigned long long)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#llo", (unsigned long long)0123456701234567);
  sprintf(buffer2, "%#llo", (unsigned long long)0123456701234567);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#llo", (unsigned long long)ULLONG_MAX);
  sprintf(buffer2, "%#llo", (unsigned long long)ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#30llo", (unsigned long long)0777777777777777);
  sprintf(buffer2, "%#30llo", (unsigned long long)0777777777777777);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llo_zero_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%020llo", (unsigned long long)0123456701234567);
  sprintf(buffer2, "%020llo", (unsigned long long)0123456701234567);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%015llo", (unsigned long long)0777777777777);
  sprintf(buffer2, "%015llo", (unsigned long long)0777777777777);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%030llo", (unsigned long long)ULLONG_MAX);
  sprintf(buffer2, "%030llo", (unsigned long long)ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llo_minus_flag) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%-25llo", (unsigned long long)1234567890123456789);
  sprintf(buffer2, "%-25llo", (unsigned long long)1234567890123456789);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-20llo", (unsigned long long)0777777777777777);
  sprintf(buffer2, "%-20llo", (unsigned long long)0777777777777777);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-30llo", (unsigned long long)ULLONG_MAX);
  sprintf(buffer2, "%-30llo", (unsigned long long)ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llo_flag_combinations) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%#020llo", (unsigned long long)1234567890123456789);
  sprintf(buffer2, "%#020llo", (unsigned long long)1234567890123456789);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-#25llo", (unsigned long long)0777777777777777);
  sprintf(buffer2, "%-#25llo", (unsigned long long)0777777777777777);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%#30llo", (unsigned long long)ULLONG_MAX);
  sprintf(buffer2, "%#30llo", (unsigned long long)ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_llo_edge_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%llo", (unsigned long long)1);
  sprintf(buffer2, "%llo", (unsigned long long)1);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llo", (unsigned long long)0777777777777);
  sprintf(buffer2, "%llo", (unsigned long long)0777777777777);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llo", (unsigned long long)ULLONG_MAX);
  sprintf(buffer2, "%llo", (unsigned long long)ULLONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%llo", (unsigned long long)0xDEADBEEF12345678);
  sprintf(buffer2, "%llo", (unsigned long long)0xDEADBEEF12345678);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// р формат
START_TEST(test_p_basic) {
  char buffer1[100], buffer2[100];
  void *ptr = (void *)0x12345;

  s21_sprintf(buffer1, "%p", ptr);
  sprintf(buffer2, "%p", ptr);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_p_null) {
  char buffer1[100], buffer2[100];
  void *ptr = NULL;

  s21_sprintf(buffer1, "%p", ptr);
  sprintf(buffer2, "%p", ptr);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_p_with_width_1) {
  char buffer1[100], buffer2[100];
  void *ptr = (void *)0x12345;

  s21_sprintf(buffer1, "%20p", ptr);
  sprintf(buffer2, "%20p", ptr);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_p_basic_cases) {
  char buffer1[100], buffer2[100];
  void *ptr1 = (void *)0x12345678;
  void *ptr2 = (void *)0;

  s21_sprintf(buffer1, "%p", ptr1);
  sprintf(buffer2, "%p", ptr1);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%p", ptr2);
  sprintf(buffer2, "%p", ptr2);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%p", (void *)0xFFFFFFFF);
  sprintf(buffer2, "%p", (void *)0xFFFFFFFF);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%p", (void *)0xDEADBEEF);
  sprintf(buffer2, "%p", (void *)0xDEADBEEF);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%p", (void *)0xCAFEBABE1234);
  sprintf(buffer2, "%p", (void *)0xCAFEBABE1234);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_p_with_width_2) {
  char buffer1[100], buffer2[100];
  void *ptr = (void *)0x12345678;

  s21_sprintf(buffer1, "%10p", ptr);
  sprintf(buffer2, "%10p", ptr);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%20p", (void *)0xFFFFFFFF);
  sprintf(buffer2, "%20p", (void *)0xFFFFFFFF);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%15p", (void *)0xCAFEBABE);
  sprintf(buffer2, "%15p", (void *)0xCAFEBABE);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%25p", (void *)0);
  sprintf(buffer2, "%25p", (void *)0);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%8p", (void *)0xDEADC0DE);
  sprintf(buffer2, "%8p", (void *)0xDEADC0DE);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_p_flag_minus) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%-20p", (void *)0x12345678);
  sprintf(buffer2, "%-20p", (void *)0x12345678);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-15p", (void *)0xCAFEBABE);
  sprintf(buffer2, "%-15p", (void *)0xCAFEBABE);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-30p", (void *)0xFFFFFFFFFFFF);
  sprintf(buffer2, "%-30p", (void *)0xFFFFFFFFFFFF);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%-10p", (void *)0);
  sprintf(buffer2, "%-10p", (void *)0);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_p_edge_cases) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%p", (void *)1);
  sprintf(buffer2, "%p", (void *)1);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%p", (void *)UINTPTR_MAX);
  sprintf(buffer2, "%p", (void *)UINTPTR_MAX);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%p", (void *)0xDEADBEEF);
  sprintf(buffer2, "%p", (void *)0xDEADBEEF);
  ck_assert_str_eq(buffer1, buffer2);

  s21_sprintf(buffer1, "%p", (void *)0x123456789ABCDEF);
  sprintf(buffer2, "%p", (void *)0x123456789ABCDEF);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

Suite *s21_sprintf_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_sprintf");

  tc_core = tcase_create("Core");

  // тесты для спецификатора с
  tcase_add_test(tc_core, test_char_specifier);
  tcase_add_test(tc_core, test_char_specifier_basic);
  tcase_add_test(tc_core, test_char_specifier_width);
  tcase_add_test(tc_core, test_char_specifier_null_char);
  // тесты для wc
  tcase_add_test(tc_core, test_wchar_basic);
  tcase_add_test(tc_core, test_wchar_width);
  tcase_add_test(tc_core, test_wchar_too_big);
  tcase_add_test(tc_core, test_wchar_null);

  // тесты для s
  tcase_add_test(tc_core, test_str_specifier);
  tcase_add_test(tc_core, test_s_null_pointer);
  tcase_add_test(tc_core, test_s_empty_string);
  tcase_add_test(tc_core, test_s_padding_with_minus_flag);
  tcase_add_test(tc_core, test_s_multiple_strings);
  tcase_add_test(tc_core, test_s_precision_and_width);
  tcase_add_test(tc_core, test_s_unicode_characters);
  tcase_add_test(tc_core, test_s_special_characters);
  // тесты для d спецификатора
  tcase_add_test(tc_core, test_int_specifier);
  tcase_add_test(tc_core, test_positive_number);
  tcase_add_test(tc_core, test_zero);
  tcase_add_test(tc_core, test_int_max);
  tcase_add_test(tc_core, test_multiple_numbers);
  tcase_add_test(tc_core, test_with_text);
  tcase_add_test(tc_core, test_leading_zero);
  tcase_add_test(tc_core, test_negative_with_leading_zero);
  tcase_add_test(tc_core, test_large_field_width);
  tcase_add_test(tc_core, test_small_field_width);
  tcase_add_test(tc_core, test_invalid_format);
  tcase_add_test(tc_core, test_width_d_star_positive);
  tcase_add_test(tc_core, test_width_d_star_negative);
  tcase_add_test(tc_core, test_width_d_star_zero);
  // hd
  tcase_add_test(tc_core, test_short_positive);
  tcase_add_test(tc_core, test_short_zero);
  tcase_add_test(tc_core, test_short_with_leading_zeros);
  tcase_add_test(tc_core, test_short_negative_with_leading_zeros);
  tcase_add_test(tc_core, test_short_with_plus_flag);
  tcase_add_test(tc_core, test_short_with_space_flag);
  tcase_add_test(tc_core, test_short_with_large_field_width);
  tcase_add_test(tc_core, test_short_with_small_field_width);
  tcase_add_test(tc_core, test_short_with_precision);
  tcase_add_test(tc_core, test_short_with_precision_and_width);
  tcase_add_test(tc_core, test_short_with_minus_flag);
  tcase_add_test(tc_core, test_short_multiple_values);
  tcase_add_test(tc_core, test_short_edge_case_positive);
  // ld
  tcase_add_test(tc_core, test_long_positive);
  tcase_add_test(tc_core, test_long_zero);
  tcase_add_test(tc_core, test_long_with_plus_flag);
  tcase_add_test(tc_core, test_long_with_space_flag);
  tcase_add_test(tc_core, test_long_with_leading_zeros);
  tcase_add_test(tc_core, test_long_negative_with_leading_zeros);
  tcase_add_test(tc_core, test_long_with_precision);
  tcase_add_test(tc_core, test_long_with_width_and_precision);
  tcase_add_test(tc_core, test_long_negative_with_width_and_precision);
  tcase_add_test(tc_core, test_long_with_minus_flag);
  tcase_add_test(tc_core, test_long_multiple_values);
  tcase_add_test(tc_core, test_long_small_values);
  tcase_add_test(tc_core, test_long_large_width);
  tcase_add_test(tc_core, test_long_small_width);
  tcase_add_test(tc_core, test_long_zero_width_and_precision);
  tcase_add_test(tc_core, test_long_with_star_width);
  tcase_add_test(tc_core, test_long_with_star_precision);
  // lld
  tcase_add_test(tc_core, test_lld_positive);
  tcase_add_test(tc_core, test_lld_zero);
  tcase_add_test(tc_core, test_lld_with_plus_flag);
  tcase_add_test(tc_core, test_lld_with_space_flag);
  tcase_add_test(tc_core, test_lld_with_leading_zeros);
  tcase_add_test(tc_core, test_lld_negative_with_leading_zeros);
  tcase_add_test(tc_core, test_lld_with_precision);
  tcase_add_test(tc_core, test_lld_with_width_and_precision);
  tcase_add_test(tc_core, test_lld_negative_with_width_and_precision);
  tcase_add_test(tc_core, test_lld_with_minus_flag);
  tcase_add_test(tc_core, test_lld_multiple_values);
  tcase_add_test(tc_core, test_lld_small_values);
  tcase_add_test(tc_core, test_lld_large_width);
  tcase_add_test(tc_core, test_lld_small_width);
  tcase_add_test(tc_core, test_lld_zero_width_and_precision);
  tcase_add_test(tc_core, test_lld_with_star_width);
  tcase_add_test(tc_core, test_lld_with_star_precision);

  // тесты для f
  tcase_add_test(tc_core, test_f_basic_cases);
  tcase_add_test(tc_core, test_f_with_flags);
  tcase_add_test(tc_core, test_f_with_width_and_precision);
  tcase_add_test(tc_core, test_f_star_width_and_precision);
  tcase_add_test(tc_core, test_f_precision_zero);
  tcase_add_test(tc_core, test_f_rounding_edge_1);
  tcase_add_test(tc_core, test_f_zero_and_negative_zero);
  tcase_add_test(tc_core, test_f_edge_cases);
  tcase_add_test(tc_core, test_f_precision);
  tcase_add_test(tc_core, test_f_large_values_with_width);
  tcase_add_test(tc_core, test_precision_f_star_positive);
  tcase_add_test(tc_core, test_precision_f_star_negative);
  tcase_add_test(tc_core, test_precision_f_star_zero);
  tcase_add_test(tc_core, test_f_rounding_edge_2);

  // lf
  tcase_add_test(tc_core, test_lf_positive_numbers);
  tcase_add_test(tc_core, test_lf_negative_numbers);
  tcase_add_test(tc_core, test_lf_with_precision);
  tcase_add_test(tc_core, test_lf_with_width);
  tcase_add_test(tc_core, test_lf_with_zero_flag);
  tcase_add_test(tc_core, test_lf_with_minus_flag);
  tcase_add_test(tc_core, test_lf_with_plus_flag);
  tcase_add_test(tc_core, test_lf_with_space_flag);
  tcase_add_test(tc_core, test_lf_special_values);
  tcase_add_test(tc_core, test_lf_zero_value);
  // u
  tcase_add_test(tc_core, test_unsigned_int_specifier);
  tcase_add_test(tc_core, test_u_basic_cases);
  tcase_add_test(tc_core, test_u_with_width);
  tcase_add_test(tc_core, test_u_with_precision);
  tcase_add_test(tc_core, test_u_with_width_and_precision);
  tcase_add_test(tc_core, test_u_large_values);
  tcase_add_test(tc_core, test_u_edge_cases);
  tcase_add_test(tc_core, test_u_with_flags);
  tcase_add_test(tc_core, test_u_combined);

  // hu
  tcase_add_test(tc_core, test_hu_basic_cases);
  tcase_add_test(tc_core, test_hu_with_width);
  tcase_add_test(tc_core, test_hu_with_precision);
  tcase_add_test(tc_core, test_hu_with_width_and_precision);
  tcase_add_test(tc_core, test_hu_edge_cases);
  tcase_add_test(tc_core, test_hu_combined);
  tcase_add_test(tc_core, test_hu_large_values);
  tcase_add_test(tc_core, test_hu_special_cases);
  tcase_add_test(tc_core, test_hu_with_zero_flag_and_width);
  tcase_add_test(tc_core, test_hu_minimal_values);
  tcase_add_test(tc_core, test_hu_maximal_values);
  tcase_add_test(tc_core, test_hu_combined_width_and_flags);
  tcase_add_test(tc_core, test_hu_with_large_width);
  tcase_add_test(tc_core, test_hu_precision_with_zero_value);
  tcase_add_test(tc_core, test_hu_with_precision_and_width);
  tcase_add_test(tc_core, test_hu_special_width_and_zero_flag);
  tcase_add_test(tc_core, test_hu_large_combinations);
  tcase_add_test(tc_core, test_hu_precision_edge_cases);
  tcase_add_test(tc_core, test_hu_edge_cases_with_flags);

  // lu
  tcase_add_test(tc_core, test_lu_basic_cases);
  tcase_add_test(tc_core, test_lu_with_width);
  tcase_add_test(tc_core, test_lu_with_precision);
  tcase_add_test(tc_core, test_lu_with_width_and_precision);
  tcase_add_test(tc_core, test_lu_edge_cases);
  tcase_add_test(tc_core, test_lu_combined);
  tcase_add_test(tc_core, test_lu_large_values);
  tcase_add_test(tc_core, test_lu_special_cases);
  tcase_add_test(tc_core, test_lu_large_combinations);
  tcase_add_test(tc_core, test_lu_invalid_cases);
  tcase_add_test(tc_core, test_lu_maximum_width);

  // llu
  tcase_add_test(tc_core, test_llu_basic_cases);
  tcase_add_test(tc_core, test_llu_with_width);
  tcase_add_test(tc_core, test_llu_with_precision);
  tcase_add_test(tc_core, test_llu_with_width_and_precision);
  tcase_add_test(tc_core, test_llu_edge_cases);
  tcase_add_test(tc_core, test_llu_combined);
  tcase_add_test(tc_core, test_llu_large_values);
  tcase_add_test(tc_core, test_llu_special_cases);
  tcase_add_test(tc_core, test_llu_large_combinations);
  tcase_add_test(tc_core, test_llu_invalid_cases);
  tcase_add_test(tc_core, test_llu_maximum_width);
  // G
  // g
  tcase_add_test(tc_core, test_g_specifier_basic);
  tcase_add_test(tc_core, test_g_specifier_large_numbers);
  tcase_add_test(tc_core, test_g_specifier_precision);
  tcase_add_test(tc_core, test_g_specifier_flags);
  tcase_add_test(tc_core, test_g_specifier_precision_and_zero_flag);
  tcase_add_test(tc_core, test_g_specifier_zero_flag_with_large_numbers);
  tcase_add_test(tc_core, test_g_specifier_precision_zero_flag_small_numbers);
  tcase_add_test(tc_core, test_g_specifier_precision_zero_flag_with_hash);
  tcase_add_test(tc_core, test_float_specifier);
  tcase_add_test(tc_core, test_parse_flags);
  tcase_add_test(tc_core, test_parse_length);
  tcase_add_test(tc_core, test_process_number_format);
  tcase_add_test(tc_core, test_process_string);
  tcase_add_test(tc_core, test_apply_width_and_minus);
  tcase_add_test(tc_core, test_apply_plus_and_space);
  tcase_add_test(tc_core, test_int_to_str);
  tcase_add_test(tc_core, test_s21_sprintf_long_long);
  // тесты для спец е
  tcase_add_test(tc_core, test_spec_e_positive);
  tcase_add_test(tc_core, test_spec_e_negative);
  tcase_add_test(tc_core, test_spec_e_zero);
  tcase_add_test(tc_core, test_spec_e_small_number);
  tcase_add_test(tc_core, test_spec_e_large_number);
  tcase_add_test(tc_core, test_spec_e_precision);
  tcase_add_test(tc_core, test_spec_e_uppercase);
  tcase_add_test(tc_core, test_spec_e_negative_exponent);
  tcase_add_test(tc_core, test_spec_e_with_flags);
  tcase_add_test(tc_core, test_spec_e_with_space_flag);
  tcase_add_test(tc_core, test_spec_e_hash);
  tcase_add_test(tc_core, test_spec_e_hash_no_fraction);
  tcase_add_test(tc_core, test_spec_e_hash_zero);
  // E
  tcase_add_test(tc_core, test_spec_E_positive_small);
  tcase_add_test(tc_core, test_spec_E_positive_large);
  tcase_add_test(tc_core, test_spec_E_negative_small);
  tcase_add_test(tc_core, test_spec_E_negative_large);
  tcase_add_test(tc_core, test_spec_E_zero);
  tcase_add_test(tc_core, test_spec_E_inf);
  tcase_add_test(tc_core, test_spec_E_negative_inf);
  tcase_add_test(tc_core, test_spec_E_nan);
  tcase_add_test(tc_core, test_spec_E_precision);
  tcase_add_test(tc_core, test_spec_E_width);
  tcase_add_test(tc_core, test_spec_E_width_precision);
  tcase_add_test(tc_core, test_spec_E_hash);
  tcase_add_test(tc_core, test_spec_E_zero_flag);
  tcase_add_test(tc_core, test_spec_E_negative_with_zero_flag);
  tcase_add_test(tc_core, test_spec_E_with_space_flag);
  tcase_add_test(tc_core, test_spec_E_with_plus_flag);
  tcase_add_test(tc_core, test_spec_E_edge_case_min);
  tcase_add_test(tc_core, test_spec_E_edge_case_max);
  tcase_add_test(tc_core, test_spec_E_with_special_width_and_precision);
  tcase_add_test(tc_core, test_spec_E_negative_special_width_and_precision);
  tcase_add_test(tc_core, test_spec_E_multiple_flags);
  // Le
  tcase_add_test(tc_core, test_spec_Le_positive);
  tcase_add_test(tc_core, test_spec_Le_negative);
  tcase_add_test(tc_core, test_spec_Le_zero);
  tcase_add_test(tc_core, test_spec_Le_positive_small);
  tcase_add_test(tc_core, test_spec_Le_positive_large);
  tcase_add_test(tc_core, test_spec_Le_negative_small);
  tcase_add_test(tc_core, test_spec_Le_negative_large);
  tcase_add_test(tc_core, test_spec_Le_nan);
  tcase_add_test(tc_core, test_spec_Le_width);
  tcase_add_test(tc_core, test_spec_Le_precision);
  tcase_add_test(tc_core, test_spec_Le_width_and_precision);
  tcase_add_test(tc_core, test_spec_Le_zero_flag);
  tcase_add_test(tc_core, test_spec_Le_negative_zero_flag);
  tcase_add_test(tc_core, test_spec_Le_plus_flag);
  tcase_add_test(tc_core, test_spec_Le_space_flag);
  // LE
  tcase_add_test(tc_core, test_spec_LE_positive);
  tcase_add_test(tc_core, test_spec_LE_negative);
  tcase_add_test(tc_core, test_spec_LE_zero);
  tcase_add_test(tc_core, test_spec_LE_positive_small);
  tcase_add_test(tc_core, test_spec_LE_positive_large);
  tcase_add_test(tc_core, test_spec_LE_negative_small);
  tcase_add_test(tc_core, test_spec_LE_negative_large);
  tcase_add_test(tc_core, test_spec_LE_nan);
  tcase_add_test(tc_core, test_spec_LE_width);
  tcase_add_test(tc_core, test_spec_LE_precision);
  tcase_add_test(tc_core, test_spec_LE_width_and_precision);
  tcase_add_test(tc_core, test_spec_LE_zero_flag);
  tcase_add_test(tc_core, test_spec_LE_negative_zero_flag);
  tcase_add_test(tc_core, test_spec_LE_plus_flag);
  tcase_add_test(tc_core, test_spec_LE_space_flag);
  tcase_add_test(tc_core, test_spec_f_hash);
  tcase_add_test(tc_core, test_spec_f_hash_no_fraction);
  tcase_add_test(tc_core, test_spec_f_hash_zero);
  tcase_add_test(tc_core, test_spec_e_zero_flag);
  tcase_add_test(tc_core, test_spec_f_zero_flag);

  // х формат
  tcase_add_test(tc_core, test_x_lowercase);
  tcase_add_test(tc_core, test_x_uppercase);
  tcase_add_test(tc_core, test_x_with_hash);
  tcase_add_test(tc_core, test_x_basic_cases);
  tcase_add_test(tc_core, test_x_with_width);
  tcase_add_test(tc_core, test_x_with_precision);
  tcase_add_test(tc_core, test_x_width_and_precision);
  tcase_add_test(tc_core, test_x_hash_flag);
  tcase_add_test(tc_core, test_x_zero_flag);
  tcase_add_test(tc_core, test_x_minus_flag);
  tcase_add_test(tc_core, test_x_flag_combinations);
  tcase_add_test(tc_core, test_x_edge_cases);
  tcase_add_test(tc_core, test_x_precision_and_hash);
  // X формат
  tcase_add_test(tc_core, test_X_basic_cases);
  tcase_add_test(tc_core, test_X_with_width);
  tcase_add_test(tc_core, test_X_with_precision);
  tcase_add_test(tc_core, test_X_width_and_precision);
  tcase_add_test(tc_core, test_X_hash_flag);
  tcase_add_test(tc_core, test_X_zero_flag);
  tcase_add_test(tc_core, test_X_minus_flag);
  tcase_add_test(tc_core, test_X_flag_combinations);
  tcase_add_test(tc_core, test_X_edge_cases);
  tcase_add_test(tc_core, test_X_precision_and_hash);

  // hx
  tcase_add_test(tc_core, test_hx_basic_cases);
  tcase_add_test(tc_core, test_hx_with_width);
  tcase_add_test(tc_core, test_hx_with_precision);
  tcase_add_test(tc_core, test_hx_width_and_precision);
  tcase_add_test(tc_core, test_hx_hash_flag);
  tcase_add_test(tc_core, test_hx_zero_flag);
  tcase_add_test(tc_core, test_hx_minus_flag);
  tcase_add_test(tc_core, test_hx_flag_combinations);
  tcase_add_test(tc_core, test_hx_edge_cases);
  // hX
  tcase_add_test(tc_core, test_hX_basic_cases);
  tcase_add_test(tc_core, test_hX_with_width);
  tcase_add_test(tc_core, test_hX_with_precision);
  tcase_add_test(tc_core, test_hX_width_and_precision);
  tcase_add_test(tc_core, test_hX_hash_flag);
  tcase_add_test(tc_core, test_hX_zero_flag);
  tcase_add_test(tc_core, test_hX_minus_flag);
  tcase_add_test(tc_core, test_hX_flag_combinations);
  tcase_add_test(tc_core, test_hX_edge_cases);
  // lx
  tcase_add_test(tc_core, test_lx_basic_cases);
  tcase_add_test(tc_core, test_lx_with_width);
  tcase_add_test(tc_core, test_lx_with_precision);
  tcase_add_test(tc_core, test_lx_width_and_precision);
  tcase_add_test(tc_core, test_lx_hash_flag);
  tcase_add_test(tc_core, test_lx_zero_flag);
  tcase_add_test(tc_core, test_lx_minus_flag);
  tcase_add_test(tc_core, test_lx_flag_combinations);
  tcase_add_test(tc_core, test_lx_edge_cases);
  // lX
  tcase_add_test(tc_core, test_lX_basic_cases);
  tcase_add_test(tc_core, test_lX_with_width);
  tcase_add_test(tc_core, test_lX_with_precision);
  tcase_add_test(tc_core, test_lX_width_and_precision);
  tcase_add_test(tc_core, test_lX_hash_flag);
  tcase_add_test(tc_core, test_lX_zero_flag);
  tcase_add_test(tc_core, test_lX_minus_flag);
  tcase_add_test(tc_core, test_lX_flag_combinations);
  tcase_add_test(tc_core, test_lX_edge_cases);
  // llx
  tcase_add_test(tc_core, test_Lx_basic_cases);
  tcase_add_test(tc_core, test_Lx_with_width);
  tcase_add_test(tc_core, test_Lx_with_precision);
  tcase_add_test(tc_core, test_Lx_width_and_precision);
  tcase_add_test(tc_core, test_Lx_hash_flag);
  tcase_add_test(tc_core, test_Lx_zero_flag);
  tcase_add_test(tc_core, test_Lx_minus_flag);
  tcase_add_test(tc_core, test_Lx_flag_combinations);
  tcase_add_test(tc_core, test_Lx_edge_cases);
  // llX
  tcase_add_test(tc_core, test_llX_basic_cases);
  tcase_add_test(tc_core, test_llX_with_width);
  tcase_add_test(tc_core, test_llX_with_precision);
  tcase_add_test(tc_core, test_llX_width_and_precision);
  tcase_add_test(tc_core, test_llX_hash_flag);
  tcase_add_test(tc_core, test_llX_zero_flag);
  tcase_add_test(tc_core, test_llX_minus_flag);
  tcase_add_test(tc_core, test_llX_flag_combinations);
  tcase_add_test(tc_core, test_llX_edge_cases);
  // o формат
  tcase_add_test(tc_core, test_o_basic);
  tcase_add_test(tc_core, test_o_with_hash);
  tcase_add_test(tc_core, test_o_with_precision_1);
  tcase_add_test(tc_core, test_o_basic_cases);
  tcase_add_test(tc_core, test_o_with_width);
  tcase_add_test(tc_core, test_o_with_precision_2);
  tcase_add_test(tc_core, test_o_width_and_precision);
  tcase_add_test(tc_core, test_o_hash_flag);
  tcase_add_test(tc_core, test_o_zero_flag);
  tcase_add_test(tc_core, test_o_minus_flag);
  tcase_add_test(tc_core, test_o_flag_combinations);
  tcase_add_test(tc_core, test_o_edge_cases);
  // ho
  tcase_add_test(tc_core, test_ho_basic_cases);
  tcase_add_test(tc_core, test_ho_with_width);
  tcase_add_test(tc_core, test_ho_with_precision);
  tcase_add_test(tc_core, test_ho_width_and_precision);
  tcase_add_test(tc_core, test_ho_hash_flag);
  tcase_add_test(tc_core, test_ho_zero_flag);
  tcase_add_test(tc_core, test_ho_minus_flag);
  tcase_add_test(tc_core, test_ho_flag_combinations);
  tcase_add_test(tc_core, test_ho_edge_cases);
  // lo
  tcase_add_test(tc_core, test_lo_basic_cases);
  tcase_add_test(tc_core, test_lo_with_width);
  tcase_add_test(tc_core, test_lo_with_precision);
  tcase_add_test(tc_core, test_lo_width_and_precision);
  tcase_add_test(tc_core, test_lo_hash_flag);
  tcase_add_test(tc_core, test_lo_zero_flag);
  tcase_add_test(tc_core, test_lo_minus_flag);
  tcase_add_test(tc_core, test_lo_flag_combinations);
  tcase_add_test(tc_core, test_lo_edge_cases);
  // llo
  tcase_add_test(tc_core, test_llo_basic_cases);
  tcase_add_test(tc_core, test_llo_with_width);
  tcase_add_test(tc_core, test_llo_with_precision);
  tcase_add_test(tc_core, test_llo_width_and_precision);
  tcase_add_test(tc_core, test_llo_hash_flag);
  tcase_add_test(tc_core, test_llo_zero_flag);
  tcase_add_test(tc_core, test_llo_minus_flag);
  tcase_add_test(tc_core, test_llo_flag_combinations);
  tcase_add_test(tc_core, test_llo_edge_cases);

  // р формат
  tcase_add_test(tc_core, test_p_basic);
  tcase_add_test(tc_core, test_p_null);
  tcase_add_test(tc_core, test_p_with_width_1);
  tcase_add_test(tc_core, test_p_basic_cases);
  tcase_add_test(tc_core, test_p_with_width_2);
  tcase_add_test(tc_core, test_p_flag_minus);
  tcase_add_test(tc_core, test_p_edge_cases);

  suite_add_tcase(s, tc_core);

  return s;
}
