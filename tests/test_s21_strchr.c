#include <check.h>

#include "../s21_string.h"

// Общая функция для сравнения результатов
START_TEST(test_s21_strchr) {
#define test_strchr(str, ch) \
  ck_assert_ptr_eq(s21_strchr(str, (int)(ch)), strchr(str, (int)(ch)))

  // Тестовые строки
  const char *str1 = "Hello, World!";
  const char *str2 = "Test String";
  const char *str3 = "Sample Text";
  const char *str4 = "";
  const char *str5 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  const char *str6 = "1234567890";
  const char *str7 = "Mississippi";

  // Простой набор тестов
  test_strchr(str1, 'o');  // Простой поиск
  test_strchr(str2, 'g');  // Символ в конце строки
  test_strchr(str3, 'z');  // Символ отсутствует
  test_strchr(str4, 'a');  // Пустая строка
  test_strchr(str5, 'A');  // Поиск первого символа
  test_strchr(str6, '0');  // Поиск последнего символа
  test_strchr(str7, 's');  // Символ встречается несколько раз

  // Специальные символы и пределы
  test_strchr("Start with this", 'S');  // Верхний регистр
  test_strchr("End of string", '\0');  // Тестируем символ конца строки
  test_strchr("No match here", 'x');  // Символ не найден

  // Тест с большим набором данных
  test_strchr("This is a very long string to test performance and coverage",
              'e');

  // Проверка с разными регистрами букв
  test_strchr("MixedCaseLetters", 'C');
  test_strchr("MixedCaseLetters", 'c');

  // Проверка с цифрами
  test_strchr("Numbers 12345", '1');

  // Дополнительные тесты для улучшения покрытия
  test_strchr("abcdefghijklm", 'g');  // Символ в середине строки
  test_strchr("abcdef", 'z');         // Символ отсутствует
  test_strchr("", 'a');               // Пустая строка
  test_strchr("The quick brown fox jumps over the lazy dog", 'o');
  test_strchr("End of this string\0", '\0');  // Символ конца строки
}
END_TEST

Suite *s21_strchr_suite(void) {
  Suite *s = suite_create("S21 Strchr Test Suite");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_s21_strchr);

  suite_add_tcase(s, tc);

  return s;
}