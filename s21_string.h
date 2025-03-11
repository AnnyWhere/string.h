#ifndef S21_STRING_H
#define S21_STRING_H

#include <ctype.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

// Макросы для определения выравнивания
#define ALIGNMENT_OF(type) \
  offsetof(                \
      struct {             \
        char c;            \
        type x;            \
      },                   \
      x)
#define IS_ALIGNED(ptr, align) (!((uintptr_t)(ptr) & ((align) - 1)))

#define S21_NULL 0

typedef unsigned long s21_size_t;

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *ptr1, const void *ptr2, size_t n);
void *s21_memcpy(void *dest, const void *src, size_t n);
char *s21_strchr(const char *s, int c);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
s21_size_t s21_strlen(const char *str);
char *s21_strerror(int errnum);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
char *s21_strcpy(char *dest, const char *src);
void *s21_insert(const char *src, const char *str, size_t start_index);
void *s21_to_lower(const char *str);
void *s21_to_upper(const char *str);
void *s21_trim(const char *src, const char *trim_chars);

// структура и функции s21_sscanf
typedef struct {
  char specifier;        // Спецификатор
  int width;             // Ширина поля
  bool suppress_assign;  // Флаг подавления присваивания (*)
  char length_modifier;  // Модификатор длины
  bool conversation;     // Флаг подсчета
  bool percent;          // Флаг процента
} FormatSpecifier;

FormatSpecifier parse_format(const char *format);
s21_size_t apply_width(const char *str, FormatSpecifier *specifier);
char *trim_string(const char *str, s21_size_t width);
bool is_integer_specifier(FormatSpecifier *specifier);
bool is_unsigned_specifier(FormatSpecifier *specifier);
int parse_integer(const char *str, FormatSpecifier *specifier, void *result,
                  bool signed_type);
long long parse_integer_value(const char *str, FormatSpecifier *specifier,
                              bool signed_type, char **end);
long long parse_unsigned_value(const char *str, FormatSpecifier *specifier,
                               char **end);
long long parse_number_with_prefix(const char *str, bool signed_type,
                                   char **end, FormatSpecifier *specifier);
long long parse_octal_value(const char *str, bool signed_type, char **end,
                            FormatSpecifier *specifier);
long long parse_hex_value(const char *str, bool signed_type, char **end,
                          FormatSpecifier *specifier);
long long parse_decimal_value(const char *str, bool signed_type, char **end,
                              FormatSpecifier *specifier);
int is_hex_digit(char c);
int is_octal_digit(char c);
void apply_length_modifier(FormatSpecifier *specifier, void *result,
                           long long value, bool signed_type);
int parse_float(const char *str, FormatSpecifier *specifier, void *result);
bool is_blank(const char *str);
int parse_string(const char *str, FormatSpecifier *specifier, void *result);
int parse_pointer(const char *str, FormatSpecifier *specifier, void **result);
int parse_char(const char *str, FormatSpecifier *specifier, void *result);
int handle_specifier(const char **current_str, va_list *args,
                     FormatSpecifier specifier);
int process_characters(const char **current_str, const char **current_format,
                       int *chars_parsed);

int s21_sscanf(const char *str, const char *format, ...);

// структура и функции s21_printf
int s21_sprintf(char *str, const char *format, ...);

struct format_info {  // Структура для получении и хранении информации
  int minus;          // о формате
  int plus;
  int space;
  int precision;        // есть ли точность
  int precision_value;  // какое значение у точности
  char length;          // хранит длину (h, l, w(ll), L) или 0
  int hash;
  int uppercase;  // для e/E g/G x/X
  int zero;       // флаг 0
  int width;
  int error;
};
void s21_parse_flags(const char **p, struct format_info *specs);
int s21_parse_width(const char **p, va_list *args, struct format_info *specs);
void s21_parse_precision(const char **p, va_list *args,
                         struct format_info *specs);
void s21_parse_length(const char **p, struct format_info *specs);
void s21_process_c(char **output, va_list *args, struct format_info *specs,
                   int width);
void s21_process_string(char **output, va_list *args, struct format_info *specs,
                        int width);
void s21_process_number_format(char **output, va_list *args,
                               struct format_info *specs, char specifier,
                               int width);
void s21_append_char(char **dest, char c);
void s21_append_str(char **dest, const char *src);
void s21_int_to_str(long long int value, char *buffer);
void s21_unsigned_to_str(unsigned long long value, char *buffer);
void s21_float_to_str(double value, char *buffer, int precision);
int s21_handle_special_values_and_zero_float(double value, char *buffer);
void handle_whole_and_fraction(double value, char *buffer, int precision,
                               int is_negative);
void handle_fraction(double fraction, char *buffer, int start_index,
                     int precision);
void s21_apply_width_and_minus(char **output, const char *value, int width,
                               int minus, int zero, struct format_info *specs);
void s21_apply_plus_and_space(char **output, double value, int plus_flag,
                              int space_flag);
int s21_str_length(const char *str);
void s21_str_copy(char *dest, const char *src);
void s21_apply_precision(char *buffer, struct format_info *specs, char type);
void s21_exponent_to_str(int exponent, char *buffer, int is_uppercase);
void s21_float_to_sci(long double value, char *buffer, int precision,
                      int is_uppercase);
void s21_process_e(char **output, va_list *args, struct format_info *specs,
                   int width, char specifier);
void s21_process_g(char **output, va_list *args, struct format_info *specs,
                   int width, char specifier);
void s21_process_x(char **output, va_list *args, struct format_info *specs,
                   int width, char specifier);
void s21_int_to_hex(unsigned long long value, char *buffer, int is_uppercase);
void s21_int_to_oxto(unsigned long long value, char *buffer);
void s21_process_o(char **output, va_list *args, struct format_info *specs,
                   int width);
void s21_process_p(char **output, va_list *args, struct format_info *specs,
                   int width);
int char_to_str(char *buffer, wchar_t wc, int is_wide);
void s21_process_wchar(char **output, va_list *args, struct format_info *specs,
                       int width);
void s21_process_leading_zeros(char **output, const char *buffer, int width,
                               int is_negative);
void s21_apply_precision_x(char *buffer, int precision);
void s21_format_with_padding(char **output, const char *prefix,
                             const char *buffer, int padding, int width,
                             struct format_info *specs,
                             unsigned long long value);
unsigned long long s21_extract_unsigned_value(va_list *args,
                                              struct format_info *specs);
void s21_handle_zero_value(char *buffer, unsigned long long value,
                           struct format_info *specs, char **output, int width);
int s21_calculate_exponent(double *abs_value);
void s21_round_significant_digits(double *value, int precision, int exp);
void s21_remove_trailing_zeros(char *buffer);
void s21_format_and_apply_flags(char **output, char *buffer, double value,
                                int width, struct format_info *specs);
void s21_handle_special_values_exp(char *buffer, double value,
                                   struct format_info *specs, char **output,
                                   int width);

#endif