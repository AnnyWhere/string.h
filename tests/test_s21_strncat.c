#include <check.h>

#include "../s21_string.h"

// Общая функция для сравнения результатов
#define test_strncat(dest, src, n) \
  ck_assert_str_eq(s21_strncat(dest, src, n), strncat(dest, src, n))

START_TEST(test_s21_strncat) {
  // Тестовые строки
  char str1[20] = "Hello, ";
  const char *src1 = "World!";
  char str2[20] = "Test ";
  const char *src2 = "String";
  char str3[20] = "Sample ";
  const char *src3 = "Text";
  char str4[10] = "Full";
  const char *src4 = "Stop";
  char str5[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  const char *src5 = "12345";

  // Добавление завершающего нуля для str5
  str5[25] = '\0';

  // Простые тесты
  test_strncat(str1, src1, 6);  // Простой конкатенация
  test_strncat(str2, src2, 6);  // Конкатенация с полной строкой
  test_strncat(str3, src3, 4);  // Частичная конкатенация

  // Специальные символы и пределы
  test_strncat(str1, "", 0);
  test_strncat(str2, "", 5);

  // char temp_buffer[7];
  // test_strncat(temp_buffer, src1, 6);

  // Тест с большим набором данных
  char large_dest[50] = "This is a large destination string";
  const char *large_src = " with additional content.";
  test_strncat(large_dest, large_src, 10);

  // Проверка на неправильное поведение (без проверок на переполнение)
  test_strncat(str4, src4, 5);
  test_strncat(str5, src5, 5);
}
END_TEST

Suite *s21_strncat_suite(void) {
  Suite *s = suite_create("S21 Strncat Test Suite");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_s21_strncat);

  suite_add_tcase(s, tc);

  return s;
}
