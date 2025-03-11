#include "s21_string.h"

// Выполняет поиск первого вхождения символа в первых n байтах строки
void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *result = S21_NULL;

  if (str != S21_NULL) {
    const unsigned char *byte_ptr = (const unsigned char *)str;
    s21_size_t i = 0;

    for (; i < n && byte_ptr[i] != (unsigned char)c; i++) {
    }

    if (i < n) {
      result = (void *)(byte_ptr + i);
    }
  }

  return result;
}

// Сравнивает первые n байтов str1 и str2
int s21_memcmp(const void *ptr1, const void *ptr2, s21_size_t n) {
  // Проверка на S21_NULL указатели
  if (ptr1 == S21_NULL && ptr2 == S21_NULL) return 0;
  if (ptr1 == S21_NULL) return -1;
  if (ptr2 == S21_NULL) return 1;

  // Преобразование указателей в байтовые указатели
  const uint8_t *byte_ptr1 = (const uint8_t *)ptr1;
  const uint8_t *byte_ptr2 = (const uint8_t *)ptr2;
  s21_size_t block_size = sizeof(s21_size_t);
  int result = 0;
  int found_difference = 0;

  // Проверка на выравнивание указателей для оптимизации
  if (IS_ALIGNED(byte_ptr1, ALIGNMENT_OF(s21_size_t)) &&
      IS_ALIGNED(byte_ptr2, ALIGNMENT_OF(s21_size_t))) {
    s21_size_t block_count = n / block_size;

    // Сравнение блоков памяти, если указатели выровнены
    for (s21_size_t i = 0; i < block_count && !found_difference; ++i) {
      const s21_size_t *block1 =
          (const s21_size_t *)(byte_ptr1 + i * block_size);
      const s21_size_t *block2 =
          (const s21_size_t *)(byte_ptr2 + i * block_size);

      // Если блоки не равны, сохраняем разницу и прекращаем дальнейшее
      // сравнение
      if (*block1 != *block2) {
        result = *block1 - *block2;
        found_difference = 1;
      }
    }

    // Если блоки памяти равны, сравниваем оставшиеся байты
    if (!found_difference) {
      byte_ptr1 += block_count * block_size;
      byte_ptr2 += block_count * block_size;
      n %= block_size;
    }
  }

  // Сравнение оставшихся байтов памяти (если не было различий в блоках)
  for (s21_size_t i = 0; i < n && !found_difference; ++i) {
    if (byte_ptr1[i] != byte_ptr2[i]) {
      result = byte_ptr1[i] - byte_ptr2[i];
      found_difference = 1;
    }
  }

  return result;
}

// Копирует n символов из src в dest
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  void *result = S21_NULL;

  if (dest != S21_NULL && src != S21_NULL) {
    char *d = (char *)dest;
    const char *s = (const char *)src;

    for (s21_size_t i = 0; i < n; i++) {
      d[i] = s[i];
    }

    result = dest;
  }

  return result;
}

// Выполняет поиск первого вхождения символа в строке
char *s21_strchr(const char *s, int c) {
  char *result = S21_NULL;

  if (s != S21_NULL) {
    size_t i = 0;

    while (s[i] != '\0' && s[i] != (char)c) {
      i++;
    }

    if (s[i] == (char)c || (char)c == '\0') {
      result = (char *)&s[i];
    }
  }

  return result;
}

// Добавляет строку, на которую указывает src, в конец строки, на которую
// указывает dest, длиной до n символов
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *result = S21_NULL;

  if (dest != S21_NULL && src != S21_NULL) {
    s21_size_t dest_len = 0;
    while (dest[dest_len] != '\0') {
      dest_len++;
    }

    s21_size_t i = 0;
    while (i < n && src[i] != '\0') {
      dest[dest_len + i] = src[i];
      i++;
    }

    dest[dest_len + i] = '\0';

    result = dest;
  }

  return result;
}

