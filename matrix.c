#include "matrix.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <wchar.h>

void *int_zero()
{
    static int INT_ZERO = 0;
    return &INT_ZERO;
}

void *float_zero()
{
    static float FLOAT_ZERO = 0.0f;
    return &FLOAT_ZERO;
}

void *double_zero()
{
    static double DOUBLE_ZERO = 0.0;
    return &DOUBLE_ZERO;
}


void *int_input()
{
    int *res = (int *)malloc(sizeof(int));
    wscanf(L"%d", res);
    return res;
}

void *float_input()
{
    float *res = (float *)malloc(sizeof(float));
    wscanf(L"%f", res);
    return res;
}

void *double_input()
{
    double *res = (double *)malloc(sizeof(double));
    wscanf(L"%lf", res);
    return res;
}

void *int_add(void *a, void *b)
{
    int *res = (int *)malloc(sizeof(int));
    *res = *(int *)a + *(int *)b;
    return res;
}

void *float_add(void *a, void *b)
{
    float *res = (float *)malloc(sizeof(float));
    *res = *(float *)a + *(float *)b;
    return res;
}

void *double_add(void *a, void *b)
{
    double *res = (double *)malloc(sizeof(double));
    *res = *(double *)a + *(double *)b;
    return res;
}

void *int_mul(void *a, void *b)
{
    int *res = (int *)malloc(sizeof(int));
    *res = *(int *)a * *(int *)b;
    return res;
}

void *float_mul(void *a, void *b)
{
    float *res = (float *)malloc(sizeof(float));
    *res = *(float *)a * *(float *)b;
    return res;
}

void *double_mul(void *a, void *b)
{
    double *res = (double *)malloc(sizeof(double));
    *res = *(double *)a * *(double *)b;
    return res;
}
void *int_copy(void *a)
{
    int *res = malloc(sizeof(int));
    *res = *((int *)a);
    return res;
}

void *float_copy(void *a)
{
    float *res = malloc(sizeof(float));
    *res = *(float *)a;
    return res;
}

void *double_copy(void *a)
{
    double *res = (double *)malloc(sizeof(double));
    *res = *(double *)a;
    return res;
}

void int_show(void *x)
{
    wprintf(L"%d", *(int *)x);
}

void float_show(void *x)
{
    wprintf(L"%f", *(float *)x);
}

void double_show(void *x)
{
    wprintf(L"%lf", *(double *)x);
}

EL INT_Type = {sizeof(int), L"целые числа int", int_zero, int_input, int_add, int_mul, int_copy, int_show};
EL FLOAT_Type = {sizeof(float), L"вещественные числа float", float_zero, float_input, float_add, float_mul, float_copy,float_show};
EL DOUBLE_Type = {sizeof(double), L"вещественные числа double", double_zero, double_input, double_add, double_mul, double_copy,double_show};
EL TYPE;  // Выбранный тип элементов

// Создание квадратной матрицы размера N * N, заполненной нулями
Matrix matrix_create(int N)
{
    Matrix m;
    m.N = N;  // Записываем размер
    // Создаём в динамической памяти массив строк
    m.data = (void ***)malloc(sizeof(void **) * N);
    // Создаём каждую строчку в отдельности
    for (int i = 0; i < N; i++)
    {
        m.data[i] = (void **)malloc(sizeof(void *) * N);
        // Заполняем строчку нулями
        for (int j = 0; j < N; j++)
        {
            m.data[i][j] = TYPE.zero();
        }
    }
    return m;
}

Matrix matrix_input()
{
    Matrix m;
    wprintf(L"Введите количество элементов (размер) матрицы: ");
    wscanf(L"%d", &m.N);
    // Создаём массив указателей N элементов void **
    m.data = (void ***)malloc(sizeof(void **) * m.N);
    // Вводим в цикле все элементы
    for (int i = 0; i < m.N; i++)
    {
        m.data[i] = (void **)malloc(sizeof(void *) * m.N);
        for (int j = 0; j < m.N; j++)
        {
            wprintf(L"    Введите элемент %d %d: ", i, j);
            m.data[i][j] = TYPE.input();
        }
    }
    return m;
}
// Получить элемент
void *matrix_get(Matrix m, int i, int j)
{
    return m.data[i][j];
}

// Поменять элемент
void matrix_set(Matrix m, int i, int j, void *value)
{
    m.data[i][j] = value;
}
// Сложение матриц
Matrix matrix_add(Matrix a, Matrix b)
{
    if (a.N != b.N)
    {
        wprintf(L" Размеры матриц не совпадают %d!=%d\n", a.N, b.N);
        return a;
    }
    // Создаём новую матрицу такого же размера
    Matrix m = matrix_create(a.N);
    // Суммируем в цикле все элементы
    for (int i = 0; i < m.N; i++)
    {
        for (int j = 0; j < m.N; j++)
        {
            m.data[i][j] = TYPE.add(a.data[i][j], b.data[i][j]);
        }
    }
    return m;
}

