#include <check.h>

#include "../s21_string.h"

START_TEST(test_n_specifier) {
  int value;
  int value_std;
  int num_chars = 0;
  int num_chars_std = 0;
  int result;
  int result_std;

  result = s21_sscanf("42", "%d%n", &value, &num_chars);
  result_std = sscanf("42", "%d%n", &value_std, &num_chars_std);
  ck_assert_int_eq(result, result_std);
  ck_assert_int_eq(value, value_std);
  ck_assert_int_eq(num_chars, num_chars_std);
  ck_assert_int_eq(num_chars, 2);

  result = s21_sscanf("077", "%i%n", &value, &num_chars);
  result_std = sscanf("077", "%i%n", &value_std, &num_chars_std);
  ck_assert_int_eq(result, result_std);
  ck_assert_int_eq(value, value_std);
  ck_assert_int_eq(num_chars, num_chars_std);
  ck_assert_int_eq(num_chars, 3);

  float value1;
  float value1_std;

  result = s21_sscanf("63.23", "%f%n", &value1, &num_chars);
  result_std = sscanf("63.23", "%f%n", &value1_std, &num_chars_std);
  ck_assert_int_eq(result, result_std);
  ck_assert_int_eq(value1, value1_std);
  ck_assert_int_eq(num_chars, num_chars_std);
  ck_assert_int_eq(num_chars, 5);

  result = s21_sscanf("1.0e+40", "%g%n", &value1, &num_chars);
  result_std = sscanf("1.0e+40", "%g%n", &value1_std, &num_chars_std);
  ck_assert_int_eq(result, result_std);
  ck_assert_int_eq(value1, value1_std);
  ck_assert_int_eq(num_chars, num_chars_std);
  ck_assert_int_eq(num_chars, 7);

  char value2[20];
  char value2_s[20];

  result = s21_sscanf("Hello World", "%s%n", value2, &num_chars);
  result_std = sscanf("Hello World", "%s%n", value2_s, &num_chars_std);
  ck_assert_int_eq(result, result_std);
  ck_assert_str_eq(value2, value2_s);
  ck_assert_int_eq(num_chars, num_chars_std);
  ck_assert_int_eq(num_chars, 5);

  char value3;
  char value3_s;

  result = s21_sscanf("a", "%c%n", &value3, &num_chars);
  result_std = sscanf("a", "%c%n", &value3_s, &num_chars_std);
  ck_assert_int_eq(result, result_std);
  ck_assert_int_eq(value3, value3_s);
  ck_assert_int_eq(num_chars, num_chars_std);
  ck_assert_int_eq(num_chars, 1);

  void *ptr1 = NULL, *ptr2 = NULL;

  result = s21_sscanf("0x7ffeefbff5f0", "%p%n", &ptr1, &num_chars);
  result_std = sscanf("0x7ffeefbff5f0", "%p%n", &ptr2, &num_chars_std);
  ck_assert_int_eq(result, result_std);
  ck_assert_ptr_eq(ptr1, ptr2);
  ck_assert_int_eq(num_chars, num_chars_std);
  ck_assert_int_eq(num_chars, 14);
}
END_TEST

START_TEST(test_several_specifier) {
  char buffer;
  int value;
  int value_std;
  char buffer_std;
  int result;
  int result_std;

  result = s21_sscanf("42abc", "%d%c", &value, &buffer);
  result_std = sscanf("42abc", "%d%c", &value_std, &buffer_std);
  ck_assert_int_eq(result, result_std);
  ck_assert_int_eq(value, value_std);
  ck_assert_int_eq(buffer, buffer_std);

  char buffer1[100];
  char buffer1_std[100];

  result = s21_sscanf("42abc", "%d%s", &value, buffer1);
  result_std = sscanf("42abc", "%d%s", &value_std, buffer1_std);
  ck_assert_int_eq(result, result_std);
  ck_assert_int_eq(value, value_std);
  ck_assert_str_eq(buffer1, buffer1_std);
}
END_TEST