// Вычисляет длину начального сегмента str1, который полностью состоит из
// символов, не входящих в str2
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t i = 0;
  bool found = false;

  while (str1[i] != '\0' && !found) {
    for (s21_size_t j = 0; str2[j] != '\0' && !found; j++) {
      if (str1[i] == str2[j]) {
        found = true;
      }
    }
    if (!found) {
      i++;
    }
  }

  return i;
}

// Копирует до n символов из строки, на которую указывает src, в dest
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  unsigned int i = 0;
  if (dest != S21_NULL && src != S21_NULL) {
    for (; i < n; i++) {
      *(dest + i) = *(src + i);
    }

    // Заполняем остаток dest символами '\0', если строка src короче n
    for (; i < n; i++) {
      *(dest + i) = '\0';
    }
  }
  return dest;
}

// Сравнивает не более первых n байтов str1 и str2
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  int flag = 0;
  while ((*str1 || *str2) && n-- && flag == 0) {
    if (*str1++ != *str2++) {
      result = (unsigned char)*--str1 - (unsigned char)*--str2;
      flag = 1;
    }
  }
  return result;
}

// Копирует символ в первые n символов строки, на которую указывает аргумент
// str.
void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *str_copy = str;
  for (s21_size_t i = 0; i < n; i++) {
    *(str_copy + i) = (unsigned char)c;
  }
  return str_copy;
}

// Вычисляет длину строки str, не включая завершающий нулевой символ
s21_size_t s21_strlen(const char *str) {
  s21_size_t length = 0;
  for (; str[length] != '\0'; length++);
  return length;
}

#ifdef __linux__
#define N 134
static const char *mass_errors[] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource temporarily unavailable",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device or resource busy",
    "File exists",
    "Invalid cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Numerical result out of range",
    "Resource deadlock avoided",
    "File name too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Too many levels of symbolic links",
    "Unknown error 41",
    "No message of desired type",
    "Identifier removed",
    "Channel number out of range",
    "Level 2 not synchronized",
    "Level 3 halted",
    "Level 3 reset",
    "Link number out of range",
    "Protocol driver not attached",
    "No CSI structure available",
    "Level 2 halted",
    "Invalid exchange",
    "Invalid request descriptor",
    "Exchange full",
    "No anode",
    "Invalid request code",
    "Invalid slot",
    "Unknown error 58",
    "Bad font file format",
    "Device not a stream",
    "No data available",
    "Timer expired",
    "Out of streams resources",
    "Machine is not on the network",
    "Package not installed",
    "Object is remote",
    "Link has been severed",
    "Advertise error",
    "Srmount error",
    "Communication error on send",
    "Protocol error",
    "Multihop attempted",
    "RFS specific error",
    "Bad message",
    "Value too large for defined data type",
    "Name not unique on network",
    "File descriptor in bad state",
    "Remote address changed",
    "Can not access a needed shared library",
    "Accessing a corrupted shared library",
    ".lib section in a.out corrupted",
    "Attempting to link in too many shared libraries",
    "Cannot exec a shared library directly",
    "Invalid or incomplete multibyte or wide character",
    "Interrupted system call should be restarted",
    "Streams pipe error",
    "Too many users",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address already in use",
    "Cannot assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Transport endpoint is already connected",
    "Transport endpoint is not connected",
    "Cannot send after transport endpoint shutdown",
    "Too many references: cannot splice",
    "Connection timed out",
    "Connection refused",
    "Host is down",
    "No route to host",
    "Operation already in progress",
    "Operation now in progress",
    "Stale file handle",
    "Structure needs cleaning",
    "Not a XENIX named type file",
    "No XENIX semaphores available",
    "Is a named type file",
    "Remote I/O error",
    "Disk quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "Required key not available",
    "Key has expired",
    "Key has been revoked",
    "Key was rejected by service",
    "Owner died",
    "State not recoverable",
    "Operation not possible due to RF-kill",
    "Memory page has hardware error"};
