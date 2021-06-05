// Консольная программа для демонстрации
#include <assert.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>


#include "matrix.h"

int int_value(const wchar_t *title) {
  wprintf(L"%ls: ", title);  // Выводим приглашение на ввод
  int x;                     // Выбор пользователя
  wscanf(L"%d", &x);
  return x;
}

// Вывод меню и выбор из меню
// На входе:
//  title - заголовок меню
//  N - количество пунктов меню (вариантов для выбора)
//  ... (varargs) - пункты меню (массив строк)
// На выходе: выбор пользователя
int menu(const wchar_t *title, int N, ...) {
  assert(N >= 2);               // Хотя бы 2 варианта должно быть для выбора
  wprintf(L"\n%ls:\n", title);  // Печатаем заголовок меню ls - строчка в формате юникод
  // Печатаем меню
  va_list args;  // Обьявляем что забирать параметры из ... мы будем через переменную args
  va_start(args, N);                              // Будем обрабатывать N параметров
  for (int i = 1; i <= N; i++) {                  // i=1,2,3...N - номер пункта меню
    wchar_t *menuItem = va_arg(args, wchar_t *);  // Получаем очередной пункт меню из списка
    wprintf(L"  %d. %ls\n", i, menuItem);
  }
  va_end(args);  // Завершаем работу со списком аргументов
  // Печатаем предложение о выборе
  wprintf(L"Выберите (1..%d): ", N);
  int choice;  // Выбор пользователя
  wscanf(L"%d", &choice);
  return choice;
}

void matrix_add_interface() {
  wprintf(L"Сложение матриц\n");
  wprintf(L"Ввод матрицы A\n");
  Matrix a = matrix_input(TYPE);
  wprintf(L"Ввод матрицы B\n");
  Matrix b = matrix_input(TYPE);
  Matrix c = matrix_add(a, b);
  matrix_show(c);
  wprintf(L"\n");
}

void matrix_mul_interface() {
  wprintf(L"Умножение матриц\n");
  wprintf(L"Ввод матрицы A\n");
  Matrix a = matrix_input(TYPE);
  wprintf(L"Ввод матрицы B\n");
  Matrix b = matrix_input(TYPE);
  Matrix c = matrix_mul(a, b);
  matrix_show(c);
  wprintf(L"\n");
}

void matrix_scalar_multiplication_interface() {
  wprintf(L"Умножение матрицы на скаляр\n");
  wprintf(L"Ввод матрицы\n");
  Matrix a = matrix_input(TYPE);
  wprintf(L"Ввод числа (скаляра): ");
  void *scalar = TYPE.input();
  Matrix res = matrix_scalar(a, scalar);
  matrix_show(res);
}

void matrix_linear_transformations_1_interface() {
  wprintf(L"Прибавление к строке линейной комбинации других строк\n");
  wprintf(L"Ввод матрицы\n");
  Matrix a = matrix_input(TYPE);
  // Строка[i] = Строка[i] + коэффициент * Строка[j]
  int i = int_value(L"Индекс изменяемой строки");
  int j = int_value(L"Индекс строки, которую будем прибавлять к изменяемой");
  wprintf(L"Ввод коэффициента:");
  void *coef = INT_Type.input();
  Matrix res = matrix_linear_transformation_1(a, i, j, coef);
  matrix_show(res);
  wprintf(L"\n");
}

void matrix_linear_transformations_2_interface() {
  wprintf(L"Прибавление к столбцу линейной комбинации других столбцов\n");
  wprintf(L"Ввод матрицы\n");
  Matrix a = matrix_input(TYPE);
  // Строка[i] = Строка[i] + коэффициент * Строка[j]
  int i = int_value(L"Индекс изменяемого стролбца");
  int j = int_value(L"Индекс стролбца, который будем прибавлять к изменяемому");
  wprintf(L"Ввод коэффициента:");
  void *coef = INT_Type.input();
  Matrix res = matrix_linear_transformation_2(a, i, j, coef);
  matrix_show(res);
  wprintf(L"\n");
}

void matrix_transpose_interface() {
  wprintf(L"Транспонирование\n");
  wprintf(L"Ввод матрицы A\n");
  Matrix a = matrix_input(TYPE);
  Matrix c = matrix_transpose(a);
  matrix_show(c);
  wprintf(L"\n");
}

#define TYPES_NUM 3

// Основная программа
int main() {
  // Задаём кодировку UTF-16 для всего вывода в программе
  // Все символы и строки будут wchar_t

#if WIN32 || WIN64
  _setmode(_fileno(stdout), _O_U16TEXT);
  _setmode(_fileno(stdin), _O_U16TEXT);
  _setmode(_fileno(stderr), _O_U16TEXT);
#endif
  // Создадим 2 вектора по 2 элемента с типами int и float
  // TODO: сделать эксперимент: Create0(2, )
  EL TYPES[TYPES_NUM] = {INT_Type, FLOAT_Type, DOUBLE_Type};
  wprintf(L"== Квадратная матрица ==\n");
  int type = menu(L"Какой тип элементов матрицы вы будете использовать", TYPES_NUM, L"Целые числа",
                  L"Вещественные числа (float)", L"Вещественные числа (double)");
  if (type < 1 || type > TYPES_NUM) {
    wprintf(L"Типа %d нет => выход из программы\n", type);
    return 0;
  }
  TYPE = TYPES[type - 1];
  wprintf(L"Вы выбрали: %ls\n", TYPE.type);
  while (1) {
    int op = menu(L"Возможные операции (0-выход)", 6, L"Матричное сложение", L"Матричное умножение",
                  L"Умножение матрицы на скаляр", L"Прибавление к строке линейной комбинации других строк",
                  L"Прибавление к столбцу линейной комбинации других столбцов", L"Транспонирование");
    switch (op) {
    case 1:
      matrix_add_interface();
      break;
    case 2:
      matrix_mul_interface();
      break;
    case 3:
      matrix_scalar_multiplication_interface();
      break;
    case 4:
      matrix_linear_transformations_1_interface();
      break;
    case 5:
      matrix_linear_transformations_2_interface();
      break;
    case 6:
      matrix_transpose_interface();
      break;
    default:
      return 0;
    }
  }
}
