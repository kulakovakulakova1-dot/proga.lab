#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-9

// Функция для вычисления определителя матрицы N*N методом Гаусса
double determinant(int n, double matrix[n][n]) {
    double mat[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mat[i][j] = matrix[i][j];
        }
    }

    double det = 1.0;
    for (int i = 0; i < n; i++) {
        int k = i;
        for (int j = i + 1; j < n; j++) {
            if (fabs(mat[j][i]) > fabs(mat[k][i])) {
                k = j;
            }
        }

        if (fabs(mat[k][i]) < EPS) {
            return 0.0;
        }

        if (k != i) {
            for (int j = 0; j < n; j++) {
                double temp = mat[i][j];
                mat[i][j] = mat[k][j];
                mat[k][j] = temp;
            }
            det = -det;
        }

        det *= mat[i][i];

        for (int j = i + 1; j < n; j++) {
            double factor = mat[j][i] / mat[i][i];
            for (int l = i; l < n; l++) {
                mat[j][l] -= factor * mat[i][l];
            }
        }
    }
    return det;
}

// Решение СЛАУ методом Крамера
int solveCramer(int n, double A[n][n], double B[n], double X[n]) {
    double detA = determinant(n, A);

    if (fabs(detA) < EPS) {
        printf("Главный определитель равен нулю. Система не имеет единственного решения.\n");
        return 0; 
    }

    double tempA[n][n];

    for (int i = 0; i < n; i++) {
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                tempA[r][c] = A[r][c];
            }
        }

        for (int r = 0; r < n; r++) {
            tempA[r][i] = B[r];
        }

        double detI = determinant(n, tempA);
        X[i] = detI / detA;
    }
    return 1; 
}

//функция для генерации имени переменной
void getVarName(int index, int n, char* buffer) {
    if (n <= 26) {
        sprintf(buffer, "%c", 'a' + index);
    } else {
        sprintf(buffer, "x%d", index + 1);
    }
}

// Ручной ввод матрицы и вектора свободных членов
int inputMatrix(int n, double A[n][n], double B[n]) {
    printf("Введите элементы матрицы A (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%lf", &A[i][j]) != 1) {
                return 0;
            }
        }
    }

    printf("Введите вектор свободных членов B (%d элементов):\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%lf", &B[i]) != 1) {
            return 0;
        }
    }
    return 1;
}

// Красивый вывод системы уравнений
void printSystem(int n, double A[n][n], double B[n]) {
    printf("Система уравнений:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char varName[10];
            getVarName(j, n, varName);
            
            printf("%.0f*%s", A[i][j], varName);
            if (j < n - 1) {
                printf("+");
            }
        }
        printf(" = %.0f\n", B[i]);
    }
}

// Вывод результатов решения
void printResults(int n, double X[n]) {
    printf("Решение системы:\n");
    for (int i = 0; i < n; i++) {
        char varName[10];
        getVarName(i, n, varName);
        
        printf("%s = %.2f", varName, X[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("\n\n");
}

// Запуск тестовых примеров
void runSingleTest() {
      int n = 4;
        double A1[4][4] = { {2, 5, 4, 1}, {1, 3, 2, 1}, {2, 10, 9, 7}, {3, 8, 9, 2} };
        double B1[4] = {20, 11, 40, 37};    
        double X1[4];
        
        printf("--- ТЕСТ №1 (Размерность 4x4) ---\n");
        printSystem(4, A1, B1);
        if (solveCramer(4, A1, B1, X1)) printResults(4, X1);

        double A2[4][4] =  { {1, 3, 5, 7}, {3, 5, 7, 1}, {5, 7, 1, 3}, {7, 1, 3, 5} };
        double B2[4] = {12, 0, 4, 16};
        double X2[4];

        printf("--- ТЕСТ №2 (Размерность 4x4) ---\n");
        printSystem(n, A2, B2);
        if (solveCramer(n, A2, B2, X2)) printResults(n, X2);
  
        n = 8;
        double A4[8][8] = {
            {2, 6, -2, 3, 3, 6, 1, 6}, {1, 4, 4, 2, 4, 7, -2, 3}, {3, 6, 7, -1, 0, 5, 3, 1}, {7, 3, 6, 0, 7, 4, 2, 4}, 
            {1, 0, -1, 2, 3, 6, 0, -2},  {-1, 0, 2, 6, -2, 0, 5, -1},  {4, 5, -2, 7, 4, 4, 5, -2},  {3, 3, 4, 6, -2, 6, -2, 2}
        };
        double B4[8] = {22, 39, 34, 23, 3, 26, 17, 37};
        double X4[8];

        printf("--- ТЕСТ №3 (Размерность 8x8) ---\n");
        printSystem(n, A4, B4);
        if (solveCramer(n, A4, B4, X4)) printResults(n, X4);
    }

int main() {
    int mode = 0;
    printf("Выберите режим работы:\n");
    printf("1 - Запустить встроенные тесты\n");
    printf("2 - Ввести пример вручную\n");
    printf("Ваш выбор: ");
    
    if (scanf(" %d", &mode) != 1 || (mode != 1 && mode != 2)) {
        printf("Некорректный выбор.\n");
        return 1;
    }
    
    if (mode == 1) {
        printf("\n-----Встроенные тесты-----\n\n");
        runSingleTest();
    } 
    else {
        int n = 0;
        printf("\nРаздел ручного ввода одного примера.\n");
        printf("Введите размерность матрицы N: ");
        if (scanf("%d", &n) != 1 || n <= 0) {
            printf("Некорректная размерность.\n");
            return 1;
        }

        double A[n][n];
        double B[n];
        double X[n];

        if (!inputMatrix(n, A, B)) {
            printf("Ошибка ввода данных.\n");
            return 1;
        }

        printf("\nВаш пример:\n");
        printSystem(n, A, B);
        if (solveCramer(n, A, B, X)) {
            printResults(n, X);
        }
    }

    return 0;
}