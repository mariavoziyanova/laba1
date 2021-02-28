#ifndef MATRIX_H
#define MATRIX_H

#include <wchar.h>

// Операции над заданным типом данных
typedef struct {
    int size;                      // Размер одного элемента в памяти
    wchar_t *(*type);              // Имя типа для вывода на экран: int, float, double
    void *(*zero)();               // Константа 0
    void *(*input)();              // Ввод значения с клавиатуры
    void *(*add)(void *, void *);  // Сумма двух значений
    void *(*mul)(void *, void *);  // Произведение двух значений
    void *(*copy)(void *);         // Копирование значений
    void (*show)(void *);          // Вывести значение на экран
} EL;

extern EL INT_Type;
extern EL FLOAT_Type;
extern EL DOUBLE_Type;
extern EL TYPE;  // Выбранный тип элементов

// Динамический массив из N*N элементов
typedef struct
{
    int N;         // Размер матрицы
    void ***data;  // Данные матрицы
} Matrix;



Matrix matrix_create(int);
// Ввод матрицы
Matrix matrix_input();
// Получить элемент
void *matrix_get(Matrix, int, int);//пока не нужно

// Поменять элемент
void matrix_set(Matrix, int, int, void *);//пока не нужно

// Сложение матриц
Matrix matrix_add(Matrix, Matrix);
// Умножение матриц
Matrix matrix_mul(Matrix, Matrix);
//Умножение матрицы на скаляр
Matrix matrix_scalar(Matrix a, void*);

// Прибавление к строке линейной комбинации других строк
Matrix matrix_linear_transformation_1(Matrix a, int, int, void *);

// Прибавление к столбцу линейной комбинации других стролбцов
Matrix matrix_linear_transformation_2(Matrix a, int, int, void *);

//Транспонирование
Matrix matrix_transpose(Matrix a);

// Вывод матрицы на экран
void matrix_show(Matrix);

#endif  // MATRIX_H