// Умножение матриц
Matrix matrix_mul(Matrix a, Matrix b)
{
    if (a.N != b.N)
    {
        wprintf(L" Размеры матриц не совпадают %d!=%d\n", a.N, b.N);
        return a;
    }
    // Создаём новую матрицу такого же размера
    Matrix m = matrix_create(a.N);
    for (int i = 0; i < m.N; i++)
        for (int j = 0; j < m.N; j++)
            for (int k = 0; k < m.N; k++)
            {
                m.data[i][j] = TYPE.add(m.data[i][j], TYPE.mul(a.data[i][k], b.data[k][j]));
            }
    return m;
}

// Умножение матрицы на скаляр
Matrix matrix_scalar(Matrix a, void *scalar)
{
    Matrix res = matrix_create(a.N);   // Матрица-результат
    for (int i = 0; i < res.N; i++)    // Цикл по строкам
        for (int j = 0; j < res.N; j++)  // Цикл по столбцам
            res.data[i][j] = TYPE.mul(a.data[i][j], scalar);
    return res;
}

// Прибавление к строке линейной комбинации других строк
// destination - индекс строки к которой прибавляем
// source - индекс строки которую прибавляем
Matrix matrix_linear_transformation_1(Matrix a, int destination, int source, void *coef)
{
    if (destination<1 || destination>a.N || source> a.N || source  < 1)
    {
        if (destination < 1 || destination > a.N)
        {
            wprintf(L" Строки %d не существует\n", destination);
        }
        if (source > a.N || source  < 1)
        {
            wprintf(L" Строки %d не существует\n", source);
        }
        return a;
    }
    Matrix res = matrix_create(a.N);  // Матрица-результат
    // Копируем все элементы исходной матрицы
    for (int i = 0; i < res.N; i++)    // Цикл по строкам
    {
        for (int j = 0; j < res.N; j++)  // Цикл по столбцам
        {
            res.data[i][j] = TYPE.copy(a.data[i][j]);
        }
    }
    for (int k = 0; k < res.N; k++)
    {  // Цикл по столбцам
        // Строка[destination] = Строка[destination] + Строка[source] * coef
        res.data[destination-1][k] = TYPE.add(res.data[destination-1][k], TYPE.mul(res.data[source-1][k],coef));
    }
    return res;

}


// Прибавление к столбцу линейной комбинации других столбцов
// destination - индекс столбца к которому прибавляем
// source - индекс столбца который прибавляем
Matrix matrix_linear_transformation_2(Matrix a, int destination, int source, void *coef)
{
    if (destination<1 || destination>a.N || source> a.N || source  < 1)
    {
        if (destination < 1 || destination > a.N)
        {
            wprintf(L" Столбца %d не существует\n", destination);
        }
        if (source > a.N || source  < 1)
        {
            wprintf(L" Столбца %d не существует\n", source);
        }
        return a;
    }
    Matrix res = matrix_create(a.N);  // Матрица-результат
    // Копируем все элементы исходной матрицы
    for (int i = 0; i < res.N; i++)    // Цикл по строкам
    {
        for (int j = 0; j < res.N; j++)  // Цикл по столбцам
        {
            res.data[i][j] = TYPE.copy(a.data[i][j]);
        }
    }
    for (int k = 0; k < res.N; k++)
    {  // Цикл по столбцам
        // Столбец[destination] = Столбец[destination] + Столбец[source] * coef
        res.data[k][destination-1] = TYPE.add(res.data[k][destination-1], TYPE.mul(res.data[k][source-1],coef));
    }
    return res;

}


// Транспонирование
Matrix matrix_transpose(Matrix a)
{
    // Создаём новую матрицу такого же размера
    Matrix m = matrix_create(a.N);
    // Меняем местами строки и столбцы
    for (int i = 0; i < m.N; i++)
        for (int j = 0; j < m.N; j++)
            {
                m.data[i][j]=a.data[j][i];
            }
    return m;
}


// Вывод матрицы на экран
void matrix_show(Matrix m)
{
    // Суммируем в цикле все элементы
    for (int i = 0; i < m.N; i++)
    {
        for (int j = 0; j < m.N; j++)
        {
            TYPE.show(m.data[i][j]);
            wprintf(L" ");
        }
        wprintf(L"\n");
    }
}


