#include "../src/s21_string.h"

// Парсинг спецификаторов и модификаторов
FormatSpecifier parse_format(const char *format) {
  FormatSpecifier spec = {0};

  // Пропускаем начальный символ '%'
  format++;

  // Проверка на наличие '*'
  if (*format == '*') {
    spec.suppress_assign = true;
    format++;
  }

  // Чтение ширины (целое число)
  while (isdigit(*format)) {
    spec.width = spec.width * 10 + (*format - '0');
    format++;
  }

  // Чтение модификатора длины
  if (*format == 'h' || *format == 'l' || *format == 'L') {
    spec.length_modifier = *format;
    format++;
    // Проверка на повтор модификатора
    if (*format == spec.length_modifier) {
      printf("Данный формат в рамках текущей реализации не поддерживается");
      printf("\n");
      spec.length_modifier = '\0';
      format++;
    }
  }

  // Обработка двух символов '%'
  if (*format == '%' && *(format + 1) == '%') {
    spec.percent = true;
    format += 2;
  } else {
    // Чтение спецификатора
    spec.specifier = *format;
    format++;
  }

  return spec;
}

// Функция для обработки ширины
s21_size_t apply_width(const char *str, FormatSpecifier *specifier) {
  s21_size_t max_length = s21_strlen(str);
  if (specifier->width > 0 && specifier->width < (int)max_length) {
    max_length = specifier->width;
  }
  return max_length;
}

// Функция для обрезки строки по заданной ширине
char *trim_string(const char *str, s21_size_t width) {
  char *str_trimmed = (char *)malloc(width + 1);
  bool success = true;

  if (str_trimmed == S21_NULL) {
    success = false;
  } else {
    s21_strncpy(str_trimmed, str, width);
    str_trimmed[width] = '\0';
  }

  return success ? str_trimmed : S21_NULL;
}

// Функция подтвердения, что спецификатор знаковый
bool is_integer_specifier(FormatSpecifier *specifier) {
  return specifier->specifier == 'd' || specifier->specifier == 'i';
}

// Функция подтверждения, что спецификатор беззнаковый
bool is_unsigned_specifier(FormatSpecifier *specifier) {
  return specifier->specifier == 'o' || specifier->specifier == 'u' ||
         specifier->specifier == 'x' || specifier->specifier == 'X';
}

// Обработка спецификаторов целых чисел (главная)
int parse_integer(const char *str, FormatSpecifier *specifier, void *result,
                  bool signed_type) {
  char *end = S21_NULL;
  long long value = 0;
  int flag = 0;

  // Проверяем входные данные
  if (str == S21_NULL || result == S21_NULL) {
    return -1;
  }

  while (*str == ' ') {
    str++;
  }

  // Задаем ширину
  s21_size_t width = apply_width(str, specifier);

  char *str_trimmed = trim_string(str, width);

  if (str_trimmed == S21_NULL) {
    flag = -1;
  }

  char *start_of_str_trimmed = str_trimmed;

  // Обработка чисел
  if (is_integer_specifier(specifier)) {
    value = parse_integer_value(str_trimmed, specifier, signed_type, &end);
  } else if (is_unsigned_specifier(specifier)) {
    value = parse_unsigned_value(str_trimmed, specifier, &end);
  } else {
    free(str_trimmed);
    flag = 0;
  }

  // Модификатор длины
  apply_length_modifier(specifier, result, value, signed_type);

  int result_length;

  result_length = (int)(end - start_of_str_trimmed);

  free(str_trimmed);

  return (flag == 0) ? result_length : -1;
}

// Основная функция обработки знаковых спецификаторов (i, d)
long long parse_integer_value(const char *str, FormatSpecifier *specifier,
                              bool signed_type, char **end) {
  long long result;

  if (specifier->specifier == 'i') {
    result = parse_number_with_prefix(str, signed_type, end, specifier);
  } else {  // Спецификатор d
    result = parse_decimal_value(str, signed_type, end, specifier);
  }

  return result;
}

// Функция парсинга без знака
long long parse_unsigned_value(const char *str, FormatSpecifier *specifier,
                               char **end) {
  long long value = 0;
  bool signed_type = is_integer_specifier(specifier);

  if (specifier->specifier == 'x' || specifier->specifier == 'X') {
    if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) {
      value = parse_hex_value(str + 2, signed_type, end, specifier);
    } else if (is_hex_digit(*str)) {
      value = parse_hex_value(str, signed_type, end, specifier);
    } else if (*str == '0' && (!is_hex_digit(*str + 1))) {
      specifier->conversation = true;
      value = 0;
    } else if ((!is_hex_digit(*str))) {
      specifier->conversation = true;
      value = 0;
    }
  } else if (specifier->specifier == 'o') {
    value = parse_octal_value(str, signed_type, end, specifier);
  } else {  // спецификатор u
    value = parse_decimal_value(str, signed_type, end, specifier);
  }

  return value;
}

