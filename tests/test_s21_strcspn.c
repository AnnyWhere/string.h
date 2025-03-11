#include <check.h>

#include "../s21_string.h"

// Общая функция для сравнения результатов
#define test_strcspn(str, reject) \
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject))

START_TEST(test_s21_strcspn) {
  // Тестовые строки
  char str1[10] = "123456789";  // Обычная строка
  char str2[10] = "abcdef";     // Обычная строка
  char str3[10] = "abcxyz";     // Обычная строка
  char str4[2] = "";  // Пустая строка (учитываем место для NULL-терминатора)
  char str5[27] = "qwertyuiopasdfghjklzxcvbnm";  // Большая строка
  char str6[10] = "abc\0def";  // Строка с нулевым символом
  char str7[2] = "a";          // Строка из одного символа
  char str8[12] = "abracadabra";  // Строка с повторяющимися символами
  char str9[10] = "abcdefgh";  // Строка без символов из reject
  char large_str[1000] =
      "This is a large string to test the function with a very long input "
      "string.";               // Большая строка
  char very_large_str[10000];  // Очень длинная строка

  // Заполнение очень длинной строки
  memset(very_large_str, 'a', 9999);
  very_large_str[9999] = '\0';

  // Простые тесты
  test_strcspn(str1, "456");  // Найти первый символ из "456"
  test_strcspn(str2, "xyz");  // Найти первый символ из "xyz"
  test_strcspn(str3, "c");    // Найти первый символ 'c'

  // Тесты на пустые строки
  test_strcspn(str4, "a");
  test_strcspn(str5, "ae");

  // Тест с пустой строкой для reject
  test_strcspn(str1, "");

  // Тесты на нулевой символ в строке
  test_strcspn(str6, "d");

  // Тесты с единственным символом в строках
  test_strcspn(str7, "a");
  test_strcspn(str7, "b");

  // Тесты с повторяющимися символами в reject
  test_strcspn(str8, "abc");

  // Тесты, когда все символы строки не находятся в reject
  test_strcspn(str9, "xyz");

  // Тест на длинные строки
  test_strcspn(large_str, "t");  // Первый символ 't'

  // Очень длинная строка (10000 символов)
  test_strcspn(very_large_str, "b");

  // Проверка на строку, содержащую пробелы
  test_strcspn("hello world", " ");
  test_strcspn("line1\tline2", "\t");

  // Тест с пустым reject
  test_strcspn("abcdef", "");

  // Проверка на строку из одинаковых символов
  test_strcspn("aaaaaaaaaa", "a");
  test_strcspn(
      "aaaaaaaaaa",
      "b");  // Нет символов из reject, должна вернуть длину всей строки

  // Тест с символами нового строки и табуляции
  test_strcspn("hello\nworld", "\n");  // Найти символ новой строки
  test_strcspn("line1\tline2", "\t");  // Найти символ табуляции

  // Проверка на большие строки (10000+ символов)
  char large_str2[10000];
  memset(large_str2, 'x', 9999);
  large_str2[9999] = '\0';
  test_strcspn(large_str2, "y");  // Все символы одинаковые, не найдено
}
END_TEST

Suite *s21_strcspn_suite(void) {
  Suite *s = suite_create("S21 Strcspn Test Suite");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_s21_strcspn);

  suite_add_tcase(s, tc);

  return s;
}
