#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

int main() {
    short int complex[2 * N]; 
    double energy = 0.0;

    srand(time(NULL));

    for (int i = 0; i < 2 * N; i++) {
        complex[i] = (rand() % 65536) - 32768;
}

    printf("Отсчёты сигнала:\n");
    for (int i = 0; i < N; i++) {
        printf("s[%d] = %.1f + j*(%.1f)\n", i, (double)complex[2 * i],       (double)complex[2 * i + 1]);
}
        for (int i = 0; i < N; i++) {
        double re = complex[2 * i];
        double im = complex[2 * i + 1];
        energy += (re * re) + (im * im);
    }
    printf("\nЭнергия сигнала E = %.1f\n", energy);

    int max_complex_idx = 0; 
    short int max_re = complex[0]; // Первый четный элемент

    for (int i = 1; i < N; i++) {
        if (complex[2 * i] > max_re) {
            max_re = complex[2 * i];
            max_complex_idx = i;
        }
    }
    printf("Максимальный элемент реальной части: s[%d].re = %.1f\n", max_complex_idx, (double)max_re);

    return 0;
}
