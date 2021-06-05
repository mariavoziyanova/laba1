#ifndef MATRIX_H
#define MATRIX_H

#include <wchar.h>

// Операции над заданным типом данных
// Реализация всех операций через указатель (void *)
typedef struct {
  int size;                      // Размер одного элемента в памяти
  wchar_t *(*type);              // Имя типа для вывода на экран: int, float, complex
  void *(*zero)();               // Константа 0: для int 0 с типом int
  void *(*input)();              // Ввод значения с клавиатуры (консоли)
  void *(*add)(void *, void *);  // Сумма двух значений
  void *(*mul)(void *, void *);  // Произведение двух значений
  void *(*copy)(void *);         // Копирование значений
  void (*show)(void *);          // Вывести значение на экран
} EL;

extern EL INT_Type;
extern EL FLOAT_Type;
extern EL DOUBLE_Type;
extern EL TYPE;  // Выбранный тип элементов

// Квадратная матрица - динамический массив из N*N элементов
//  − Целые числа
//  − Вещественные числа
typedef struct {
  EL TYPE;       // Выбранный тип элементов
  int N;         // Размер матрицы
  void ***data;  // Данные матрицы
} Matrix;

// Создание матрицы:
// Создание квадратной матрицы размера N * N заполненной нулями
Matrix matrix_create(EL, int);

// Ввод матрицы с консоли
Matrix matrix_input();

// Получить элемент
void *matrix_get(Matrix, int, int);

// Поменять элемент
void matrix_set(Matrix, int, int, void *);

// Сложение матриц
Matrix matrix_add(Matrix, Matrix);

// Умножение матриц
Matrix matrix_mul(Matrix, Matrix);

// Умножение матрицы на скаляр
Matrix matrix_scalar(Matrix, void *);

// Прибавление к строке линейной комбинации других строк
Matrix matrix_linear_transformation_1(Matrix, int, int, void *);

// Прибавление к столбцу линейной комбинации других стролбцов
Matrix matrix_linear_transformation_2(Matrix, int, int, void *);

// Транспонирование
Matrix matrix_transpose(Matrix);

// Вывод матрицы на экран
void matrix_show(Matrix);

#endif  // MATRIX_H
