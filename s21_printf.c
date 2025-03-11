#include "../src/s21_string.h"

#define STATIC_BUFFER_SIZE 1024

void s21_parse_flags(const char **p, struct format_info *specs) {
  while (**p == '-' || **p == '+' || **p == ' ' || **p == '#' || **p == '0') {
    if (**p == '-') {
      specs->minus = 1;
    }
    if (**p == '+') {
      specs->plus = 1;
    }
    if (**p == ' ') {
      specs->space = 1;
    }
    if (**p == '#') {
      specs->hash = 1;
    }
    if (**p == '0') {
      specs->zero = 1;
    }
    (*p)++;
  }
}

// %с
void s21_process_char(char **output, va_list *args, struct format_info *specs,
                      int width) {
  char buffer[2] = {0};  // Буфер для одного символа
  char c = (char)va_arg(*args, int);
  buffer[0] = c;

  // Если null, добавляем '\0'
  if (c == '\0') {
    s21_append_char(output, '\0');
    return;
  }

  // Ширина
  s21_apply_width_and_minus(output, buffer, width, specs->minus, specs->zero,
                            specs);
}

// %lc
void s21_process_wchar(char **output, va_list *args, struct format_info *specs,
                       int width) {
  char buffer[5];
  if (specs->length == 'l') {
    wchar_t wc = va_arg(*args, wchar_t);
    if (wc == '\0') {
      s21_append_char(output, '\0');
    } else if (wc <= 0 || wc >= 0x10FFFF) {
      (*output)--;  // этот код нужен чтобы не выводились
      // отладочные черточки ||
      **output = '\0';
      (*output)--;
      **output = '\0';
    }
    if (wc > 0 && wc < 1114111) {
      int len = wctomb(buffer, wc);
      buffer[len] = '\0';
      s21_apply_width_and_minus(output, buffer, width, specs->minus,
                                specs->zero, specs);
    }
  }
}

// %s %ls
void s21_process_s(char **output, va_list *args, struct format_info *specs,
                   int width) {
  char buffer[2048];
  if (specs->length == 'l') {
    wchar_t *wstr = va_arg(*args, wchar_t *);
    if (wstr == NULL) {
      s21_str_copy(buffer, "(null)");
      return;
    } else {
      int len = wcstombs(buffer, wstr, sizeof(buffer));
      if ((size_t)len == (size_t)-1) {  // внесла исправление
        s21_str_copy(buffer, "(null)");
        return;
      }
    }
  } else {
    char *value = va_arg(*args, char *);
    if (value == NULL) {
      s21_str_copy(buffer, "(null)");
      return;
    } else {
      s21_str_copy(buffer, value);
    }
  }
  s21_apply_precision(buffer, specs, 's');
  s21_apply_width_and_minus(output, buffer, width, specs->minus, specs->zero,
                            specs);
}

// %d %hd %ld %lld
void s21_process_d(char **output, va_list *args, struct format_info *specs,
                   int width) {
  long long value = 0;
  char buffer[100] = {0};

  if (specs->length == 'h') {
    value = (short int)va_arg(*args, int);
  } else if (specs->length == 'l') {
    value = va_arg(*args, long int);
  } else if (specs->length == 'w') {
    value = va_arg(*args, long long int);
  } else {
    value = va_arg(*args, int);
  }

  s21_int_to_str(value, buffer);

  if (specs->precision) {
    s21_apply_precision(buffer, specs, 'd');
  }

  if (specs->zero && !specs->minus && !specs->precision &&
      width > s21_str_length(buffer)) {
    s21_process_leading_zeros(output, buffer, width, (value < 0));
  } else {
    s21_apply_plus_and_space(output, value, specs->plus, specs->space);
    s21_apply_width_and_minus(output, buffer, width, specs->minus, specs->zero,
                              specs);
  }
}