#elif defined(__APPLE__)
#define N 107
static const char *mass_errors[] = {
    "Undefined error: 0",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "Device not configured",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource deadlock avoided",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Resource busy",
    "File exists",
    "Cross-device link",
    "Operation not supported by device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Result too large",
    "Resource temporarily unavailable",
    "Operation now in progress",
    "Operation already in progress",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol family",
    "Address already in use",
    "Can't assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Socket is already connected",
    "Socket is not connected",
    "Can't send after socket shutdown",
    "Too many references: can't splice",
    "Operation timed out",
    "Connection refused",
    "Too many levels of symbolic links",
    "File name too long",
    "Host is down",
    "No route to host",
    "Directory not empty",
    "Too many processes",
    "Too many users",
    "Disc quota exceeded",
    "Stale NFS file handle",
    "Too many levels of remote in path",
    "RPC struct is bad",
    "RPC version wrong",
    "RPC prog. not avail",
    "Program version wrong",
    "Bad procedure for program",
    "No locks available",
    "Function not implemented",
    "Inappropriate file type or format",
    "Authentication error",
    "Need authenticator",
    "Device power is off",
    "Device error",
    "Value too large to be stored in data type",
    "Bad executable (or shared library)",
    "Bad CPU type in executable",
    "Shared library version mismatch",
    "Malformed Mach-o file",
    "Operation canceled",
    "Identifier removed",
    "No message of desired type",
    "Illegal byte sequence",
    "Attribute not found",
    "Bad message",
    "EMULTIHOP (Reserved)",
    "No message available on STREAM",
    "ENOLINK (Reserved)",
    "No STREAM resources",
    "Not a STREAM",
    "Protocol error",
    "STREAM ioctl timeout",
    "Operation not supported on socket",
    "Policy not found",
    "State not recoverable",
    "Previous owner died",
    "Interface output queue is full"};
#endif

// Выполняет поиск во внутреннем массиве номера ошибки errnum и возвращает
// указатель на строку с сообщением об ошибке
char *s21_strerror(int errnum) {
  static char result[60] = "";
  if (errnum > -1 && errnum < N) {
    s21_strcpy(result, (char *)mass_errors[errnum]);
  } else {
    s21_sprintf(result, "Unknown error %d", errnum);
  }
  return result;
}

// Находит первый символ в строке str1, который соответствует любому символу,
// указанному в str2
char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = S21_NULL;
  bool found = false;

  for (; *str1 != '\0' && !found; str1++) {
    for (s21_size_t i = 0; *(str2 + i) != '\0' && !found; i++) {
      if (*str1 == *(str2 + i)) {
        result = (char *)str1;
        found = true;
      }
    }
  }

  return result;
}

// Выполняет поиск последнего вхождения символа в строке
char *s21_strrchr(const char *str, int c) {
  char *result = S21_NULL;
  s21_size_t len = s21_strlen(str);
  bool found = false;

  for (s21_size_t i = len; i-- > 0 && !found;) {
    if (*(str + i) == (char)c) {
      result = (char *)(str + i);
      found = true;
    }
  }

  // Проверка первого символа (нулевого индекса)
  if (len > 0 && *str == (char)c && !found) {
    result = (char *)str;
  }

  return result;
}

// Находит первое вхождение всей строки, оторая встречается в строке haystack
char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;

  if (*needle == '\0') {
    return (char *)haystack;
  }

  for (s21_size_t i = 0; *(haystack + i) != '\0'; i++) {
    if (*(haystack + i) == *needle) {
      s21_size_t j = 0;
      while (*(needle + j) != '\0' && *(haystack + i + j) == *(needle + j)) {
        j++;
      }
      if (*(needle + j) == '\0') {
        result = (char *)(haystack + i);
        break;
      }
    }
  }

  return result;
}

