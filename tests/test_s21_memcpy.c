#include <check.h>

#include "../s21_string.h"

#define test_memcpy(dest, src, n) \
  ck_assert_mem_eq(s21_memcpy(dest, src, n), memcpy(dest, src, n), n)

START_TEST(test_s21_memcpy) {
  // Тесты строк
  const char *src1 = "Hello, World!";
  const char *src2 = "Test String";
  const char *src3 = "Sample Text";
  const char *src4 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  const char *src5 = "1234567890";
  const char *src6 = "Mississippi";
  const char *src7 = "";
  const char *src8 = "Test\0String";

  char dest1[100], dest2[100], dest3[100], dest4[100];
  char dest5[1000], dest6[100], dest7[100], dest8[100];

  // Простые тесты
  test_memcpy(dest1, src1, strlen(src1) + 1);
  test_memcpy(dest2, src2, strlen(src2) + 1);
  test_memcpy(dest3, src3, strlen(src3) + 1);
  test_memcpy(dest4, src4, strlen(src4) + 1);

  // Теест пустой строки
  test_memcpy(dest1, src7, 1);

  // Копирование в пустую строку
  test_memcpy(dest2, src8, strlen(src8) + 1);

  // Тест большой строки
  char large_data[1000];
  memset(large_data, 'A', sizeof(large_data));
  test_memcpy(dest5, large_data, sizeof(large_data));

  // Тест частичной копии данных
  test_memcpy(dest1, src5, 5);
  test_memcpy(dest2, src6, 5);

  // Тест символа null посередине строки
  test_memcpy(dest1, src8, strlen(src8) + 1);

  // Тест, что строки разной длины не объединяются
  test_memcpy(dest6, "Short", 5);
  test_memcpy(dest7, "LongerStringExample", 10);

  // Проверка корректности после копирования
  test_memcpy(dest8, src1, strlen(src1) + 1);
  ck_assert_str_eq(dest8, src1);
}
END_TEST

Suite *s21_memcpy_suite(void) {
  Suite *s = suite_create("S21 Memcpy Test Suite");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_s21_memcpy);

  suite_add_tcase(s, tc);

  return s;
}
