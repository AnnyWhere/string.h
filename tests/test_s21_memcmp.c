#include <check.h>
#include <string.h>

#include "../s21_string.h"

void assert_memcmp(const char *s1, const char *s2, size_t n) {
  int result_s21 = s21_memcmp(s1, s2, n);
  int result_std = memcmp(s1, s2, n);

  ck_assert((result_s21 > 0 && result_std > 0) ||
            (result_s21 < 0 && result_std < 0) ||
            (result_s21 == 0 && result_std == 0));
}

START_TEST(test_s21_memcmp) {
  const char *str1 = "Hello, World!";
  const char *str2 = "Hello, World!";
  const char *str3 = "Hello, Worle!";
  const char *str4 = "Different String";
  const char *str5 = "Short";
  const char *str6 = "";
  const char *str7 = "12345";
  const char *str8 = "54321";

  // Проверка одинаковых строк
  assert_memcmp(str1, str2, strlen(str1));

  // Проверка разных строк
  assert_memcmp(str1, str3, strlen(str1));

  // Проверка первых символов
  assert_memcmp(str1, str4, 5);

  // Пустая строка
  assert_memcmp(str5, str6, strlen(str5));

  // Один символ
  assert_memcmp(str6, str6, 1);

  // Разные длины строк
  assert_memcmp("abc", "abcdef", 3);
  char arr1[] = "abcdef";
  char arr2[] = "abc";
  assert_memcmp(arr1, arr2, strlen(arr2));

  // Тесты на сравнение с различными данными
  assert_memcmp("ABC", "abc", 3);
  assert_memcmp("12345", "12344", 5);
  assert_memcmp("longstringtest", "longstringteSt", 15);

  // Граничные случаи
  assert_memcmp(str1, str4, 1);
  assert_memcmp(str7, str8, 5);  // Разные строки
  assert_memcmp("abc", "abc", 0);  // Сравнение с нулевой длиной
  assert_memcmp("a", "b", 1);  // Тест на символы
  assert_memcmp("123456789", "1234567890", 9);  // Сравнение с длинной строкой
  assert_memcmp("abcdefgh", "abcdefghi",
                8);  // Сравнение с одной дополнительной буквой
  assert_memcmp("test", "test", 5);  // Сравнение с выходом за пределы строки

  // Большие строки
  char big_str1[10000];
  char big_str2[10000];
  memset(big_str1, 'a', sizeof(big_str1));
  memset(big_str2, 'a', sizeof(big_str2));
  big_str1[9999] = '\0';
  big_str2[9999] = '\0';
  assert_memcmp(big_str1, big_str2, 10000);
}
END_TEST

Suite *s21_memcmp_suite() {
  Suite *s = suite_create("S21 Memcmp Test Suite");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_s21_memcmp);
  suite_add_tcase(s, tc);

  return s;
}