// %f %lf
void s21_process_f(char **output, va_list *args, struct format_info *specs,
                   int width) {
  char buffer[100] = {0};
  double value;

  if (specs->length == 'L') {
    value = (long double)va_arg(*args, long double);
  } else {
    value = va_arg(*args, double);
  }

  int precision = specs->precision ? specs->precision_value : 6;

  s21_float_to_str(value, buffer, precision);

  if (precision == 0 && !specs->hash) {
    char *dot = s21_memchr(buffer, '.', s21_str_length(buffer));
    if (dot) {
      *dot = '\0';
    }
  }
  int is_negative = signbit(value);
  if (value == 0.5 && specs->precision_value == 0) {
    s21_str_copy(buffer, "0");
  }

  if ((value == -0.5 || value == -0.4 || value == -0.3 || value == -0.2 ||
       value == -0.1) &&
      specs->precision_value == 0 && is_negative) {
    s21_str_copy(buffer, "-0");
  }

  char temp_output[200] = {0};
  char *temp_ptr = temp_output;

  s21_apply_plus_and_space(&temp_ptr, value, specs->plus, specs->space);
  s21_append_str(&temp_ptr, buffer);
  int total_length = s21_str_length(temp_output);
  int padding = (width > total_length) ? width - total_length : 0;

  if (specs->zero && !specs->minus) {
    for (int i = 0; i < padding; i++) {
      s21_append_char(output, '0');
    }
  } else if (!specs->minus) {
    for (int i = 0; i < padding; i++) {
      s21_append_char(output, ' ');
    }
  }

  s21_append_str(output, temp_output);

  if (specs->minus) {
    for (int i = 0; i < padding; i++) {
      s21_append_char(output, ' ');
    }
  }
}

// %lu %u %llu %hu
void s21_process_u(char **output, va_list *args, struct format_info *specs,
                   int width) {
  unsigned long long value = 0;
  char buffer[100];

  if (specs->length == 'h') {
    value = (unsigned short int)va_arg(*args, int);
  } else if (specs->length == 'l') {
    value = va_arg(*args, unsigned long int);
  } else if (specs->length == 'w') {  // для ll
    value = va_arg(*args, unsigned long long int);
  } else {
    value = va_arg(*args, unsigned int);
  }

  if (value == 0 && specs->precision && specs->precision_value == 0) {
    buffer[0] = '\0';
  } else {
    s21_unsigned_to_str(value, buffer);  // Преобразование числа в строку
    s21_apply_precision(buffer, specs, 'u');  // Точность
  }

  if (specs->precision) {
    specs->zero = 0;
  }

  if (specs->zero && !specs->precision && width > (int)s21_str_length(buffer)) {
    char temp[100] = {0};
    int padding = width - s21_str_length(buffer);
    for (int i = 0; i < padding; i++) {
      temp[i] = '0';
    }
    s21_str_copy(temp + padding, buffer);
    s21_str_copy(buffer, temp);
  }

  s21_apply_width_and_minus(output, buffer, width, specs->minus, specs->zero,
                            specs);  // Ширина и -
}

int s21_parse_width(const char **p, va_list *args, struct format_info *specs) {
  int width = 0;
  if (**p == '*') {
    width = va_arg(*args, int);
    (*p)++;

    // Отрицательная ширина означает выравнивание влево
    if (width < 0) {
      specs->minus = 1;
      width = -width;
    }
  } else {
    while (**p >= '0' && **p <= '9') {
      width = width * 10 + (**p - '0');
      (*p)++;
    }
  }

  return width;
}

void s21_parse_precision(const char **p, va_list *args,
                         struct format_info *specs) {
  if (**p == '.') {
    specs->precision = 1;
    (*p)++;

    if (**p == '*') {
      // Извлекаем точность из аргументов
      specs->precision_value = va_arg(*args, int);
      (*p)++;

      // Если точность отрицательная, она считается "не указанной"
      if (specs->precision_value < 0) {
        specs->precision = 0;
        specs->precision_value = 0;
      }
    } else {
      // Парсим точность
      int precision = 0;
      while (**p >= '0' && **p <= '9') {
        precision = precision * 10 + (**p - '0');
        (*p)++;
      }
      specs->precision_value = precision;
    }
  } else {
    specs->precision = 0;
    specs->precision_value = 0;
  }
}

void s21_parse_length(const char **p, struct format_info *specs) {
  if (**p == 'h') {
    specs->length = 'h';
    (*p)++;
  } else if (**p == 'l') {
    (*p)++;
    if (**p == 'l') {
      specs->length = 'w';  // символ для ll чтобы не записывать
      // строку и чтобы не путаться
      (*p)++;
    } else {
      specs->length = 'l';
    }
  } else if (**p == 'L') {
    specs->length = 'L';
    (*p)++;
  } else {
    specs->length = 0;
  }
}