START_TEST(test_specifier_percent) {
  int result;
  int result2;

  char buffer[20];
  char buffer_s[20];

  result = s21_sscanf("abc%def%ghi", "%s", buffer);
  result2 = sscanf("abc%def%ghi", "%s", buffer_s);
  ck_assert_int_eq(result, result2);
  ck_assert_str_eq(buffer, buffer_s);

  result = s21_sscanf("%%abc%def%ghi", "%s", buffer);
  result2 = sscanf("%%abc%def%ghi", "%s", buffer_s);
  ck_assert_int_eq(result, result2);
  ck_assert_str_eq(buffer, buffer_s);

  result = s21_sscanf("%%abc%def%ghi", "%%%s", buffer);
  result2 = sscanf("%%abc%def%ghi", "%%%s", buffer_s);
  ck_assert_int_eq(result, result2);
  ck_assert_str_eq(buffer, buffer_s);

  result = s21_sscanf("%abc%def%ghi", "%s", buffer);
  result2 = sscanf("%abc%def%ghi", "%s", buffer_s);
  ck_assert_int_eq(result, result2);
  ck_assert_str_eq(buffer, buffer_s);

  result = s21_sscanf("%def%ghi", "%%%s", buffer);
  result2 = sscanf("%def%ghi", "%%%s", buffer_s);
  ck_assert_int_eq(result, result2);
  ck_assert_str_eq(buffer, buffer_s);

  result = s21_sscanf("%%%%", "%%%s", buffer);
  result2 = sscanf("%%%%", "%%%s", buffer_s);
  ck_assert_int_eq(result, result2);
  ck_assert_str_eq(buffer, buffer_s);

  int num;
  int num2;

  result = s21_sscanf("123%456", "%d%%%s", &num, buffer);
  result2 = sscanf("123%456", "%d%%%s", &num2, buffer_s);
  ck_assert_int_eq(num, num2);
  ck_assert_str_eq(buffer, buffer_s);
  ck_assert_int_eq(result, result2);

  result = s21_sscanf("50%% discount", "%d%%%s", &num, buffer);
  result2 = sscanf("50%% discount", "%d%%%s", &num2, buffer_s);
  ck_assert_int_eq(num, num2);
  ck_assert_str_eq(buffer, buffer_s);
  ck_assert_int_eq(result, result2);

  result = s21_sscanf("50% discount", "%d%%%s", &num, buffer);
  result2 = sscanf("50% discount", "%d%%%s", &num2, buffer_s);
  ck_assert_int_eq(num, num2);
  ck_assert_str_eq(buffer, buffer_s);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_suppress) {
  int result;
  int result2;

  result = s21_sscanf("a", "%*c");
  result2 = sscanf("a", "%*c");
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(result2, 0);

  result = s21_sscanf("abc", "%*s");
  result2 = sscanf("abc", "%*s");
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(result2, 0);

  result = s21_sscanf("3.14e2", "%*e");
  result2 = sscanf("3.14e2", "%*e");
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(result2, 0);

  result = s21_sscanf("3.14159", "%*f");
  result2 = sscanf("3.14159", "%*f");
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(result2, 0);

  result = s21_sscanf("123", "%*d");
  result2 = sscanf("123", "%*d");
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(result2, 0);

  result = s21_sscanf("0123", "%*i");
  result2 = sscanf("0123", "%*i");
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(result2, 0);

  result = s21_sscanf("0123", "%*o");
  result2 = sscanf("0123", "%*o");
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(result2, 0);

  result = s21_sscanf("0x123abc", "%*p");
  result2 = sscanf("0x123abc", "%*p");
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(result2, 0);
}
END_TEST

