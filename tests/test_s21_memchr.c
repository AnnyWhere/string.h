#include <check.h>

#include "../s21_string.h"

START_TEST(test_s21_memchr) {
// Общая функция для сравнения результатов
#define test_memchr(str, ch, len) \
  ck_assert_ptr_eq(s21_memchr(str, ch, len), memchr(str, ch, len))

  // Тестовые строки
  const char *str1 = "Hello, World!";
  const char *str2 = "Test String";
  const char *str3 = "Sample Text";
  const char *str4 = "";
  const char *str5 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  const char *str6 = "1234567890";
  const char *str7 = "Mississippi";

  // Простой набор тестов
  test_memchr(str1, 'o', strlen(str1));
  test_memchr(str2, 'g', strlen(str2));
  test_memchr(str3, 'z', strlen(str3));  // Символ отсутствует
  test_memchr(str4, 'a', strlen(str4));  // Пустая строка
  test_memchr(str5, 'A', strlen(str5));  // Поиск первого символа
  test_memchr(str6, '0', strlen(str6));  // Поиск последнего символа
  test_memchr(str7, 's', strlen(str7));  // Символ встречается несколько раз

  // Специальные символы и пределы
  test_memchr("Start with this", 'S', strlen("Start with this"));
  test_memchr("End of string", '\0',
              strlen("End of string") + 1);  // Тестируем символ конца строки
  test_memchr("No match here", 'x',
              strlen("No match here"));  // Символ не найден
  // Тест с большим набором данных
  test_memchr(
      "This is a very long string to test performance and coverage", 'e',
      strlen("This is a very long string to test performance and coverage"));
  // Проверка на пустое значение n
  test_memchr("Empty n", 'E', 0);  // Пустой поиск
  // Проверка с разными регистрами букв
  test_memchr("MixedCaseLetters", 'C', strlen("MixedCaseLetters"));
  // Проверка с цифрами
  test_memchr("Numbers 12345", '1', strlen("Numbers 12345"));
  // Поиск символа в середине строки
  test_memchr("abcdefghijklm", 'g', strlen("abcdefghijklm"));
  // Поиск символа, которого нет в строке
  test_memchr("abcdef", 'z', strlen("abcdef"));
  // Пустая строка, поиск первого символа
  test_memchr("", 'a', 1);
  // Проверка на большую строку
  test_memchr("The quick brown fox jumps over the lazy dog", 'o',
              strlen("The quick brown fox jumps over the lazy dog"));
  // Проверка с символом конца строки
  test_memchr("End of this string\0", '\0', strlen("End of this string\0"));
}
END_TEST

// Функция для создания Suite и добавления теста
Suite *s21_memchr_suite(void) {
  Suite *s = suite_create("S21 Memchr Test Suite");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_s21_memchr);

  suite_add_tcase(s, tc);

  return s;
}