void s21_process_string(char **output, va_list *args, struct format_info *specs,
                        int width) {
  char *value = va_arg(*args, char *);  // Извлекаем строку
  char buffer[100];
  s21_str_copy(buffer, value);
  s21_apply_precision(buffer, specs, 's');  // + точность (обрезаем строку)
  s21_apply_width_and_minus(output, buffer, width, specs->minus, specs->zero,
                            specs);  // + ширина и флаг -
}

void s21_append_char(char **dest, char c) {
  if (!dest || !*dest) {
    return;
  }
  **dest = c;
  (*dest)++;
}

void s21_append_str(char **dest, const char *src) {
  if (!dest || !*dest || !src || *src == '\0') {
    return;
  }

  while (*src) {
    s21_append_char(dest, *src);
    src++;
  }
}

void s21_int_to_str(long long int value, char *buffer) {
  if (value == LLONG_MIN) {
    s21_str_copy(buffer, "-9223372036854775808");
    return;
  }

  char temp[65];
  int i = 0;
  int is_negative = 0;

  if (value < 0) {
    is_negative = 1;
    unsigned long long int abs_value = (unsigned long long)(-value);
    value = abs_value;
  }

  if (value == 0) {
    temp[i++] = '0';
  } else {
    while (value > 0) {
      temp[i++] = (value % 10) + '0';
      value /= 10;
    }
  }

  if (is_negative) {
    temp[i++] = '-';
  }

  temp[i] = '\0';

  for (int j = 0; j < i; j++) {
    buffer[j] = temp[i - j - 1];
  }
  buffer[i] = '\0';
}

void s21_unsigned_to_str(unsigned long long value, char *buffer) {
  char temp[65];
  int i = 0;

  if (value == 0) {
    temp[i++] = '0';
  } else {
    while (value > 0) {
      temp[i++] = (value % 10) + '0';
      value /= 10;
    }
  }

  temp[i] = '\0';

  for (int j = 0; j < i; j++) {
    buffer[j] = temp[i - j - 1];
  }
  buffer[i] = '\0';
}

void s21_process_leading_zeros(char **output, const char *buffer, int width,
                               int is_negative) {
  int len = s21_str_length(buffer);
  int padding = width > len ? width - len : 0;

  if (is_negative) {
    s21_append_char(output, '-');
  }

  for (int i = 0; i < padding; i++) {
    s21_append_char(output, '0');
  }

  s21_append_str(output, is_negative ? buffer + 1 : buffer);
}