// Разбивает строку str на ряд токенов, разделенных delim
char *s21_strtok(char *str, const char *delim) {
  static char *last = S21_NULL;
  char *token_start = S21_NULL;

  if (str != S21_NULL) {
    last = str;
  }

  if (last == S21_NULL || *last == '\0') {
    token_start = S21_NULL;
  } else {
    while (*last != '\0' && s21_strchr(delim, *last) != S21_NULL) {
      last++;
    }

    if (*last == '\0') {
      token_start = S21_NULL;
    } else {
      token_start = last;

      while (*last != '\0' && s21_strchr(delim, *last) == S21_NULL) {
        last++;
      }

      if (*last != '\0') {
        *last = '\0';
        last++;
      }
    }
  }

  return token_start;
}

// копирует строку, нужна в одной из функций
char *s21_strcpy(char *dest, const char *src) {
  unsigned int i = 0;
  while (*(src + i) != '\0') {
    *(dest + i) = *(src + i);
    i++;
  }
  *(dest + i) = '\0';

  return dest;
}

// Функции из 5 задания

// Возвращает новую строку, в которой указанная строка (str) вставлена в
// указанную позицию (start_index) в данной строке (src).
void *s21_insert(const char *src, const char *str, size_t start_index) {
  void *result = S21_NULL;

  if (src && str && start_index <= s21_strlen(src)) {
    s21_size_t src_len = s21_strlen(src);
    s21_size_t str_len = s21_strlen(str);

    result = malloc(src_len + str_len + 1);

    if (result) {
      char *new_str = (char *)result;

      s21_size_t i = 0;
      while (i < start_index) {
        new_str[i] = src[i];
        ++i;
      }

      s21_size_t j = 0;
      while (j < str_len) {
        new_str[i++] = str[j++];
      }

      s21_size_t k = start_index;
      while (k < src_len) {
        new_str[i++] = src[k++];
      }

      new_str[i] = '\0';
    }
  }

  return result;
}

// Возвращает копию строки (str), преобразованной в нижний регистр
void *s21_to_lower(const char *str) {
  int length = 0;
  void *result = S21_NULL;

  if (str) {
    while (str[length] != '\0') {
      length++;
    }

    char *lower_str = (char *)malloc((length + 1) * sizeof(char));

    if (lower_str != S21_NULL) {
      for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
          lower_str[i] = str[i] + 32;
        } else {
          lower_str[i] = str[i];
        }
      }

      lower_str[length] = '\0';
      result = (void *)lower_str;
    }
  }

  return result;
}

// Возвращает копию строки (str), преобразованной в верхний регистр.
void *s21_to_upper(const char *str) {
  int length = 0;
  void *result = S21_NULL;

  if (str) {
    while (str[length] != '\0') {
      length++;
    }

    char *upper_str = (char *)malloc((length + 1) * sizeof(char));

    if (upper_str != S21_NULL) {
      for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
          upper_str[i] = str[i] - 32;
        } else {
          upper_str[i] = str[i];
        }
      }

      upper_str[length] = '\0';
      result = (void *)upper_str;
    }
  }

  return result;
}

// Возвращает новую строку, в которой удаляются все начальные и конечные
// вхождения набора заданных символов (trim_chars) из данной строки (src).
void *s21_trim(const char *src, const char *trim_chars) {
  if (!src || !trim_chars) {
    return S21_NULL;
  }

  const char *start = src;
  const char *end = src;

  while (*start && s21_strchr(trim_chars, *start)) {
    start++;
  }

  end = start;
  while (*end) {
    end++;
  }
  end--;

  while (end >= start && s21_strchr(trim_chars, *end)) {
    end--;
  }

  size_t new_length = end - start + 1;

  char *trimmed_str =
      (char *)malloc(new_length + 1);  // +1 для нуль-терминатора
  if (!trimmed_str) {
    return S21_NULL;
  }

  for (size_t i = 0; i < new_length; i++) {
    trimmed_str[i] = start[i];
  }

  trimmed_str[new_length] = '\0';

  return trimmed_str;
}