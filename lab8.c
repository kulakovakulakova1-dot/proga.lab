#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//материалы
#define EMPTY 0 //пусто
#define SAND 1 // песок
#define WALL 2 //стена
#define WATER 3 //вода

// замер времени в сек
static double now_s(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
}

// курсор в левый верхний угол и очистка экрана
void clear_screen(void) {
    printf("\033[H\033[J");
}

// Вывод поля
void print_map(int **map, int rows, int cols) {
    clear_screen();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (map[i][j] == SAND) {
                printf("\033[1;33m#\033[0m"); // Желтый песок
            } else if (map[i][j] == WATER) {
                printf("\033[1;34m~\033[0m"); // Синяя вода
            } else if (map[i][j] == WALL) {
                printf("\033[1;37m█\033[0m"); // Белое препятствие
            } else {
                printf(".");                   // Пустота
            }
        }
        printf("\n");
    }
    fflush(stdout);
}

// начало стен
void init_walls(int **map, int rows, int cols) {
    int mid_r = rows / 2;
    int mid_c = cols / 2;
    // сами стены
    for (int j = mid_c - cols/5; j <= mid_c + cols/5; j++) {
        if (j >= 0 && j < cols) {
            map[mid_r][j] = WALL;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Использование: %s <строки N> <столбцы M>\n", argv[0]);
        return 1;
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    int ticks = 300; // скок тактов

    if (rows <= 0 || cols <= 0) {
        fprintf(stderr, "Размеры поля должны быть положительными числами!\n");
        return 1;
    }

    // Выделение динамич памяти для матрицы
    int **map = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        map[i] = (int *)calloc(cols, sizeof(int));
    }

    srand(time(NULL));
    init_walls(map, rows, cols);

    struct timespec delay;
    delay.tv_sec = 0;
    delay.tv_nsec = 50000000L; 

    long checksum = 0;

    // начало времени
    double t0 = now_s();

    for (int t = 0; t < ticks; t++) {
        // Каждые неск тиков + песок или воду сверху в случайный столб
        if (t % 2 == 0) {
            int spawn_col = rand() % cols;
            if (map[0][spawn_col] == EMPTY) {
                map[0][spawn_col] = (rand() % 2 == 0) ? SAND : WATER;
            }
        }

        // физика СНИЗУ ВВЕРХ
        for (int i = rows - 2; i >= 0; i--) {
            for (int j = 0; j < cols; j++) {
                int current = map[i][j];

                if (current == SAND) {
                    //  вниз
                    if (map[i + 1][j] == EMPTY) {
                        map[i + 1][j] = SAND;
                        map[i][j] = EMPTY;
                    } 
                    // по диагонали
                    else {
                        int left_empty = (j > 0 && map[i + 1][j - 1] == EMPTY);
                        int right_empty = (j < cols - 1 && map[i + 1][j + 1] == EMPTY);

                        if (left_empty && right_empty) {
                            int side = rand() % 2; 
                            map[i + 1][j - 1 + 2 * side] = SAND;
                            map[i][j] = EMPTY;
                        } else if (left_empty) {
                            map[i + 1][j - 1] = SAND;
                            map[i][j] = EMPTY;
                        } else if (right_empty) {
                            map[i + 1][j + 1] = SAND;
                            map[i][j] = EMPTY;
                        }
                    }
                } 
                else if (current == WATER) {
                    // вниз
                    if (map[i + 1][j] == EMPTY) {
                        map[i + 1][j] = WATER;
                        map[i][j] = EMPTY;
                    } 
                    // по диагонали
                    else if (j > 0 && map[i + 1][j - 1] == EMPTY) {
                        map[i + 1][j - 1] = WATER;
                        map[i][j] = EMPTY;
                    } else if (j < cols - 1 && map[i + 1][j + 1] == EMPTY) {
                        map[i + 1][j + 1] = WATER;
                        map[i][j] = EMPTY;
                    } 
                    //  вбок для воды
                    else {
                        int left_flow = (j > 0 && map[i][j - 1] == EMPTY);
                        int right_flow = (j < cols - 1 && map[i][j + 1] == EMPTY);

                        if (left_flow && right_flow) {
                            int side = (rand() % 2 == 0) ? -1 : 1;
                            map[i][j + side] = WATER;
                            map[i][j] = EMPTY;
                        } else if (left_flow) {
                            map[i][j - 1] = WATER;
                            map[i][j] = EMPTY;
                        } else if (right_flow) {
                            map[i][j + 1] = WATER;
                            map[i][j] = EMPTY;
                        }
                    }
                }
            }
        }

        // картинка
        //if (rows <= 50 && cols <= 100) { 
            print_map(map, rows, cols);
            nanosleep(&delay, NULL);
        //}
    }

    // контр сумма
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            checksum += map[i][j];
        }
    }

    double dt = now_s() - t0;
    // --- КОНЕЦ ЗАМЕРА ВРЕМЕНИ ---

    printf("\nСимуляция завершена за: %.6f секунд.\n", dt);
    printf("Контрольная сумма поля: %ld\n", checksum);

    // чистим динам память
    for (int i = 0; i < rows; i++) {
        free(map[i]);
    }
    free(map);

    return 0;
}
// проверка 