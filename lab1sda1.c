#include <stdio.h>
#include <string.h>

#define SIZE 10

typedef struct {
    char fio[100];
    char position[50];
    float salary;
    int shipped_goods;
} Worker;


/* Очистка буфера после scanf, чтобы в потоке не оставался символ перевода строки */
void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


/* Ввод строки */
void inputString(char *str, int size) {
    scanf(" %[^\n]", str);
    clearInput();
}


/* Ввод работника */
void inputWorker(Worker *w) {
    printf("Введите ФИО: ");
    inputString(w->fio, 100);

    printf("Введите должность: ");
    inputString(w->position, 50);

    printf("Введите зарплату: ");
    scanf("%f", &w->salary);
    clearInput();

    printf("Введите количество отгруженных товаров: ");
    scanf("%d", &w->shipped_goods);
    clearInput();
}


/* Вывод одного работника */
void printWorker(Worker w, int index) {
    printf("\nРаботник #%d\n", index);
    printf("ФИО: %s\n", w.fio);
    printf("Должность: %s\n", w.position);
    printf("Зарплата: %.2f\n", w.salary);
    printf("Отгружено товаров: %d\n", w.shipped_goods);
}


/* Вывод всех работников */
void printAll(Worker workers[], int count) {
    if (count == 0) {
        printf("Список пуст.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printWorker(workers[i], i);
    }
}


/* Редактирование работников */
void editWorker(Worker *w) {
    int choice;

    printf("\nЧто редактировать?\n");
    printf("1. ФИО\n");
    printf("2. Должность\n");
    printf("3. Зарплата\n");
    printf("4. Количество товаров\n");
    printf("Выбор: ");

    scanf("%d", &choice);
    clearInput();

    switch (choice) {
        case 1:
            printf("Новое ФИО: ");
            inputString(w->fio, 100);
            break;

        case 2:
            printf("Новая должность: ");
            inputString(w->position, 50);
            break;

        case 3:
            printf("Новая зарплата: ");
            scanf("%f", &w->salary);
            clearInput();
            break;

        case 4:
            printf("Новое количество товаров: ");
            scanf("%d", &w->shipped_goods);
            clearInput();
            break;

        default:
            printf("Неверный выбор.\n");
    }
}


/* Поиск по должности */
void searchByPosition(Worker workers[], int count) {
    char pos[50];
    int found = 0;

    if (count == 0) {
        printf("Список пуст.\n");
        return;
    }

    printf("Введите должность для поиска: ");
    inputString(pos, 50);

    for (int i = 0; i < count; i++) {
        if (strcmp(workers[i].position, pos) == 0) {
            printWorker(workers[i], i);
            found = 1;
        }
    }

    if (!found) {
        printf("Работники с такой должностью не найдены.\n");
    }
}


int main() {

    Worker workers[SIZE];
    int count = 0;
    int choice;

    do {
        printf("\n----- МЕНЮ -----\n");
        printf("1. Добавить работника\n");
        printf("2. Показать всех\n");
        printf("3. Редактировать\n");
        printf("4. Поиск по должности\n");
        printf("0. Выход\n");
        printf("Выбор: ");

        scanf("%d", &choice);
        clearInput();

        switch (choice) {

            case 1:
                if (count < SIZE) {
                    inputWorker(&workers[count]);
                    count++;
                } else {
                    printf("Массив заполнен!\n");
                }
                break;

            case 2:
                printAll(workers, count);
                break;

            case 3: {
                int index;
                printf("Введите индекс: ");
                scanf("%d", &index);
                clearInput();

                if (index >= 0 && index < count) {
                    editWorker(&workers[index]);
                } else {
                    printf("Неверный индекс.\n");
                }
                break;
            }

            case 4:
                searchByPosition(workers, count);
                break;

        }

    } while (choice != 0);

    return 0;
}