// Парсинг числа с учетом префикса
long long parse_number_with_prefix(const char *str, bool signed_type,
                                   char **end, FormatSpecifier *specifier) {
  // Проверка на знак
  bool negative = false;
  if (str[0] == '-') {
    negative = true;
    str++;
  } else if (str[0] == '+') {
    str++;
  }

  long long value = 0;

  if (str[0] == '0') {
    if (str[1] == 'x' || str[1] == 'X') {
      value = parse_hex_value(str + 2, signed_type, end, specifier);
    } else {
      value = parse_octal_value(str, signed_type, end, specifier);
    }
  } else {
    value = parse_decimal_value(str, signed_type, end, specifier);
  }

  if (negative) {
    value = -value;
  }

  return value;
}

// Парсинг восьмеричного числа
long long parse_octal_value(const char *str, bool signed_type, char **end,
                            FormatSpecifier *specifier) {
  const char *ptr = str;
  long long result = 0;
  bool valid_octal = true;

  for (; *ptr != '\0'; ++ptr) {
    if (!is_octal_digit(*ptr)) {
      valid_octal = false;
      break;
    }
  }

  if (!valid_octal && ptr == str) {
    *end = (char *)str;
    result = 0;
    specifier->conversation = true;
  } else if (valid_octal || ptr != str) {
    *end = (char *)ptr;

    if (signed_type) {
      result = strtol(str, end, 8);
    } else {
      result = (long long)strtoul(str, end, 8);
    }
  }

  return result;
}

// Парсинг шестнадцатеричного числа
long long parse_hex_value(const char *str, bool signed_type, char **end,
                          FormatSpecifier *specifier) {
  const char *ptr = str;
  long long result = 0;
  bool valid_hex = true;

  for (; *ptr != '\0'; ++ptr) {
    if (!is_hex_digit(*ptr)) {
      valid_hex = false;
      break;
    }
  }

  if (valid_hex || ptr != str + 2) {
    *end = (char *)ptr;

    if (signed_type) {
      result = strtol(str, end, 16);
    } else {
      result = (long long)strtoul(str, end, 16);
    }
  } else {
    *end = (char *)str;
    result = 0;
    specifier->conversation = true;
  }

  return result;
}

// Парсинг десятичного числа
long long parse_decimal_value(const char *str, bool signed_type, char **end,
                              FormatSpecifier *specifier) {
  const char *ptr = str;
  long long result = 0;

  if (*ptr == '+' || *ptr == '-') {
    ptr++;
  }

  if (*ptr == '\0' || !isdigit(*ptr)) {
    *end = (char *)str;
    result = 0;
    specifier->conversation = true;
  }

  if (signed_type) {
    result = strtol(str, end, 10);
  } else {
    result = (long long)strtoul(str, end, 10);
  }

  return result;
}