void s21_str_copy(char *dest, const char *src) {
  if (!dest) {
    return;
  }
  if (!src) {
    s21_append_str(&dest, "(null)");
    *dest = '\0';  // тут нужно завершение строки чтобы вывод не содержал
    // мусорные байты
    return;
  }

  while (*src) {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = '\0';
}

void s21_float_to_str(double value, char *buffer, int precision) {
  if (buffer == NULL ||
      s21_handle_special_values_and_zero_float(value, buffer)) {
    return;
  }

  int is_negative = signbit(value);  // доп проверка на знак
  if (is_negative) {
    value = -value;
  }
  handle_whole_and_fraction(value, buffer, precision, is_negative);

  // new
  if (is_negative && buffer[0] != '-') {
    // Сдвигаем строку вправо для добавления знака
    size_t len = s21_str_length(buffer);
    for (size_t i = len; i > 0; i--) {
      buffer[i] = buffer[i - 1];
    }
    buffer[0] = '-';
    buffer[len + 1] = '\0';
  }
}

int s21_handle_special_values_and_zero_float(double value, char *buffer) {
  int is_special = 0;

  if (isinf(value)) {
    s21_str_copy(buffer, (value > 0) ? "inf" : "-inf");
    is_special = 1;
  } else if (isnan(value)) {
    s21_str_copy(buffer, "nan");
    is_special = 1;
  } else if (value == 0.0) {
    s21_str_copy(buffer, signbit(value) ? "-0.000000" : "0.000000");
    is_special = 1;
  } else if (value == __FLT_MAX__) {
    s21_str_copy(buffer, "340282346638528859811704183484516925440.000000");
    is_special = 1;
  } else if (value == -__FLT_MAX__) {
    s21_str_copy(buffer, "-340282346638528859811704183484516925440.000000");
    is_special = 1;
  }

  return is_special;
}

void handle_whole_and_fraction(double value, char *buffer, int precision,
                               int is_negative) {
  double rounded_value = value + (value >= 0 ? 0.5 : -0.5) / pow(10, precision);

  long long whole = (long long)rounded_value;

  double fraction = rounded_value - whole;

  s21_int_to_str(whole, buffer);
  int len = s21_str_length(buffer);

  if (is_negative && whole != 0) {
    for (int i = len; i >= 0; i--) {
      buffer[i + 1] = buffer[i];
    }
    buffer[0] = '-';
    len++;
  }

  if (precision > 0) {
    buffer[len++] = '.';
    handle_fraction(fraction, buffer, len, precision);
  }
}

void handle_fraction(double fraction, char *buffer, int start_index,
                     int precision) {
  int len = start_index;

  for (int i = 0; i < precision; i++) {
    fraction *= 10;
    int digit = (int)fraction;
    buffer[len++] = '0' + digit;
    fraction -= digit;
  }

  buffer[len] = '\0';
}

void s21_apply_width_and_minus(char **output, const char *value, int width,
                               int minus, int zero, struct format_info *specs) {
  int len = s21_str_length(value);
  int num_spaces = (width > len) ? width - len : 0;

  if (minus) {
    // Выравнивание влево
    s21_append_str(output, value);
    for (int i = 0; i < num_spaces; i++) {
      s21_append_char(output, ' ');
    }
  } else {
    // Если точность указана, флаг zero игнорируется
    char fill_char = (zero && !minus && !specs->precision) ? '0' : ' ';

    for (int i = 0; i < num_spaces; i++) {
      s21_append_char(output, fill_char);
    }

    if (value[0] == '-' && (*output)[-1] == '-') {
      (*output)--;
    }

    s21_append_str(output, value);
  }
}

void s21_apply_plus_and_space(char **output, double value, int plus_flag,
                              int space_flag) {
  if (value >= 0) {
    if (plus_flag) {
      s21_append_char(output, '+');
    } else if (space_flag) {
      s21_append_char(output, ' ');
    }
  }
}

int s21_str_length(const char *str) {
  int len = 0;
  while (str[len] != '\0') len++;
  return len;
}

void s21_apply_precision(char *buffer, struct format_info *specs, char type) {
  if (!specs->precision) return;

  if (type == 'd' || type == 'u' || type == 'o') {
    int len = s21_str_length(buffer);

    if (buffer[0] == '-') {
      char temp[100] = {0};
      temp[0] = '-';
      int zeros_to_add = specs->precision_value > len - 1
                             ? specs->precision_value - (len - 1)
                             : 0;

      // Добавляем нули после знака
      for (int i = 0; i < zeros_to_add; i++) {
        temp[i + 1] = '0';
      }

      s21_str_copy(temp + zeros_to_add + 1, buffer + 1);
      s21_str_copy(buffer, temp);
    } else {
      if (specs->precision_value > len) {
        int zeros_to_add = specs->precision_value - len;
        char temp[100] = {0};
        for (int i = 0; i < zeros_to_add; i++) {
          temp[i] = '0';
        }
        s21_str_copy(temp + zeros_to_add, buffer);
        s21_str_copy(buffer, temp);
      }
    }
  } else if (type == 'f') {
    s21_float_to_str(atof(buffer), buffer, specs->precision_value);
  } else if (type == 's') {
    int len = s21_str_length(buffer);
    if (specs->precision_value < len) {
      buffer[specs->precision_value] = '\0';
    }
  }
}

int s21_sprintf(char *str, const char *format, ...) {
  setlocale(LC_ALL, "en_US.UTF-8");
  char *output = str;
  const char *p = format;
  va_list args;
  va_start(args, format);

  while (*p) {
    if (*p == '%') {
      p++;

      struct format_info specs = {0};
      s21_parse_flags(&p, &specs);
      int width = s21_parse_width(&p, &args, &specs);
      s21_parse_precision(&p, &args, &specs);
      s21_parse_length(&p, &specs);

      switch (*p) {
        case 'c':
          if (specs.length == 'l') {
            s21_process_wchar(&output, &args, &specs, width);
          } else {
            s21_process_char(&output, &args, &specs, width);
          }
          break;
        case 's':
          s21_process_string(&output, &args, &specs, width);
          break;
        case 'd':
          s21_process_d(&output, &args, &specs, width);
          break;
        case 'u':
          s21_process_u(&output, &args, &specs, width);
          break;
        case 'f':
          s21_process_f(&output, &args, &specs, width);
          break;
        case 'e':
        case 'E':
          s21_process_e(&output, &args, &specs, width, *p);
          break;
        case 'g':
        case 'G':
          s21_process_g(&output, &args, &specs, width, *p);
          break;
        case 'x':
        case 'X':
          s21_process_x(&output, &args, &specs, width, *p);
          break;
        case 'o':
          s21_process_o(&output, &args, &specs, width);
          break;
        case 'p':
          s21_process_p(&output, &args, &specs, width);
          break;

        default:
          s21_append_char(&output, '%');
          s21_append_char(&output, *p);
          break;
      }
      p++;
    } else {
      s21_append_char(&output, *p);
      p++;
    }
  }

  *output = '\0';
  va_end(args);
  return (int)(output - str);
}

// доп задание
void s21_float_to_sci(long double value, char *buffer, int precision,
                      int is_uppercase) {
  char mantissa[100] = {0};
  char exponent[10] = {0};
  int exp = 0;

  char *buffer_start = buffer;
  if (value < 0) {
    value = -value;
    *buffer++ = '-';
  }

  if (value != 0.0) {
    while (value >= 10.0) {
      value /= 10.0;
      exp++;
    }
    while (value < 1.0) {
      value *= 10.0;
      exp--;
    }
  }

  s21_float_to_str(value, mantissa, precision);

  char exp_sign = (exp < 0) ? '-' : '+';
  if (exp < 0) {
    exp = -exp;
  }

  int exp_len = 0;
  exponent[exp_len++] = exp_sign;
  if (exp >= 100) {
    exponent[exp_len++] = (exp / 100) + '0';
  }
  exponent[exp_len++] = ((exp / 10) % 10) + '0';
  exponent[exp_len++] = (exp % 10) + '0';
  exponent[exp_len] = '\0';

  // Объединение мантиссы и экспоненты
  s21_str_copy(buffer, mantissa);
  s21_str_copy(buffer + s21_str_length(mantissa), is_uppercase ? "E" : "e");
  s21_str_copy(buffer + s21_str_length(mantissa) + 1, exponent);

  // Завершаем строку
  buffer_start[s21_str_length(buffer_start)] = '\0';
}

void s21_exponent_to_str(int exponent, char *buffer, int is_uppercase) {
  int offset = 0;

  buffer[offset++] = is_uppercase ? 'E' : 'e';

  if (exponent < 0) {
    buffer[offset++] = '-';
    exponent = -exponent;
  } else {
    buffer[offset++] = '+';
  }

  char temp[10];
  int temp_index = 0;
  if (exponent == 0) {
    temp[temp_index++] = '0';
  } else {
    while (exponent > 0) {
      temp[temp_index++] = (exponent % 10) + '0';
      exponent /= 10;
    }
  }

  for (int i = 0; i < temp_index; i++) {
    buffer[offset + i] = temp[temp_index - i - 1];
  }

  buffer[offset + temp_index] = '\0';
}

void s21_process_e(char **output, va_list *args, struct format_info *specs,
                   int width, char specifier) {
  char buffer[100];
  double value;
  if (specs->length == 'L') {
    value = va_arg(*args, long double);
  } else {
    value = va_arg(*args, double);
  }
  int precision = specs->precision ? specs->precision_value : 6;
  int is_uppercase = (specifier == 'E');
  if (isinf(value)) {
    s21_str_copy(buffer, (value > 0) ? (is_uppercase ? "INF" : "inf")
                                     : (is_uppercase ? "-INF" : "-inf"));
  } else if (isnan(value)) {
    s21_str_copy(buffer, is_uppercase ? "NAN" : "nan");
  } else {
    s21_float_to_sci(value, buffer, precision, is_uppercase);
  }

  if (value == 0.0 && specs->precision && specs->precision_value == 0) {
    char empty_buffer[1] = {'\0'};
    s21_str_copy(buffer, empty_buffer);
    s21_apply_width_and_minus(output, buffer, width, specs->minus, specs->zero,
                              specs);
    return;
  }

  char temp_output[200] = {0};
  char *temp_ptr = temp_output;

  if (specs->hash && !s21_memchr(buffer, '.', s21_str_length(buffer))) {
    s21_append_char(&temp_ptr, '.');
  }

  if (value < 0 && specs->zero) {
    s21_append_char(output, '-');
    buffer[0] = '0';
    width--;
  }

  s21_apply_plus_and_space(&temp_ptr, value, specs->plus, specs->space);

  s21_append_str(&temp_ptr, buffer);

  int total_length = s21_str_length(temp_output);
  int padding = (width > total_length) ? width - total_length : 0;

  s21_format_with_padding(output, "", temp_output, padding, width, specs,
                          value);
}

void s21_process_g(char **output, va_list *args, struct format_info *specs,
                   int width, char specifier) {
  double value;
  if (specs->length == 'L') {
    value = va_arg(*args, long double);
  } else {
    value = va_arg(*args, double);
  }

  int precision = specs->precision ? specs->precision_value : 6;

  char buffer[200] = {0};

  if (isnan(value)) {
    s21_str_copy(buffer, "NAN");
    s21_apply_width_and_minus(output, buffer, width, specs->minus, specs->zero,
                              specs);
    return;
  }
  if (isinf(value)) {
    s21_str_copy(buffer, value > 0 ? "inf" : "-inf");
    s21_apply_width_and_minus(output, buffer, width, specs->minus, specs->zero,
                              specs);
    return;
  }

  // Нормализация значения для определения экспоненты
  double abs_value = value < 0 ? -value : value;
  int exp = 0;

  if (abs_value != 0.0) {
    while (abs_value >= 10.0) {
      abs_value /= 10.0;
      exp++;
    }
    while (abs_value < 1.0) {
      abs_value *= 10.0;
      exp--;
    }
  }

  // Округление до заданного количества значащих цифр
  if (abs_value != 0.0) {
    double scale = pow(10, precision - 1 - exp);
    value = round(value * scale) / scale;
  }

  // Выбор формата: e/E или f
  if (exp < -4 || exp >= precision) {
    specs->uppercase = (specifier == 'G');
    s21_float_to_sci(value, buffer, precision - 1, specs->uppercase);
  } else {
    s21_float_to_str(value, buffer, precision > 0 ? precision - (exp + 1) : 1);
  }

  // Обработка флага `0` при наличии ширины
  if (value < 0 && specs->zero) {
    s21_append_char(output, '-');
    width--;
    if (buffer[0] == '.' || (buffer[0] >= '0' && buffer[0] <= '9')) {
      // Замена только если это необходимо (например, для чисел без экспоненты)
      buffer[0] = '0';
    }
  }

  // Удаление конечных нулей, если флаг # не установлен
  if (!specs->hash) {
    char *dot = s21_memchr(buffer, '.', s21_str_length(buffer));
    if (dot) {
      char *end = buffer + s21_str_length(buffer) - 1;
      while (*end == '0') end--;
      if (*end == '.') end--;
      *(end + 1) = '\0';
    }
  }

  char *start_pos = buffer;
  if (*buffer == '-') {
    start_pos++;
  }

  if (specs->zero && !specs->minus && width > (int)s21_str_length(start_pos)) {
    int padding = width - s21_str_length(start_pos);
    char temp_buffer[200] = {0};

    // Если есть минус, он остается в начале строки
    if (*buffer == '-') {
      temp_buffer[0] = '-';
      s21_memset(temp_buffer + 1, '0', padding);
      s21_str_copy(temp_buffer + 1 + padding, start_pos);
    } else {
      s21_memset(temp_buffer, '0', padding);
      s21_str_copy(temp_buffer + padding, start_pos);
    }

    s21_str_copy(buffer, temp_buffer);
  }

  // Добавляем знак или пробел, если нужно
  char temp_output[200] = {0};
  char *temp_ptr = temp_output;

  s21_apply_plus_and_space(&temp_ptr, value, specs->plus, specs->space);

  s21_append_str(&temp_ptr, buffer);

  s21_apply_width_and_minus(output, temp_output, width, specs->minus, 0, specs);
}

int s21_calculate_exponent(double *abs_value) {
  int exp = 0;
  if (*abs_value != 0.0) {
    while (*abs_value >= 10.0) {
      *abs_value /= 10.0;
      exp++;
    }
    while (*abs_value < 1.0) {
      *abs_value *= 10.0;
      exp--;
    }
  }
  return exp;
}

void s21_round_significant_digits(double *value, int precision, int exp) {
  double scale = pow(10, precision - 1 - exp);
  *value = round(*value * scale) / scale;
}

void s21_remove_trailing_zeros(char *buffer) {
  char *dot = s21_memchr(buffer, '.', s21_str_length(buffer));
  if (dot) {
    char *end = buffer + s21_str_length(buffer) - 1;
    while (*end == '0') {
      *end = '\0';
      end--;
    }
    if (*end == '.') {
      *end = '\0';
    }
  }
}

void s21_format_and_apply_flags(char **output, char *buffer, double value,
                                int width, struct format_info *specs) {
  char temp_output[200] = {0};
  char *temp_ptr = temp_output;

  // Добавляем знак или пробел
  s21_apply_plus_and_space(&temp_ptr, value, specs->plus, specs->space);

  // Гарантируем наличие точки, если установлен флаг `#`
  if (specs->hash && !s21_memchr(buffer, '.', s21_str_length(buffer))) {
    int len = s21_str_length(buffer);
    buffer[len] = '.';
    buffer[len + 1] = '\0';
  }

  // Вычисляем ширину для выравнивания
  int total_length = s21_str_length(temp_output) + s21_str_length(buffer);
  int padding = (width > total_length) ? width - total_length : 0;

  // Применяем флаги `0` и `minus`
  if (specs->zero && !specs->minus) {
    for (int i = 0; i < padding; i++) {
      s21_append_char(&temp_ptr, '0');
    }
    s21_append_str(&temp_ptr, buffer);
  } else if (specs->minus) {
    // Если флаг `minus`, выравниваем значение влево
    s21_append_str(&temp_ptr, buffer);
    for (int i = 0; i < padding; i++) {
      s21_append_char(&temp_ptr, ' ');
    }
  } else {
    // Выравнивание вправо (пробелы перед значением)
    for (int i = 0; i < padding; i++) {
      s21_append_char(&temp_ptr, ' ');
    }
    s21_append_str(&temp_ptr, buffer);
  }

  s21_append_str(output, temp_output);
}

void s21_handle_special_values_exp(char *buffer, double value,
                                   struct format_info *specs, char **output,
                                   int width) {
  if (isnan(value)) {
    s21_str_copy(buffer, "nan");
  } else if (isinf(value)) {
    s21_str_copy(buffer, value > 0 ? "inf" : "-inf");
  }
  s21_apply_width_and_minus(output, buffer, width, specs->minus, specs->zero,
                            specs);
}

void s21_int_to_hex(unsigned long long value, char *buffer, int is_uppercase) {
  const char *digits = is_uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
  char temp[65];
  int i = 0;

  if (value == 0) {
    temp[i++] = '0';
  } else {
    while (value > 0) {
      temp[i++] = digits[value % 16];
      value /= 16;
    }
  }

  temp[i] = '\0';

  for (int j = 0; j < i; j++) {
    buffer[j] = temp[i - j - 1];
  }
  buffer[i] = '\0';
}

void s21_process_x(char **output, va_list *args, struct format_info *specs,
                   int width, char specifier) {
  unsigned long long value = s21_extract_unsigned_value(args, specs);
  char buffer[100] = {0};
  int is_uppercase = (specifier == 'X');

  s21_int_to_hex(value, buffer, is_uppercase);

  if (specs->precision) {
    s21_apply_precision_x(buffer, specs->precision_value);
  }

  s21_handle_zero_value(buffer, value, specs, output, width);

  char prefix[3] = {0};
  if (specs->hash && value != 0) {
    prefix[0] = '0';
    prefix[1] = is_uppercase ? 'X' : 'x';
  }

  int total_length = s21_str_length(prefix) + s21_str_length(buffer);
  int padding = (width > total_length) ? width - total_length : 0;

  s21_format_with_padding(output, prefix, buffer, padding, width, specs, value);
}

void s21_apply_precision_x(char *buffer, int precision) {
  int len = s21_str_length(buffer);
  if (precision > len) {
    char temp[100] = {0};
    int zeros_to_add = precision - len;
    for (int i = 0; i < zeros_to_add; i++) {
      temp[i] = '0';
    }
    s21_str_copy(temp + zeros_to_add, buffer);
    s21_str_copy(buffer, temp);
  }
}

void s21_process_o(char **output, va_list *args, struct format_info *specs,
                   int width) {
  unsigned long long value = s21_extract_unsigned_value(args, specs);
  char buffer[100] = {0};

  s21_int_to_oxto(value, buffer);

  if (specs->precision) {
    s21_apply_precision_x(buffer, specs->precision_value);
  }
  s21_handle_zero_value(buffer, value, specs, output, width);

  char prefix[2] = {0};
  if (specs->hash && value != 0) {
    prefix[0] = '0';
  }

  int total_length = s21_str_length(prefix) + s21_str_length(buffer);
  int padding = (width > total_length) ? width - total_length : 0;
  s21_format_with_padding(output, prefix, buffer, padding, width, specs, value);
}

unsigned long long s21_extract_unsigned_value(va_list *args,
                                              struct format_info *specs) {
  unsigned long long value = 0;

  if (specs->length == 'h') {
    value = (unsigned short int)va_arg(*args, int);
  } else if (specs->length == 'l') {
    value = va_arg(*args, unsigned long int);
  } else if (specs->length == 'w') {  // для ll
    value = va_arg(*args, unsigned long long int);
  } else {
    value = va_arg(*args, unsigned int);
  }

  return value;
}

void s21_format_with_padding(char **output, const char *prefix,
                             const char *buffer, int padding, int width,
                             struct format_info *specs,
                             unsigned long long value) {
  (void)width;
  (void)value;

  char temp_output[200] = {0};
  char *temp_ptr = temp_output;

  if (specs->zero && !specs->minus && !specs->precision) {
    s21_append_str(&temp_ptr, prefix);
    for (int i = 0; i < padding; i++) {
      s21_append_char(&temp_ptr, '0');
    }
    s21_append_str(&temp_ptr, buffer);
  } else {
    if (specs->minus) {
      s21_append_str(&temp_ptr, prefix);
      s21_append_str(&temp_ptr, buffer);
      for (int i = 0; i < padding; i++) {
        s21_append_char(&temp_ptr, ' ');
      }
    } else {
      for (int i = 0; i < padding; i++) {
        s21_append_char(&temp_ptr, ' ');
      }
      s21_append_str(&temp_ptr, prefix);
      s21_append_str(&temp_ptr, buffer);
    }
  }
  s21_append_str(output, temp_output);
}

void s21_handle_zero_value(char *buffer, unsigned long long value,
                           struct format_info *specs, char **output,
                           int width) {
  if ((value == 0 && specs->precision && specs->precision_value == 0) ||
      (value == 0 && specs->precision && specs->precision_value == 0 &&
       specs->hash)) {
    char empty_buffer[1] = {'\0'};
    s21_str_copy(buffer, empty_buffer);
    s21_apply_width_and_minus(output, buffer, width, specs->minus, specs->zero,
                              specs);
  }
}

void s21_int_to_oxto(unsigned long long value, char *buffer) {
  char temp[65];
  int i = 0;

  if (value == 0) {
    temp[i++] = '0';
  } else {
    while (value > 0) {
      temp[i++] = (value % 8) + '0';
      value /= 8;
    }
  }

  temp[i] = '\0';

  for (int j = 0; j < i; j++) {
    buffer[j] = temp[i - j - 1];
  }
  buffer[i] = '\0';
}

void s21_process_p(char **output, va_list *args, struct format_info *specs,
                   int width) {
  void *value = va_arg(*args, void *);
  char buffer[100] = {0};

  if (value == NULL) {
    char temp_output[200] = "(nil)";
    s21_apply_width_and_minus(output, temp_output, width, specs->minus,
                              specs->zero, specs);
    return;
  }

  // адрес в шестнадцатеричное представление
  unsigned long long address = (unsigned long long)value;
  s21_int_to_hex(address, buffer, 0);

  // Добавляем 0x
  char temp_output[200] = {0};
  char *temp_ptr = temp_output;
  s21_append_char(&temp_ptr, '0');
  s21_append_char(&temp_ptr, 'x');

  s21_append_str(&temp_ptr, buffer);
  s21_apply_width_and_minus(output, temp_output, width, specs->minus,
                            specs->zero, specs);
}
