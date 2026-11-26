#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void count_letters(const char *str, int *count_array) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            count_array[tolower((unsigned char)str[i]) - 'a']++;
        }
    }
}

bool is_anagram(const char *str1, const char *str2) {
    int count1[26] = {0};
    int count2[26] = {0};

    count_letters(str1, count1);
    count_letters(str2, count2);

    for (int i = 0; i < 26; i++) {
        if (count1[i] != count2[i]) {
            return false;
        }
    }
    return true; 
}

void print_anagram_diff(const char *str1, const char *str2) {
    int count1[26] = {0};
    int count2[26] = {0};

    count_letters(str1, count1);
    count_letters(str2, count2);

    printf("Не хватает во второй строке: ");
    bool missing = false;
    for (int i = 0; i < 26; i++) {
        if (count1[i] > count2[i]) {
            for (int j = 0; j < (count1[i] - count2[i]); j++) {
                printf("%c ", 'a' + i);
            }
            missing = true;
        }
    }
    if (!missing) printf("нет");
    printf("\n");
    printf("Лишние во второй строке: ");
    bool extra = false;
    for (int i = 0; i < 26; i++) {
        if (count2[i] > count1[i]) {
            for (int j = 0; j < (count2[i] - count1[i]); j++) {
                printf("%c ", 'a' + i);
            }
            extra = true;
        }
    }
    if (!extra) printf("нет");
    printf("\n");
}

int main() {
    int choice;
    printf("Выберите режим работы:\n");
    printf("1 - Запустить встроенные тестовые задания\n");
    printf("2 - Ввести строки с клавиатуры\n");
    printf("Ваш выбор: ");
    
    if (scanf("%d", &choice) != 1) {
        printf("Ошибка ввода выбора.\n");
        return 1;
    }

       while (getchar() != '\n');

    if (choice == 1) {
        char a[] = "listen";
        char b[] = "silent";
        printf("\nВстроенный тест \nСтрока A: %s\nСтрока B: %s\n", a, b);
        if (is_anagram(a, b)) {
            printf("Вердикт: строки являются анаграммами.\n");
        } else {
            printf("Вердикт: строки НЕ являются анаграммами.\n");
            print_anagram_diff(a, b);
        }

    } else if (choice == 2) {
        char user_a[256];
        char user_b[256];

        printf("\nВведите первую строку: ");
        if (fgets(user_a, sizeof(user_a), stdin) != NULL) {
            user_a[strcspn(user_a, "\n")] = '\0';
        }

        printf("Введите вторую строку: ");
        if (fgets(user_b, sizeof(user_b), stdin) != NULL) {
            user_b[strcspn(user_b, "\n")] = '\0';
        }

        printf("\nРЕЗУЛЬТАТ ПРОВЕРКИ\n");
        printf("Строка A: %s\n", user_a);
        printf("Строка B: %s\n", user_b);
        if (is_anagram(user_a, user_b)) {
            printf("Вердикт: строки являются анаграммами.\n");
        } else {
            printf("Вердикт: строки НЕ являются анаграммами.\n");
            print_anagram_diff(user_a, user_b);
        }

    } else {
        printf("Неверный выбор режима.\n");
    }

    return 0;
}