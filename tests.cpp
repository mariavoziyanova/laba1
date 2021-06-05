#include "gtest/gtest.h"
extern "C" {

#include "matrix.h"

}

TEST(int_type, zero) {
  int *res = (int *)INT_Type.zero();
  ASSERT_EQ(0, *res);
}

TEST(int_type, add) {
  for (int a = -1; a <= 3; a++) {
    int b = 5;
    int *res = (int *)INT_Type.add(&a, &b);
    ASSERT_EQ(a + b, *res);
  }
}

TEST(int_type, mul) {
  for (int a = -1; a <= 3; a++) {
    for (int b = -1; b <= 3; b++) {
      int *res = (int *)INT_Type.mul(&a, &b);
      ASSERT_EQ(a * b, *res);
    }
  }
}

TEST(float_type, zero) {
  float *res = (float *)FLOAT_Type.zero();
  ASSERT_EQ(0, *res);
}

TEST(float_type, add) {
  float a = 2.3;
  float b = 5.23;
  float *res = (float *)FLOAT_Type.add(&a, &b);
  ASSERT_NEAR(a + b, *res, 0.001);
}

TEST(float_type, mul) {
  for (float a = -1.4; a <= 3; a += 1.4) {
    for (float b = -0.5; b <= 3; b += 1.5) {
      float *res = (float *)FLOAT_Type.mul(&a, &b);
      ASSERT_NEAR(a * b, *res, 0.001);
    }
  }
}

TEST(matrix, create) {
  // Проверка граничного случая - матрица размером 0*0
  Matrix m = matrix_create(INT_Type, 0);
  ASSERT_EQ(0, m.N);
  // Проверка создания обычной матрицы 2*2
  Matrix m2 = matrix_create(FLOAT_Type, 2);
  ASSERT_EQ(2, m2.N);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) {
      ASSERT_EQ(0.0, *((float *)m2.data[i][j]));
    }
}

TEST(matrix, add) {
  int N = 10;
  Matrix first = matrix_create(INT_Type, N);
  Matrix second = matrix_create(INT_Type, N);
  Matrix ans = matrix_create(INT_Type, N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      *((int *)first.data[i][j]) = i + j;
      *((int *)second.data[i][j]) = i - j;
      *((int *)ans.data[i][j]) = 2 * i;
    }
  }
  Matrix res = matrix_create(INT_Type, N);
  matrix_show(first);
  matrix_add(first, second);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      ASSERT_EQ(*((int *)res.data[i][j]), *((int *)ans.data[i][j]));
    }
  }
}

TEST(matrix, mul) {
  int N = 10;
  Matrix first = matrix_create(INT_Type, N);
  Matrix second = matrix_create(INT_Type, N);
  Matrix ans = matrix_create(INT_Type, N);

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      *((int *)first.data[i][j]) = i + j;
      *((int *)second.data[i][j]) = i - j;
      *((int *)ans.data[i][j]) = i * i - j * j;
    }
  }
  Matrix res = matrix_mul(first, second);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      ASSERT_EQ(*((int *)res.data[i][j]), *((int *)ans.data[i][j]));
    }
  }
}

TEST(maxtrix, scalar) {
  int N = 10;
  Matrix first = matrix_create(INT_Type, N);
  Matrix ans = matrix_create(INT_Type, N);
  int k = 15;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      *((int *)first.data[i][j]) = i + j;
      *((int *)ans.data[i][j]) = k * (i + j);
    }
  }
  Matrix res = matrix_scalar(first, &k);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      ASSERT_EQ(*((int *)res.data[i][j]), k * *((int *)ans.data[i][j]));
    }
  }
}

TEST(matrix, transpose) {
  int N = 10;
  Matrix first = matrix_create(INT_Type, N);
  Matrix ans = matrix_create(INT_Type, N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      *((int *)first.data[i][j]) = i - j;
      *((int *)ans.data[i][j]) = j - i;
    }
  }
  Matrix res = matrix_transpose(first);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      ASSERT_EQ(*((int *)res.data[i][j]), *((int *)ans.data[i][j]));
    }
  }
}