// Функция для проверки, что символ является допустимым для шестнадцатеричного
// числа
int is_hex_digit(char c) {
  return (isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}

// Функция для проверки, что символ является допустимым для восьмеричного числа
int is_octal_digit(char c) { return (c >= '0' && c <= '7'); }

// Функция для применения модификаторов длины
void apply_length_modifier(FormatSpecifier *specifier, void *result,
                           long long value, bool signed_type) {
  if (specifier->length_modifier == 'h') {
    if (signed_type) {
      // Для signed short int: диапазон от -32768 до 32767
      if (value > SHRT_MAX) {
        *(short *)result = (short)(value - (USHRT_MAX + 1));
      } else if (value < SHRT_MIN) {
        *(short *)result = (short)(value + (USHRT_MAX + 1));
      } else {
        *(short *)result = (short)value;
      }
    } else {
      // Для unsigned short int: диапазон от 0 до 65535
      if (value > USHRT_MAX) {
        *(unsigned short *)result = (unsigned short)(value % (USHRT_MAX + 1));
      } else {
        *(unsigned short *)result = (unsigned short)value;
      }
    }
  } else if (specifier->length_modifier == 'l') {
    if (signed_type) {
      // Для signed long int: диапазон для 64-битных систем от
      // -9223372036854775808 до 9223372036854775807
      if (value > LONG_MAX) {
        *(long *)result = LONG_MAX;
      } else if (value < LONG_MIN) {
        *(long *)result = LONG_MIN;
      } else {
        *(long *)result = (long)value;
      }
    } else {
      // Для unsigned long int: диапазон от 0 до 18446744073709551615
      if ((unsigned long)value > ULONG_MAX) {
        *(unsigned long *)result = ULONG_MAX;
      } else {
        *(unsigned long *)result = (unsigned long)value;
      }
    }
  } else {
    *(long long *)result = value;
  }
}

// Функция обработки спецификаторов вещественных чисел
int parse_float(const char *str, FormatSpecifier *specifier, void *result) {
  int consumed_chars = -1;

  if (str != S21_NULL && result != S21_NULL) {
    // Пропускаем пробелы в начале строки
    while (*str == ' ') {
      str++;
    }

    // Проверяем, начинается ли строка с допустимых символов
    if (*str == '+' || *str == '-' || *str == '.' || isdigit(*str)) {
      s21_size_t max_length = apply_width(str, specifier);

      char temp[max_length + 1];
      s21_strncpy(temp, str, max_length);
      temp[max_length] = '\0';

      char *end = S21_NULL;
      if (specifier->length_modifier == 'L') {
        long double long_value = strtold(temp, &end);
        *(long double *)result = long_value;
      } else {
        double value = strtod(temp, &end);
        *(float *)result = value;
      }

      // Если ок, вычисляем количество потребленных символов
      if (end != temp) {
        consumed_chars = (int)(end - temp);
      } else {
        consumed_chars = 0;
      }
    } else {
      consumed_chars = 0;
    }
  }

  return consumed_chars;
}

// Проверка на пробелы
bool is_blank(const char *str) {
  bool flag = true;
  while (*str != '\0') {
    if (!isspace((unsigned char)*str)) {
      flag = false;
    }
    str++;
  }
  return flag;
}

// Функция работы спецификатора строки
int parse_string(const char *str, FormatSpecifier *specifier, void *result) {
  int flag = 0;

  if (str == S21_NULL || result == S21_NULL) {
    return -1;
  }

  while (*str == ' ') {
    str++;
  }

  s21_size_t max_length = apply_width(str, specifier);

  s21_size_t i = 0;

  if (specifier->length_modifier == 'l') {
    wchar_t *wstr = (wchar_t *)result;
    while (str[i] != '\0' && !isspace((unsigned char)str[i]) &&
           i < max_length) {
      wstr[i] = (wchar_t)(str[i]);
      i++;
    }
    wstr[i] = L'\0';
  } else {
    char *cstr = (char *)result;
    while (str[i] != '\0' && !isspace((unsigned char)str[i]) &&
           i < max_length) {
      cstr[i] = str[i];
      i++;
    }
    cstr[i] = '\0';
  }

  return (flag == 0) ? (int)i : -1;
}

// Функция обработки спецификатора указателя
int parse_pointer(const char *str, FormatSpecifier *specifier, void **result) {
  (void)specifier;

  if (str == S21_NULL || result == S21_NULL) {
    return -1;
  }

  while (*str == ' ') {
    str++;
  }

  s21_size_t max_length = apply_width(str, specifier);

  if (max_length < 2 || str[0] != '0' || (str[1] != 'x' && str[1] != 'X')) {
    return 0;
  }

  str += 2;
  max_length -= 2;

  // Ограничиваем строку для дальнейшей обработки
  char temp[max_length + 1];
  s21_strncpy(temp, str, max_length);
  temp[max_length] = '\0';

  char *endptr = S21_NULL;
  uintptr_t ptr_value = strtoull(temp, &endptr, 16);

  int result_code = 0;

  // Проверяем, если ничего не распознано
  if (endptr == temp) {
    result_code = 1;
  } else if (*endptr != '\0' && !isspace((unsigned char)*endptr)) {
    result_code = 2;
  } else {
    *result = (void *)ptr_value;
  }

  return (result_code == 0) ? (int)(endptr - temp + 2) : 0;
}

// Функция обработки спецификатора символа
int parse_char(const char *str, FormatSpecifier *specifier, void *result) {
  int flag = 1;

  if (str == S21_NULL || result == S21_NULL) {
    return -1;
  }

  if (specifier->width > 0 && specifier->length_modifier == 'l') {
    *(wchar_t *)result = (wchar_t)(*str);
  } else if (specifier->length_modifier == 'l') {
    *(wchar_t *)result = (wchar_t)(*str);
  } else if (specifier->width > 0) {
    *(char *)result = *str;
  } else {
    *(char *)result = *str;
  }

  return flag;
}

// Обработка спецификаторов
int handle_specifier(const char **current_str, va_list *args,
                     FormatSpecifier specifier) {
  int num_conversions = 0;

  if (specifier.specifier == 'e' || specifier.specifier == 'E' ||
      specifier.specifier == 'f' || specifier.specifier == 'g' ||
      specifier.specifier == 'G') {
    void *float_ptr =
        specifier.suppress_assign ? S21_NULL : va_arg(*args, void *);
    int bytes_read = parse_float(*current_str, &specifier, float_ptr);
    if (bytes_read > 0 && !specifier.conversation) {
      *current_str += bytes_read;
      num_conversions++;
    }
  } else if (specifier.specifier == 'd' || specifier.specifier == 'i') {
    int *int_ptr = specifier.suppress_assign ? S21_NULL : va_arg(*args, int *);
    int bytes_read = parse_integer(*current_str, &specifier, int_ptr, true);
    if (bytes_read > 0 && !specifier.conversation) {
      *current_str += bytes_read;
      num_conversions++;
    }
  } else if (specifier.specifier == 's') {
    void *string_ptr =
        specifier.suppress_assign ? S21_NULL : va_arg(*args, void *);
    int bytes_read = parse_string(*current_str, &specifier, string_ptr);
    if (bytes_read > 0) {
      *current_str += bytes_read;
      num_conversions++;
    }
  } else if (specifier.specifier == 'c') {
    char *char_ptr =
        specifier.suppress_assign ? S21_NULL : va_arg(*args, char *);
    int bytes_read = parse_char(*current_str, &specifier, char_ptr);
    if (bytes_read > 0) {
      *current_str += bytes_read;
      num_conversions++;
    }
  } else if (specifier.specifier == 'o' || specifier.specifier == 'u' ||
             specifier.specifier == 'x' || specifier.specifier == 'X') {
    unsigned int *unsigned_int_ptr =
        specifier.suppress_assign ? S21_NULL : va_arg(*args, unsigned int *);
    int bytes_read =
        parse_integer(*current_str, &specifier, unsigned_int_ptr, false);
    if (bytes_read > 0 && !specifier.conversation) {
      *current_str += bytes_read;
      num_conversions++;
    }
  } else if (specifier.specifier == 'p') {
    void **pointer_ptr =
        specifier.suppress_assign ? S21_NULL : va_arg(*args, void **);
    int bytes_read = parse_pointer(*current_str, &specifier, pointer_ptr);
    if (bytes_read > 0) {
      *current_str += bytes_read;
      num_conversions++;
    }
  }

  return num_conversions;
}

// Обработка текущих символов строки и формата, проверка на пробелы
int process_characters(const char **current_str, const char **current_format,
                       int *chars_parsed) {
  int flag = 0;

  if (**current_str == **current_format) {
    (*current_str)++;
    (*current_format)++;
    (*chars_parsed)++;
    flag = 1;
  } else if (isspace(**current_format)) {
    while (isspace(**current_str)) {
      (*current_str)++;
      (*chars_parsed)++;
    }
    flag = 1;
  } else {
    flag = 0;
  }

  return flag;
}

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  int num_conversions = 0;
  const char *current_format = format;
  const char *current_str = str;
  int chars_parsed = 0;

  if (*current_str == '\0' || is_blank(current_str)) {
    va_end(args);
    return -1;
  }

  while (*current_format != '\0') {
    if (*current_format == '%') {
      FormatSpecifier specifier = parse_format(current_format);

      if (specifier.percent && *current_str == '%') {
        current_str++;
      }

      if (specifier.specifier == 'n') {
        int *n_ptr = va_arg(args, int *);
        *n_ptr = current_str - str;
        current_format++;
      }

      num_conversions += handle_specifier(&current_str, &args, specifier);

      current_format += (specifier.specifier == '%' ? 2 : 1);

      if ((*current_format == '%') || *(current_format + 1) == '%') {
        current_format++;
        continue;
      }

    } else {
      if (!process_characters(&current_str, &current_format, &chars_parsed)) {
        break;
      }
    }
  }

  va_end(args);
  return num_conversions;
}
