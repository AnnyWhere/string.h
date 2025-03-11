#include <check.h>

#include "../s21_string.h"

#define test_memset(dest, c, len)                    \
  do {                                               \
    void *result1 = s21_memset((dest), (c), (len));  \
    void *result2 = memset((dest), (c), (len));      \
    ck_assert_ptr_eq(result1, result2);              \
    if ((len) > 0) {                                 \
      ck_assert(memcmp((dest), (dest), (len)) == 0); \
    }                                                \
  } while (0)

START_TEST(test_s21_memset) {
  // Тестовые строки
  char str1[10] = "123456789";      // Массив размером 10
  char str2[10] = "123456789";      // Массив размером 10
  char str3[20] = "Hello, World!";  // Массив размером 20
  char str4[5] = "abcd";            // Массив размером 5
  char str5[10] = "abcdefghij";     // Массив размером 10

  // Простые тесты
  test_memset(str1, '1', 3);  // Заполнение первых 3 символов
  test_memset(str2, '0', 10);  // Заполнение всей строки
  test_memset(str3, 'x', 5);  // Заполнение первых 5 символов
  test_memset(str4, 'z', 2);  // Заполнение первых 2 символов

  // Специальные символы и пределы
  test_memset(str5, 'A', 0);   // Ничего не изменится
  test_memset(str5, 'Z', 10);  // Заполнение всей строки

  // Большой набор данных
  char large_str[100] = "This is a large string to test the function.";
  test_memset(large_str, '!', 50);  // Заполнение первых 50 символов

  // Пограничные случаи
  test_memset(str1, 'A', 0);

  // Тестирование с большим размером массива
  char big_str[20] = "Test buffer size";
  test_memset(big_str, 'B', 15);

  // Тестирование с различными типами данных
  int arr1[5] = {1, 2, 3, 4, 5};
  test_memset(arr1, 0, sizeof(arr1));

  // Тестирование с нестандартными значениями символов
  test_memset(str1, 0, 3);
  test_memset(str2, 127, 5);

  // Тестирование с пересекающимися границами
  char str6[11] = "abcdefghijk";
  test_memset(str6, 'X', 10);  // Заполнение почти всей строки

  // Тестирование с большими размерами данных
  char big_arr[1000];
  test_memset(big_arr, '0', 1000);

  // Тесты с частичным переполнением
  char str7[20] = "abcdefghijk";
  test_memset(str7, 'A', 15);
  test_memset(str7, 'B', 20);

  // Тесты на многократное применение memset
  char str8[10] = "abcdefghi";
  test_memset(str8, 'X', 3);
  test_memset(str8, 'Y', 10);
}
END_TEST

Suite *s21_memset_suite(void) {
  Suite *s = suite_create("S21 Memset Test Suite");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_s21_memset);

  suite_add_tcase(s, tc);

  return s;
}
