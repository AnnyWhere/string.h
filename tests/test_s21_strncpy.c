#include <check.h>

#include "../s21_string.h"

// Общая функция для сравнения результатов
#define test_strncpy(dest, src, n) \
  ck_assert_str_eq(s21_strncpy(dest, src, n), strncpy(dest, src, n))

START_TEST(test_s21_strncpy) {
  // Тестовые строки
  char str1[20] = "Hello, ";
  const char *src1 = "World!";
  char str2[20] = "Test ";
  const char *src2 = "String";
  char str3[20] = "Sample ";
  const char *src3 = "Text";
  char str4[10] = "Full";
  const char *src4 = "Stop";
  // char str5[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  // const char *src5 = "12345";

  // Простые тесты
  test_strncpy(str1, src1, 6);  // Копирование первых 6 символов
  test_strncpy(str2, src2, 6);  // Копирование с полной строкой
  test_strncpy(str3, src3, 4);  // Копирование первых 4 символов
  test_strncpy(str4, src4,
               4);  // Копирование первых 4 символов из "Stop" в "Full"

  // Специальные символы и пределы
  test_strncpy(str2, "", 5);  // Пустая строка, ничего не изменится

  // Тест с большим набором данных
  char large_dest[50] = "This is a large destination string";
  const char *large_src = " with additional content.";
  test_strncpy(large_dest, large_src, 10);
}
END_TEST

Suite *s21_strncpy_suite(void) {
  Suite *s = suite_create("S21 Strncpy Test Suite");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_s21_strncpy);

  suite_add_tcase(s, tc);

  return s;
}
