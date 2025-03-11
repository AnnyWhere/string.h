F = -Wall -Werror -Wextra -std=c11
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
LDFLAGS = -lcheck -lsubunit -lm

SRC = $(wildcard s21_*.c)
TEST_SRC = $(wildcard tests/*.c)
OBJ = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

.PHONY: all clean test gcov_report

# Цель по умолчанию
all: s21_string.a test gcov_report

# Сборка библиотеки
s21_string.a: $(OBJ)
	ar rcs $@ $^
	ranlib $@

%.o: %.c
	gcc $(F) -c $< -o $@

# Тестирование
test: s21_string.a
	gcc $(F) $(GCOV_FLAGS) $(SRC) $(TEST_SRC) -o testing $(LDFLAGS)
	./testing

# Генерация отчета о покрытии
gcov_report: test
	lcov --directory . --capture --output-file coverage.info
	genhtml coverage.info --output-directory out
	open out/index.html

# Удаление всех скомпилированных файлов
clean:
	rm -f s21_string.a
	rm -f $(OBJ) $(TEST_OBJ)
	rm -f *.gcda *.gcno *.css *.html *.info
	rm -f testing
	rm -d -rf out
