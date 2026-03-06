#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char fio[100];
    char position[50];
    float salary;
    int shipped_goods;
} Worker;

void inputWorker(Worker *w) {
    printf("ФИО: ");
    scanf(" %[^\n]", w->fio);

    printf("Должность: ");
    scanf(" %[^\n]", w->position);

    printf("Зарплата: ");
    scanf("%f", &w->salary);

    printf("Количество отгруженных товаров: ");
    scanf("%d", &w->shipped_goods);
}

void printWorker(Worker w, int index) {
    printf("\nРаботник #%d\n", index);
    printf("ФИО: %s\n", w.fio);
    printf("Должность: %s\n", w.position);
    printf("Зарплата: %.2f\n", w.salary);
    printf("Отгружено: %d\n", w.shipped_goods);
}

Worker* expandArray(Worker *workers, int oldSize, int newSize) {
    Worker *newArray = (Worker*)malloc(newSize * sizeof(Worker));

    for (int i = 0; i < oldSize; i++) {
        newArray[i] = workers[i];
    }

    free(workers);
    return newArray;
}

void editWorker(Worker *workers, int count) {
    if (count == 0) {
        printf("Список пуст.\n");
        return;
    }

    int index;
    printf("Введите индекс работника: ");
    scanf("%d", &index);

    if (index < 0 || index >= count) {
        printf("Неверный индекс.\n");
        return;
    }

    int fieldChoice;

    printf("\nЧто редактировать?\n");
    printf("1. ФИО\n");
    printf("2. Должность\n");
    printf("3. Зарплату\n");
    printf("4. Количество отгруженных товаров\n");
    printf("Выбор: ");
    scanf("%d", &fieldChoice);

    switch (fieldChoice) {
        case 1:
            printf("Новое ФИО: ");
            scanf(" %[^\n]", workers[index].fio);
            break;
        case 2:
            printf("Новая должность: ");
            scanf(" %[^\n]", workers[index].position);
            break;
        case 3:
            printf("Новая зарплата: ");
            scanf("%f", &workers[index].salary);
            break;
        case 4:
            printf("Новое количество: ");
            scanf("%d", &workers[index].shipped_goods);
            break;
        default:
            printf("Неверный выбор.\n");
    }
}

void searchByPosition(Worker *workers, int count) {
    if (count == 0) {
        printf("Список пуст.\n");
        return;
    }

    char key[50];
    int found = 0;

    printf("Введите должность для поиска: ");
    scanf(" %[^\n]", key);

    for (int i = 0; i < count; i++) {
        if (strcmp(workers[i].position, key) == 0) {
            printWorker(workers[i], i);
            found = 1;
        }
    }

    if (!found) {
        printf("Работники с такой должностью не найдены.\n");
    }
}

int main() {

    Worker *workers = NULL;
    int count = 0;
    int capacity = 0;
    int choice;

    do {
        printf("\n=== МЕНЮ ===\n");
        printf("1. Добавить работника\n");
        printf("2. Показать всех\n");
        printf("3. Удалить последнего\n");
        printf("4. Редактировать по индексу\n");
        printf("5. Поиск по должности\n");
        printf("0. Выход\n");
        printf("Выбор: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                if (count == capacity) {
                    int newCapacity = capacity + 1;
                    workers = expandArray(workers, capacity, newCapacity);
                    capacity = newCapacity;
                }
                inputWorker(&workers[count]);
                count++;
                break;

            case 2:
                if (count == 0) {
                    printf("Список пуст.\n");
                } else {
                    for (int i = 0; i < count; i++) {
                        printWorker(workers[i], i);
                    }
                }
                break;

            case 3:
                if (count > 0) {
                    count--;
                    printf("Последний работник удалён.\n");
                } else {
                    printf("Список пуст.\n");
                }
                break;

            case 4:
                editWorker(workers, count);
                break;

            case 5:
                searchByPosition(workers, count);
                break;
        }

    } while (choice != 0);

    free(workers);
    printf("Память освобождена. Программа завершена.\n");

    return 0;
}