START_TEST(test_char) {
  int result;
  int result2;
  char value;
  char value_s;

  result = s21_sscanf("a", "%c", &value);
  result2 = sscanf("a", "%c", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("av", "%c", &value);
  result2 = sscanf("av", "%c", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("av", "%2c", &value);
  result2 = sscanf("av", "%2c", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  wchar_t value1;
  wchar_t value1_s;

  result = s21_sscanf("a", "%lc", &value1);
  result2 = sscanf("a", "%lc", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value1, value1_s);

  result = s21_sscanf("av", "%lc", &value1);
  result2 = sscanf("av", "%lc", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value1, value1_s);
}
END_TEST

START_TEST(test_signed_decimal) {
  int result;
  int result2;
  int value;
  int value_s;

  result = s21_sscanf("42", "%d", &value);
  result2 = sscanf("42", "%d", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("", "%d", &value);
  result2 = sscanf("", "%d", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("235642", "%4d", &value);
  result2 = sscanf("235642", "%4d", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("-123", "%d", &value);
  result2 = sscanf("-123", "%d", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("0123", "%d", &value);
  result2 = sscanf("0123", "%d", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("123a", "%d", &value);
  result2 = sscanf("123a", "%d", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("f123", "%d", &value);
  result2 = sscanf("f123", "%d", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("0xFF", "%d", &value);
  result2 = sscanf("0xFF", "%d", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("0xZF", "%d", &value);
  result2 = sscanf("0xZF", "%d", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("0x7F", "%d", &value);
  result2 = sscanf("0x7F", "%d", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  short int value1;
  short int value1_s;

  result = s21_sscanf("32767", "%hd", &value1);
  result2 = sscanf("32767", "%hd", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value1, value1_s);

  result = s21_sscanf("+32767", "%hd", &value1);
  result2 = sscanf("+32767", "%hd", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value1, value1_s);

  result = s21_sscanf("-32768", "%hd", &value1);
  result2 = sscanf("-32768", "%hd", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value1, value1_s);

  result = s21_sscanf("32769", "%hd", &value1);
  result2 = sscanf("32769", "%hd", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value1, value1_s);

  result = s21_sscanf("-32769", "%hd", &value1);
  result2 = sscanf("-32769", "%hd", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value1, value1_s);

  long int value2;
  long int value2_s;

  result = s21_sscanf("9223372036854775807", "%ld", &value2);
  result = s21_sscanf("9223372036854775807", "%ld", &value2_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value2, value2_s);

  result = s21_sscanf("-9223372036854775807", "%ld", &value2);
  result = s21_sscanf("-9223372036854775807", "%ld", &value2_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value2, value2_s);

  result = s21_sscanf("-9223372036854775809", "%ld", &value2);
  result = s21_sscanf("-9223372036854775809", "%ld", &value2_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value2, value2_s);
}
END_TEST

START_TEST(test_signed_integer) {
  int result;
  int result2;
  int value;
  int value_s;

  result = s21_sscanf("42", "%i", &value);
  result2 = sscanf("42", "%i", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("-42", "%i", &value);
  result2 = sscanf("-42", "%i", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("z2", "%i", &value);
  result2 = sscanf("z2", "%i", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("213442", "%3i", &value);
  result2 = sscanf("213442", "%3i", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("-123", "%i", &value);
  result2 = sscanf("-123", "%i", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("-123", "%2i", &value);
  result2 = sscanf("-123", "%2i", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("077", "%i", &value);
  result2 = sscanf("077", "%i", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("079", "%i", &value);
  result2 = sscanf("079", "%i", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("097", "%i", &value);
  result2 = sscanf("097", "%i", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("z57", "%i", &value);
  result2 = sscanf("z57", "%i", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("-077", "%i", &value);
  result2 = sscanf("-077", "%i", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("07756", "%3i", &value);
  result2 = sscanf("07756", "%3i", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("0x1A2B", "%i", &value);
  result2 = sscanf("0x1A2B", "%i", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("0x1A2ZB", "%i", &value);
  result2 = sscanf("0x1A2ZB", "%i", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("0xZ1A2B", "%i", &value);
  result2 = sscanf("0xZ1A2B", "%i", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("Z0x1A2B", "%i", &value);
  result2 = sscanf("Z0x1A2B", "%i", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("0zx1A2B", "%i", &value);
  result2 = sscanf("0zx1A2B", "%i", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("-0x1A2B", "%i", &value);
  result2 = sscanf("-0x1A2B", "%i", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("0xFFFFF", "%4i", &value);
  result2 = sscanf("0xFFFFF", "%4i", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  short int value1;
  short int value1_s;

  result = s21_sscanf("32767", "%hi", &value1);
  result2 = sscanf("32767", "%hi", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value1, value1_s);

  result = s21_sscanf("+32767", "%hi", &value1);
  result2 = sscanf("+32767", "%hi", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value1, value1_s);

  result = s21_sscanf("-32768", "%hi", &value1);
  result2 = sscanf("-32768", "%hi", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value1, value1_s);

  result = s21_sscanf("32769", "%hi", &value1);
  result2 = sscanf("32769", "%hi", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value1, value1_s);

  result = s21_sscanf("-32769", "%hi", &value1);
  result2 = sscanf("-32769", "%hi", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value1, value1_s);

  result = s21_sscanf("0x7FFF", "%hi", &value1);
  result2 = sscanf("0x7FFF", "%hi", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value1, value1_s);

  result = s21_sscanf("-0x7FFFF", "%hi", &value1);
  result2 = sscanf("-0x7FFFF", "%hi", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value1, value1_s);

  result = s21_sscanf("077777", "%hi", &value1);
  result2 = sscanf("077777", "%hi", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value1, value1_s);

  result = s21_sscanf("-0777777", "%hi", &value1);
  result2 = sscanf("-0777777", "%hi", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value1, value1_s);

  signed long int value2;
  signed long int value2_s;
  result = s21_sscanf("9223372036854775807", "%li", &value2);
  result2 = sscanf("9223372036854775807", "%li", &value2_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value2, value2_s);

  result = s21_sscanf("-9223372036854775807", "%li", &value2);
  result2 = sscanf("-9223372036854775807", "%li", &value2_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value2, value2_s);

  result = s21_sscanf("9223372036854775809", "%li", &value2);
  result2 = sscanf("9223372036854775809", "%li", &value2_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value2, value2_s);

  result = s21_sscanf("0x7FFFFFFFFFFFFFFF", "%li", &value2);
  result2 = sscanf("0x7FFFFFFFFFFFFFFF", "%li", &value2_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value2, value2_s);

  result = s21_sscanf("-0x7FFFFFFFFFFFFFFF", "%li", &value2);
  result2 = sscanf("-0x7FFFFFFFFFFFFFFF", "%li", &value2_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value2, value2_s);

  result = s21_sscanf("0x10000000000000000", "%li", &value2);
  result2 = sscanf("0x10000000000000000", "%li", &value2_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value2, value2_s);

  result = s21_sscanf("0176746312", "%li", &value2);
  result2 = sscanf("0176746312", "%li", &value2_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value2, value2_s);

  result = s21_sscanf("01000000000000000000001", "%li", &value2);
  result2 = sscanf("01000000000000000000001", "%li", &value2_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value2, value2_s);

  result = s21_sscanf("01000000000000000000000", "%li", &value2);
  result2 = sscanf("01000000000000000000000", "%li", &value2_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value2, value2_s);
}
END_TEST

START_TEST(test_float_scientific_lowercase) {
  float value;
  float value_s;
  int result;
  int result2;

  result = s21_sscanf("3.14e2", "%e", &value);
  result2 = sscanf("3.14e2", "%e", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("zz3.14e2", "%e", &value);
  result2 = sscanf("zz3.14e2", "%e", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("3.1z4e2", "%e", &value);
  result2 = sscanf("3.1z4e2", "%e", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("3.14e2z", "%e", &value);
  result2 = sscanf("3.14e2z", "%e", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("3.14e+02", "%e", &value);
  result2 = sscanf("3.14e+02", "%e", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("2.71e3", "%5e", &value);
  result2 = sscanf("2.71e3", "%5e", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("2.71e3", "%4e", &value);
  result2 = sscanf("2.71e3", "%4e", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("2.71e3", "%3e", &value);
  result2 = sscanf("2.71e3", "%3e", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("2.71e+123", "%8e", &value);
  result2 = sscanf("2.71e+123", "%8e", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("1.0e+40", "%e", &value);
  result2 = sscanf("1.0e+40", "%e", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq(value, value_s);

  long double value1;
  long double value1_s;

  result = s21_sscanf("12345.67890", "%Le", &value1);
  result2 = sscanf("12345.67890", "%Le", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_ldouble_eq_tol(value1, value1_s, 1e-9);

  result = s21_sscanf("1.23456789e+04", "%Le", &value1);
  result2 = sscanf("1.23456789e+04", "%Le", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_ldouble_eq_tol(value1, value1_s, 1e-9);

  result = s21_sscanf("-1.0e+5000", "%Le", &value1);
  result2 = sscanf("-1.0e+5000", "%Le", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_ldouble_eq(value1, value1_s);

  result = s21_sscanf("1.0e+5000", "%Le", &value1);
  result2 = sscanf("1.0e+5000", "%Le", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_ldouble_eq(value1, value1_s);
}
END_TEST

START_TEST(test_floatE_scientific_uppercase) {
  float value;
  float value_s;
  int result;
  int result2;

  result = s21_sscanf("3.14E2", "%E", &value);
  result2 = sscanf("3.14E2", "%E", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("z3.14E2", "%E", &value);
  result2 = sscanf("z3.14E2", "%E", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("3.1z4E2", "%E", &value);
  result2 = sscanf("3.1z4E2", "%E", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("3.14E2z", "%E", &value);
  result2 = sscanf("3.14E2z", "%E", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("3.14E+02", "%E", &value);
  result2 = sscanf("3.14E+02", "%E", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("2.71e3", "%5E", &value);
  result2 = sscanf("2.71e3", "%5E", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("2.71e3", "%4E", &value);
  result2 = sscanf("2.71e3", "%4E", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("2.71e3", "%3E", &value);
  result2 = sscanf("2.71e3", "%3E", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("2.71e+123", "%8E", &value);
  result2 = sscanf("2.71e+123", "%8E", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("1.0e+40", "%E", &value);
  result2 = sscanf("1.0e+40", "%E", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq(value, value_s);

  long double value1;
  long double value1_s;

  result = s21_sscanf("12345.67890", "%LE", &value1);
  result2 = sscanf("12345.67890", "%LE", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_ldouble_eq_tol(value1, value1_s, 1e-9);

  result = s21_sscanf("1.23456789e+04", "%LE", &value1);
  result2 = sscanf("1.23456789e+04", "%LE", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_ldouble_eq_tol(value1, value1_s, 1e-9);

  result = s21_sscanf("-1.0e+5000", "%LE", &value1);
  result2 = sscanf("-1.0e+5000", "%LE", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_ldouble_eq(value1, value1_s);

  result = s21_sscanf("1.0e+5000", "%LE", &value1);
  result2 = sscanf("1.0e+5000", "%LE", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_ldouble_eq(value1, value1_s);
}
END_TEST

START_TEST(test_float_decimal) {
  float value;
  float value_s;
  int result;
  int result2;

  result = s21_sscanf("3.14159", "%f", &value);
  result2 = sscanf("3.14159", "%f", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("z3.14159", "%f", &value);
  result2 = sscanf("z3.14159", "%f", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("3.14z159", "%f", &value);
  result2 = sscanf("3.14z159", "%f", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("3.14159z", "%f", &value);
  result2 = sscanf("3.14159z", "%f", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("2.71828", "%f", &value);
  result2 = sscanf("2.71828", "%f", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("-0.57721", "%f", &value);
  result2 = sscanf("-0.57721", "%f", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("2.71828", "%4f", &value);
  result2 = sscanf("2.71828", "%4f", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("2.71828", "%7f", &value);
  result2 = sscanf("2.71828", "%7f", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("2.71828", "%5f", &value);
  result2 = sscanf("2.71828", "%5f", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("-1.0e+40", "%f", &value);
  result2 = sscanf("-1.0e+40", "%f", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq(value, value_s);

  result = s21_sscanf("1.0e+40", "%f", &value);
  result2 = sscanf("1.0e+40", "%f", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq(value, value_s);

  result = s21_sscanf("1.0e-50", "%f", &value);
  result2 = sscanf("1.0e-50", "%f", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq(value, value_s);

  long double value1;
  long double value1_s;

  result = s21_sscanf("2.71828", "%Lf", &value1);
  result2 = sscanf("2.71828", "%Lf", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_ldouble_eq_tol(value1, value1_s, 1e-9);

  result = s21_sscanf("1.0e+5000", "%Lf", &value1);
  result2 = sscanf("1.0e+5000", "%Lf", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_ldouble_eq(value1, value1_s);
}
END_TEST

START_TEST(test_float_decimal_scientific) {
  float value;
  float value_s;
  int result;
  int result2;

  result = s21_sscanf("0.000314159", "%g", &value);
  result2 = sscanf("0.000314159", "%g", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("z0.000314159", "%g", &value);
  result2 = sscanf("z0.000314159", "%g", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("0.0003z14159", "%g", &value);
  result2 = sscanf("0.0003z14159", "%g", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("0.000314159z", "%g", &value);
  result2 = sscanf("0.000314159z", "%g", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("12345.67890", "%g", &value);
  result2 = sscanf("12345.67890", "%g", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq(value, value_s);

  result = s21_sscanf("1.234567890e+04", "%g", &value);
  result2 = sscanf("1.234567890e+04", "%g", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("12345.67890", "%5g", &value);
  result2 = sscanf("12345.67890", "%5g", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("12345.67890", "%8g", &value);
  result2 = sscanf("12345.67890", "%8g", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("12345.67890", "%10g", &value);
  result2 = sscanf("12345.67890", "%10g", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("1.234567890e+04", "%6g", &value);
  result2 = sscanf("1.234567890e+04", "%6g", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("1.234567890e+04", "%12g", &value);
  result2 = sscanf("1.234567890e+04", "%12g", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("1.234567890e+04", "%15g", &value);
  result2 = sscanf("1.234567890e+04", "%15g", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("1.0e+40", "%g", &value);
  result2 = sscanf("1.0e+40", "%g", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq(value, value_s);

  result = s21_sscanf("-1.0e+40", "%g", &value);
  result2 = sscanf("-1.0e+40", "%g", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq(value, value_s);

  result = s21_sscanf("1.0e-50", "%g", &value);
  result2 = sscanf("1.0e-50", "%g", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq(value, value_s);

  result = s21_sscanf("1.23456789e+40", "%g", &value);
  result2 = sscanf("1.23456789e+40", "%g", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq(value, value_s);

  result = s21_sscanf("-1.23456789e+40", "%g", &value);
  result2 = sscanf("-1.23456789e+40", "%g", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq(value, value_s);

  result = s21_sscanf("1.23456789e-50", "%g", &value);
  result2 = sscanf("1.23456789e-50", "%g", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq(value, value_s);

  long double value1;
  long double value1_s;

  result = s21_sscanf("12345.67890", "%Lg", &value1);
  result2 = sscanf("12345.67890", "%Lg", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_ldouble_eq_tol(value1, value1_s, 1e-9);

  result = s21_sscanf("1.0e+5000", "%Lg", &value1);
  result2 = sscanf("1.0e+5000", "%Lg", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_ldouble_eq(value1, value1_s);

  result = s21_sscanf("1.234567890e+04", "%Lg", &value1);
  result2 = sscanf("1.234567890e+04", "%Lg", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_ldouble_eq_tol(value1, value1_s, 1e-9);

  result = s21_sscanf("1.0e+5000", "%Lg", &value1);
  result2 = sscanf("1.0e+5000", "%Lg", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_ldouble_eq(value1, value1_s);
}
END_TEST

START_TEST(test_float_scientific_uppercase) {
  float value;
  float value_s;
  int result;
  int result2;

  result = s21_sscanf("0.000314159", "%G", &value);
  result2 = sscanf("0.000314159", "%G", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("q0.000314159", "%G", &value);
  result2 = sscanf("q0.000314159", "%G", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("123z45.67890", "%G", &value);
  result2 = sscanf("123z45.67890", "%G", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("12345.67890z", "%G", &value);
  result2 = sscanf("12345.67890z", "%G", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("12345.67890", "%G", &value);
  result2 = sscanf("12345.67890", "%G", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("1.234567890e+04", "%G", &value);
  result2 = sscanf("1.234567890e+04", "%G", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("12345.67890", "%5G", &value);
  result2 = sscanf("12345.67890", "%5G", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("12345.67890", "%8G", &value);
  result2 = sscanf("12345.67890", "%8G", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("12345.67890", "%10G", &value);
  result2 = sscanf("12345.67890", "%10G", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("1.234567890e+04", "%6G", &value);
  result2 = sscanf("1.234567890e+04", "%6G", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("1.234567890e+04", "%12G", &value);
  result2 = sscanf("1.234567890e+04", "%12G", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("1.234567890e+04", "%15G", &value);
  result2 = sscanf("1.234567890e+04", "%15G", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq_tol(value, value_s, 1e-9);

  result = s21_sscanf("1.0e+40", "%G", &value);
  result2 = sscanf("1.0e+40", "%G", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq(value, value_s);

  result = s21_sscanf("-1.0e+40", "%G", &value);
  result2 = sscanf("-1.0e+40", "%G", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq(value, value_s);

  result = s21_sscanf("1.0e-50", "%G", &value);
  result2 = sscanf("1.0e-50", "%G", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq(value, value_s);

  result = s21_sscanf("1.23456789e+40", "%G", &value);
  result2 = sscanf("1.23456789e+40", "%G", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq(value, value_s);

  result = s21_sscanf("-1.23456789e+40", "%G", &value);
  result2 = sscanf("-1.23456789e+40", "%G", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq(value, value_s);

  result = s21_sscanf("1.23456789e-50", "%G", &value);
  result2 = sscanf("1.23456789e-50", "%G", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_float_eq(value, value_s);

  long double value1;
  long double value1_s;

  result = s21_sscanf("12345.67890", "%LG", &value1);
  result2 = sscanf("12345.67890", "%LG", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_ldouble_eq_tol(value1, value1_s, 1e-9);

  result = s21_sscanf("1.0e+5000", "%LG", &value1);
  result2 = sscanf("1.0e+5000", "%LG", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_ldouble_eq(value1, value1_s);

  result = s21_sscanf("1.234567890e+04", "%LG", &value1);
  result2 = sscanf("1.234567890e+04", "%LG", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_ldouble_eq_tol(value1, value1_s, 1e-9);

  result = s21_sscanf("1.0e+5000", "%LG", &value1);
  result2 = sscanf("1.0e+5000", "%LG", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_ldouble_eq(value1, value1_s);
}
END_TEST

START_TEST(test_unsigned_octal) {
  int result;
  int result2;
  unsigned int value;
  unsigned int value_s;

  result = s21_sscanf("077", "%o", &value);
  result2 = sscanf("077", "%o", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("079", "%o", &value);
  result2 = sscanf("079", "%o", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("097", "%o", &value);
  result2 = sscanf("097", "%o", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("z097", "%o", &value);
  result2 = sscanf("z097", "%o", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("01234567", "%o", &value);
  result2 = sscanf("01234567", "%o", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  result = s21_sscanf("07756", "%3o", &value);
  result2 = sscanf("07756", "%3o", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value, value_s);

  unsigned short int value1;
  unsigned short int value1_s;

  result = s21_sscanf("177777", "%ho", &value1);
  result2 = sscanf("177777", "%ho", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value1, value1_s);

  result = s21_sscanf("177778", "%ho", &value1);
  result2 = sscanf("177778", "%ho", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value1, value1_s);

  unsigned long int value2;
  unsigned long int value2_s;

  result = s21_sscanf("1777777777777777777777", "%lo", &value2);
  result2 = sscanf("1777777777777777777777", "%lo", &value2_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value2, value2_s);

  result = s21_sscanf("1777777777777777777778", "%lo", &value2);
  result2 = sscanf("1777777777777777777778", "%lo", &value2_s);
  ck_assert_int_eq(result, result2);
  ck_assert_int_eq(value2, value2_s);
}
END_TEST

START_TEST(test_string) {
  int result;
  int result2;
  char value[20];
  char value_s[20];

  result = s21_sscanf("Hello World", "%s", value);
  result2 = sscanf("Hello World", "%s", value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_str_eq(value, value_s);

  result = s21_sscanf("First Word Second", "%s", value);
  result2 = sscanf("First Word Second", "%s", value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_str_eq(value, value_s);

  result = s21_sscanf("First", "%3s", value);
  result2 = sscanf("First", "%3s", value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_str_eq(value, value_s);

  result = s21_sscanf("First", "%1s", value);
  result2 = sscanf("First", "%1s", value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_str_eq(value, value_s);

  result = s21_sscanf(" ", "%s", value);
  result2 = sscanf(" ", "%s", value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_str_eq(value, value_s);

  result = s21_sscanf("First Word Second Door", "%s", value);
  result2 = sscanf("First Word Second Door", "%s", value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_str_eq(value, value_s);

  wchar_t value1[10];
  wchar_t value1_s[10];

  result = s21_sscanf("Hello", "%ls", value1);
  result2 = sscanf("Hello", "%ls", value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_mem_eq(value1, value1_s, sizeof(value));

  result = s21_sscanf("", "%ls", value1);
  result2 = sscanf("", "%ls", value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_mem_eq(value1, value1_s, sizeof(value));
}
END_TEST

START_TEST(test_unsigned_decimal) {
  int result;
  int result2;
  int value;
  int value_s;

  result = s21_sscanf("42", "%u", &value);
  result2 = sscanf("42", "%u", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value, value_s);

  result = s21_sscanf("42v", "%u", &value);
  result2 = sscanf("42v", "%u", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value, value_s);

  result = s21_sscanf("v42", "%u", &value);
  result2 = sscanf("v42", "%u", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value, value_s);

  // большое положительное число, соответствующее двоичному представлению
  //  исходного отрицательного числа, интерпретированного как беззнаковое целое.
  result = s21_sscanf("-42", "%u", &value);
  result2 = sscanf("-42", "%u", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value, value_s);

  result = s21_sscanf("345642", "%2u", &value);
  result2 = sscanf("345642", "%2u", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value, value_s);

  unsigned short int value1;
  unsigned short int value1_s;
  result = s21_sscanf("65535", "%hu", &value1);
  result2 = sscanf("65535", "%hu", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value1, value1_s);

  result = s21_sscanf("65536", "%hu", &value1);
  result2 = sscanf("65536", "%hu", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value1, value1_s);

  unsigned long int value2;
  unsigned long int value2_s;
  result = s21_sscanf("18446744073709551615", "%lu", &value2);
  result2 = sscanf("18446744073709551615", "%lu", &value2_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value2, value2_s);

  result = s21_sscanf("18446744073709551616", "%lu", &value2);
  result2 = sscanf("18446744073709551616", "%lu", &value2_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value2, value2_s);
}
END_TEST

START_TEST(test_unsigned_hexadecimal_lowercase) {
  int result;
  int result2;
  unsigned int value;
  unsigned int value_s;

  result = s21_sscanf("1a2b", "%x", &value);
  result2 = sscanf("1a2b", "%x", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value, value_s);

  result = s21_sscanf("0xff", "%x", &value);
  result2 = sscanf("0xff", "%x", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value, value_s);

  result = s21_sscanf("0x7F77", "%4x", &value);
  result2 = sscanf("0x7F77", "%4x", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value, value_s);

  result = s21_sscanf("0xZF", "%x", &value);
  result2 = sscanf("0xZF", "%x", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value, value_s);

  result = s21_sscanf("Z0xFF", "%x", &value);
  result2 = sscanf("Z0xFF", "%x", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value, value_s);

  result = s21_sscanf("0zxFF", "%x", &value);
  result2 = sscanf("0zxFF", "%x", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value, value_s);

  unsigned short int value1;
  unsigned short int value1_s;

  result = s21_sscanf("0xFFFF", "%hx", &value1);
  result2 = sscanf("0xFFFF", "%hx", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value1, value1_s);

  result = s21_sscanf("0x10000", "%hx", &value1);
  result2 = sscanf("0x10000", "%hx", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value1, value1_s);

  unsigned long int value2;
  unsigned long int value2_s;

  result = s21_sscanf("0xFFFFFFFFFFFFFFFF", "%lx", &value2);
  result2 = sscanf("0xFFFFFFFFFFFFFFFF", "%lx", &value2_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value2, value2_s);

  result = s21_sscanf("0x10000000000000000", "%lx", &value2);
  result2 = sscanf("0x10000000000000000", "%lx", &value2_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value2, value2_s);
}
END_TEST

START_TEST(test_unsigned_hexadecimal_uppercase) {
  int result;
  int result2;
  unsigned int value;
  unsigned int value_s;

  result = s21_sscanf("1a2b", "%X", &value);
  result2 = sscanf("1a2b", "%X", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value, value_s);

  result = s21_sscanf("0xff", "%X", &value);
  result2 = sscanf("0xff", "%X", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value, value_s);

  result = s21_sscanf("0x7F77", "%4X", &value);
  result2 = sscanf("0x7F77", "%4X", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value, value_s);

  result = s21_sscanf("0xZF", "%X", &value);
  result2 = sscanf("0xZF", "%X", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value, value_s);

  result = s21_sscanf("Z0xFF", "%X", &value);
  result2 = sscanf("Z0xFF", "%X", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value, value_s);

  result = s21_sscanf("0zxFF", "%X", &value);
  result2 = sscanf("0zxFF", "%X", &value_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value, value_s);

  unsigned short int value1;
  unsigned short int value1_s;

  result = s21_sscanf("0xFFFF", "%hX", &value1);
  result2 = sscanf("0xFFFF", "%hX", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value1, value1_s);

  result = s21_sscanf("0x10000", "%hX", &value1);
  result2 = sscanf("0x10000", "%hX", &value1_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value1, value1_s);

  unsigned long int value2;
  unsigned long int value2_s;

  result = s21_sscanf("0xFFFFFFFFFFFFFFFF", "%lX", &value2);
  result2 = sscanf("0xFFFFFFFFFFFFFFFF", "%lX", &value2_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value2, value2_s);

  result = s21_sscanf("0x10000000000000000", "%lX", &value2);
  result2 = sscanf("0x10000000000000000", "%lX", &value2_s);
  ck_assert_int_eq(result, result2);
  ck_assert_uint_eq(value2, value2_s);
}
END_TEST

START_TEST(test_pointer) {
  int result1, result2;
  void *ptr1 = NULL, *ptr2 = NULL;

  result1 = s21_sscanf("0x7ffeefbff5f0", "%p", &ptr1);
  result2 = sscanf("0x7ffeefbff5f0", "%p", &ptr2);
  ck_assert_int_eq(result1, result2);
  ck_assert_ptr_eq(ptr1, ptr2);

  result1 = s21_sscanf("0x7ffeefbff5f0", "%5p", &ptr1);
  result2 = sscanf("0x7ffeefbff5f0", "%5p", &ptr2);
  ck_assert_int_eq(result1, result2);
  ck_assert_ptr_eq(ptr1, ptr2);

  result1 = s21_sscanf("0x0", "%p", &ptr1);
  result2 = sscanf("0x0", "%p", &ptr2);
  ck_assert_int_eq(result1, result2);
  ck_assert_ptr_eq(ptr1, ptr2);

  result1 = s21_sscanf("0x123abc", "%p", &ptr1);
  result2 = sscanf("0x123abc", "%p", &ptr2);
  ck_assert_int_eq(result1, result2);
  ck_assert_ptr_eq(ptr1, ptr2);
}
END_TEST

Suite *s21_sscanf_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("S21_Sscanf");
  tc_core = tcase_create("Core");
  // Тесты для спецификаторов
  tcase_add_test(tc_core, test_n_specifier);
  tcase_add_test(tc_core,
                 test_several_specifier);  // для нескольких спецификаторов
  tcase_add_test(tc_core, test_specifier_percent);  // для процента
  tcase_add_test(tc_core, test_suppress);           // для *
  tcase_add_test(tc_core, test_char);               // для %c
  tcase_add_test(tc_core, test_signed_decimal);     // для %d
  tcase_add_test(tc_core, test_signed_integer);     // для %i
  tcase_add_test(tc_core, test_float_scientific_lowercase);      // для %e
  tcase_add_test(tc_core, test_floatE_scientific_uppercase);     // для %E
  tcase_add_test(tc_core, test_float_decimal);                   // для %f
  tcase_add_test(tc_core, test_float_decimal_scientific);        // для %g
  tcase_add_test(tc_core, test_float_scientific_uppercase);      // для %G
  tcase_add_test(tc_core, test_unsigned_octal);                  // для %o
  tcase_add_test(tc_core, test_string);                          // для %s
  tcase_add_test(tc_core, test_unsigned_decimal);                // для %u
  tcase_add_test(tc_core, test_unsigned_hexadecimal_lowercase);  // для %x
  tcase_add_test(tc_core, test_unsigned_hexadecimal_uppercase);  // для %X
  tcase_add_test(tc_core, test_pointer);                         // для %p

  suite_add_tcase(s, tc_core);
  return s;
}
