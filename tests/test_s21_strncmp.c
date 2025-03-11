#include <check.h>

#include "../s21_string.h"

// Общая функция для сравнения результатов
#define test_strncmp(str1, str2, n) \
  ck_assert_int_eq(s21_strncmp(str1, str2, n), strncmp(str1, str2, n))

START_TEST(test_s21_strncmp) {
  // Тестовые строки
  char str1[10] = "Hello";
  const char *str2 = "Hello";
  char str3[10] = "Hello!";
  // const char *str4 = "Hella";
  char str5[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  const char *str6 = "ABCDEFGHIJKLMNO";

  // Простые тесты
  test_strncmp(str1, str2, 5);  // Полное совпадение
  test_strncmp(str1, str3, 5);  // Частичное совпадение
  // test_strncmp(str1, str4, 5);  // Различие в последнем символе

  // Сравнение строк с большими данными
  test_strncmp(str5, str6, 10);  // Сравнение первых 10 символов

  // Тесты с длиной строки
  test_strncmp(str1, str2, 3);  // Сравнение первых 3 символов
  // test_strncmp(str1, str3, 6);  // Полный текст с дополнительными символами

  // Специальные символы и границы
  test_strncmp("", str2, 3);  // Пустая строка
  test_strncmp(str1, "", 3);  // Пустая строка
}
END_TEST

Suite *s21_strncmp_suite(void) {
  Suite *s = suite_create("S21 Strncmp Test Suite");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_s21_strncmp);

  suite_add_tcase(s, tc);

  return s;
}
